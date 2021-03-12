package mexutils;

=head1 DESCRIPTION

MEXUTILS is a module containing utilities used by MEX.PL.

=cut

# Copyright 1984-2010 The MathWorks, Inc.

require 5.008_008;
use strict;

require Exporter;

use File::Basename;
use File::Spec::Functions;
use File::Spec::Functions qw(rel2abs);
use File::Spec;
use Encode;
use Win32::TieRegistry;
use Win32;

@mexutils::ISA = qw(Exporter);
@mexutils::EXPORT = qw(fileparts mexCatfile mexCatdir mexCanonpath
                       mexGetShortPathName mexGetShortPathPreservingFilename
                       mexSupportedCompilerListLocation mexDeprecationWarning
                       mexRel2abs registry_lookup getUserProfileDir);

#=======================================================================
sub fileparts
{
    #===================================================================
    # fileparts: Tease out path, filename and extension from input.
    #===================================================================

    my ($pathname) = @_;

    #remove " and flip slashes to "\"
    $pathname =~ s/\"//g;
    $pathname = mexCanonpath($pathname);
    
    #Seperate path (first token) from filename (name.ext, second token)
            
    my ($filename, $directory, $extension) = fileparse($pathname, '\..*');
    
    if (mexCanonpath($directory) eq File::Spec->curdir())
   {
        $directory = "";
    }

    return ($directory, $filename, $extension);
}

# This is like File::Spec->catfile except empty strings in input are filtered
# out and I18n encodings are handled.
sub mexCatfile
{
    # Filter out empty inputs
    my @nonEmptyInputs = grep !/^$/, @_;

    my $fullDirPath  = callFunctionInSafeWayForI18N(\&catfile,@nonEmptyInputs);
    
    return $fullDirPath;
}

# This is like File::Spec->catdir except empty strings in input are filtered 
# out and I18n encodings are handled.
sub mexCatdir
{
    # Filter out empty inputs
    my @nonEmptyInputs = grep !/^$/, @_;

    my $fullDirPath  = callFunctionInSafeWayForI18N(\&catdir,@nonEmptyInputs);
    
    # Make sure quotes surround entire path
    if (grep /"/, $fullDirPath) {
        $fullDirPath =~ s/"//g;
        $fullDirPath = '"' . $fullDirPath . '"';
    }

    return $fullDirPath;
}

# This is like File::Spec->canonpath except I18n encodings are handled.
sub mexCanonpath
{
    my $canonicalizedPath = callFunctionInSafeWayForI18N(\&canonpath,$_[0]);
    
    return $canonicalizedPath;
}

# This is like File::Spec->rel2abs except I18n encodings are handled.
sub mexRel2abs
{
    my $fullPath = callFunctionInSafeWayForI18N(\&rel2abs,$_[0]);
    
    return $fullPath;
}

# This functions returns true if the Windows version is Windows 7 or higher.
sub isWin7orHigher
{
    my $itIsWin7OrHigher = 0;

    my ($winMajor) = (`ver` =~ / (\d+)\./);
    my ($winMinor) = (`ver` =~ /\.(\d+)\./);

    if (($winMajor == 6 && $winMinor >= 1) ||  # Windows 7 (v6.1) and its SPs.
         $winMajor > 6) {                     # Future Major version of Windows.  
        $itIsWin7OrHigher = 1
    }
    
    return $itIsWin7OrHigher;
}

# This is like Win32::GetShortPathName except it works around a bug with empty paths
# in perl 5.8.8 and I18n encodings are handled.
sub mexGetShortPathName
{
    my $pathname = $_[0];
    my $isWatcom = $_[1];

    if (isWin7orHigher() && !$isWatcom) {
        # Windows 7 has a cache name inconsistency (bug). If we generate a file
        # with a short path name, it won't appear to exist under its long name 
        # until the cache times out.         
        # BUT Watcom does not handle Long File Names properly with spaces and UNC
        # paths together, Japanese characters, or Simulink inlude.  So if Watcom
        # is used skip thisshort circuit.

       return $pathname;
    }

    # If name is empty or file/directory doesn't exist, just return the input.
    # The usual file test operator -e does not work with Shift-JIS 5c characters,
    # so we are utilizing a bug that if we add an empty space to the directory,
    # even directories with Shift-JIS 5c characters are found to exist.
    if (($pathname eq "") || !(-e $pathname . " ")) {
        return $pathname;
    }

    my $shortName = Win32::GetShortPathName($pathname);
    $shortName = callFunctionInSafeWayForI18N(\&mexUC,$shortName);
   
    return $shortName;
}

# Shortname the path, but not the filename.
sub mexGetShortPathPreservingFilename
{
     my ($directory, $filebase, $extension) = fileparts($_[0]);
     $directory = mexGetShortPathName($directory);
     return mexCatdir($directory, $filebase . $extension);
     
}

# Helper function that evaluates the first input function reference. The
# remaining arguments to callFunctionInSafeWayForI18N are assumed to be the
# arguments passed to the function reference. They are also assumed to be
# strings. These string inputs are encoded in the native encoding of the machine
# and then re-encoded back into the native encoding for Perl.
sub callFunctionInSafeWayForI18N
{
    my ($functionPointer, @argument) = @_;
    my $processedArgument;

    my $encoding = mexGetEncoding();

    # If for some reason we can't determine encoding, then call the function 
    # without all the encoding/decoding.
    if ($encoding) {
        my @decodedArgument;
        
        if ($#argument > 0) {
            @decodedArgument = map(decode($encoding, $_),@argument);
        } else {
            @decodedArgument = decode($encoding, $argument[0]);
        }
        
        my $processedAndDecodedArgument = $functionPointer->(@decodedArgument);
        $processedArgument = encode($encoding, $processedAndDecodedArgument);
    } else {
        $processedArgument = $functionPointer->(@argument);
    }
    
    return $processedArgument;
}

# Perl has a limitation that you can't call a reference to a builtin function.
# So this wrapper works around that limitation.
sub mexUC {
    return uc($_[0])
}

# Return MATLAB preferences directory.  This should be as close a match to
# MATLAB's PREFDIR function as possible
sub getUserProfileDir
{
    my $userProfilerDir = $ENV{"MATLAB_PREFDIR"};

    # if there was no environment variable, use the product default
    if ( $userProfilerDir eq "" ) {
        # Windows Application Data (APPDATA).  This might be in a different language.
        my $appData = Win32::GetFolderPath(Win32::CSIDL_APPDATA);
        
        if ($appData eq "") {
            $appData = $ENV{'SystemRoot'} . "Application Data";
        }
        
        if (getArch() eq "win64") {
            my $SystemRoot = $ENV{'SystemRoot'};
            $SystemRoot =~ s|\\|\\\\|;
            $appData =~ s|^($SystemRoot\\)system32|$1Sysnative|;
            if (!-e $appData) {
                die("\nError: The MATLAB preference directory could not be reliably determined.\n" .
                    "       The Microsoft hotfix #942589 refering to Sysnative should fix this\n" .
                    "       problem.\n\n");
            }
        }

        $userProfilerDir = mexCatdir($appData, "MathWorks", "MATLAB", getVersion());
    }

    return $userProfilerDir;
}

# Return path to utilities directory which stores version, MEX help text, etc.
sub getUtilitiesDirectory
{
    my $matlabroot  = $0;
    $matlabroot =~ s|[\\/]mex\.pl$||;
    return mexCatdir($matlabroot,"util");
}

# Return MATLAB Release string.
sub getVersion
{
    my $versionFileName = mexCatfile(getUtilitiesDirectory(),"mex","version.txt");
    open(verDat, $versionFileName);
    my $ver=<verDat>;
    close(verDat);
    chomp($ver);
    return $ver;
}

# Return MATLAB architecture.  Should match the output of MATLAB's COMPUTER function.
sub getArch
{
    my $archFileName = mexCatfile(getUtilitiesDirectory(),"arch.bat");
    # Call arch.bat and print env BINARCH using set.
    my $arch =`"$archFileName" && set BINARCH`;
    # Strip the "BINARCH=" from the result of the command above.
    $arch =~ s\^BINARCH=\\;
    chomp($arch);
    return $arch;
}

# Location of the Supported and Compatible Compiler List.
sub mexSupportedCompilerListLocation
{
    my $printAsHotlink = $_[0];
    my $version = getVersion();
    my $arch = getArch();
    my $url = "http://www.mathworks.com/support/compilers/$version/$arch.html";
    
    if ($printAsHotlink) {
        $url = "<a href=\"matlab:web('$url','-browser')\">$url</a>";
    }
    return $url;
}

# Compiler deprecation warning string
sub mexDeprecationWarning
{
   my $compilerName = $_[0];
   my $supportedCompilerListLocation = mexSupportedCompilerListLocation;
   return "\n***************************************************************************\n" .
          "  Warning: Support for $compilerName will be discontinued in a \n" .
          "           future release, at which time new versions will be supported. \n" .
          "           For a list of currently supported compilers see: \n" . 
          "           $supportedCompilerListLocation\n" .
          "***************************************************************************\n";
}

# This function looks up a string in the Windows registry. The first
# argument is a Registry key, and the second is a value name to
# look up under that key. The return argument is the corresponding
# value data, or an empty string if the key of value name are not
# found.
sub registry_lookup
{
    my ($key, $name) = @_;
    my $data;
    my $hkey = Win32::TieRegistry->new("HKEY_LOCAL_MACHINE/" . $key,
                                       {Access=>"KEY_READ", Delimiter=>"/"});
    if ($hkey) {
        $data = $hkey->GetValue($name);
    }
    
    return $data ? $data : ""
}

# Get the encoding set in the registry in a format that the Encode.pm library prefers.
sub mexGetEncoding
{
    my $codepage = registry_lookup("SYSTEM/CurrentControlSet/Control/Nls/CodePage","ACP") ||
                   registry_lookup("SYSTEM/CurrentControlSet/Control/Nls/CodePage","OEMCP");
    if (!$codepage || !$codepage =~ m/^[0-9a-fA-F]+$/s) {
        return;
    } else {
        return "cp" . lc($codepage);
    } 
}
