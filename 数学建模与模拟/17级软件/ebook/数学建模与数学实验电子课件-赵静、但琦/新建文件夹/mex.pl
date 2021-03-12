#
#  Name:
#     mex        Perl script for PC only.
# 
#     mex        compilation program for MATLAB C/C++ and Fortran
#                language MEX-files
#
#  Usage:
#      Use mex -h to see usage.
#
#  Description:
#     This Perl program provides functionality for MEX. 
#     
#  Options:
#     See the 'describe' subroutine below for the MEX options.
#
#  Options (undocumented):
#
#     -setup:$compiler[:$optionfile_type]
#
#           $compiler must be taken from the option file name:
#
#             <compiler>[<optionfile_type>]opts.bat  (mex)
#
#           Currently, <optionfile_type> = 'engmat' for mex only.
#
#     -f $destination
#
#           Where to put the options file. $destination must
#           be $dir/$file where at least $dir exists and is
#           writable. It can be used only with -setup. If
#           not used the file is put in the default location:
#
#           PC: 
#           --
#
#           <UserProfile>\Application Data\MathWorks\MATLAB\R<version>
#
#           where
#
#             <UserProfile>    Is the value determined by Perl
#                              subroutine getUserProfileDir
#
#             <version>        MATLAB Release number like 14.
#
#           UNIX/Linux/Mac: 
#           --------------
#
#          $HOME/.matlab/R<version>
#
#           where
#
#             <version>        MATLAB Release number like 14.
#
#  Option files:
#
#     mex:    $MATLAB\bin\$ARCH\mexopts\*.stp
#             $MATLAB\bin\$ARCH\mexopts\*.bat
#
#             *opts.bat        files are 'installed' by -setup.
#             *engmatopts.bat  files are arguments using -f only.
#
#  Call structure:
#
#     mex.pl
#        -> mexsetup.pm
#           MEX:
#              -> mexopts/<compiler>opts.stp
#                 (compiler == msvc50 || msvc60)
#                    -> msvc_modules_installer.pm 
#              -> mexopts/<compiler>engmatopts.bat
#
# Copyright 1984-2014 The MathWorks, Inc.
#__________________________________________________________________________
#
#=======================================================================
require 5.008_008;

sub tool_name
{
    #===================================================================
    # tool_name: Returns the tool name, i.e. mex
    #===================================================================
    
    "mex";
    
}
#=======================================================================

use File::DosGlob 'glob';
use File::Basename;
use File::Path;
use File::Copy;
use File::Temp qw/ tempdir/;
use Cwd;

BEGIN
{
    $main::cmd_name = $0;

    $main::cmd_name = File::Spec->canonpath($main::cmd_name);
    $main::cmd_name =~ s%\.*[^\\\.][^\\]*\\+\.\.(\\|$)%%g; # xxx\dir\..\yyy --> xxx\yyy
    $main::cmd_name = Win32::GetShortPathName($main::cmd_name);

    (my $unused, $main::script_directory) = fileparse($main::cmd_name);
    ($main::matlabroot = $main::cmd_name) =~ s%\\bin\\mex.pl$%%;

    $main::cmd_name = uc($main::cmd_name);

    push(@INC, $main::script_directory);
}
#=======================================================================
END{
    #===================================================================
    # This block is executed at the end of execution of mex.pl
    #===================================================================
    if ($main::temp_dir) {
     
        my $savedErrorStatus = $?;

        # We need to use the system version of RMDIR because the Perl
        # RMTREE function does not handle being run out of a Unicode path.
        # Call RMDIR trhough CMD to ensure we are using the system version
        system("cmd /c rmdir /Q /S \"$main::temp_dir\"");

        $? = $savedErrorStatus;
    }
}

#=======================================================================

use mexsetup;
use mexutils;

require "shellwords.pl";  # Found in $MATLAB/sys/perl/win32/lib
                          # This is necessary to break up the text in
                          # the file into shell arguments. This is used
                          # to support the @<rspfile> argument.

if ( ( $ENV{'PROCESSOR_ARCHITECTURE'} eq "AMD64" ) ||
     ( $ENV{'PROCESSOR_ARCHITEW6432'} eq "AMD64" ) ) {
    if ( -f  mexCatfile($main::matlabroot, "bin", "win64", "matlab.exe") ) {
        $ARCH = "win64";
    } elsif (-f mexCatfile($main::matlabroot, "bin", "win32", "matlab.exe") ) {
        $ARCH = "win32";
    } else {
        $ARCH = "UNKNOWN";
    }
} elsif ( $ENV{'PROCESSOR_ARCHITECTURE'} eq "x86" ) {
    $ARCH = "win32";
} else {
    $ARCH = "UNKNOWN";
}

# Support command line override
if (grep /^-win32$/, @ARGV) {
    $ARCH = "win32";
}

$ENV{'ARCH'} = $ARCH;       

########################################################################
#=======================================================================
# Common subroutines:
#=======================================================================
#
# compile_files:             Compile files and form list of files to
#                            link.
# compile_resource:          Compile the resource.
# do_setup:                  Do only the setup.
# emit_compile_step:         Output compile step to makefile.
# emit_delete_resource_file: Output delete resource file to makefile.
# emit_link_dependency:      Output link dependency to makefile.
# emit_linker_step:          Output linker step to makefile.
# emit_makedef:              Output makedef step to makefile.
# emit_makefile_terminator:  Output terminator for makefile.
# emit_pre_or_postlink_step: Output postlink step to makefile.
# emit_resource_compiler:    Output resource compile step to makefile.
# emit_resource_linker_step: Output resource linker step to makefile.
# expand_wildcards:          Expand possible wildcards in the arguments
#                            for perl >= 5.00503
# expire:                    Die but with cleanup.
# find_options_file:         Find the options file.
# fix_common_variables:      Fix common variables.
# fix_flag_variables:        Fix the flag variables.
# files_to_remove:           Add files to remove list.
# getUserProfileDir          Returns UserProfile directory
# init_common:               Common initialization.
# linker_arguments:          Create response file of linker arguments or
#                            just string.               
# link_files:                Link files.
# options_file:              Get options file if not passed as an
#                            argument. Source the options file.
# parse_common_dash_args:    Parse the common dash arguments.
# parse_common_nodash_args:  Parse the common non-dash arguments.
# pre_or_postlink:           Do prelink or postlink steps based on input.
# process_env_assignments:   Process environment variable assignments.
# process_response_file:     Run shellwords on filename argument.
# rectify_path:              Check path for system directories and add
#                            them if not present.
# resource_linker:           Run resource linker.
# RunCmd:                    Run a single command.
# search_path:               Search DOS PATH environment for $binary_name
#                            argument
# set_common_variables:      Set more common variables.
# smart_quote:               Add quotes around strings with space.
# remove_quotes:             Remvoe quotes from strings with quotes
# start_makefile:            Open and write the main dependency to the
#                            makefile.
# tool_name:                 Returns the tool name, i.e. mex. This 
#                            function is defined at the top of the script since
#                            it is used in the BEGIN block.
#
#-----------------------------------------------------------------------
#
# Common variables:
#
#   perl:
#
#     FILES_TO_REMOVE
#     FILES_TO_LINK
#     FLAGS
#     LINKFLAGS
#     MAKEFILE
#
#   DOS environment:
#
#     PATH                      system path
#     MATLAB                    MATLAB root
#
#     [$ENV: get in script]
#       MEX_DEBUG               This is for debugging this script.
#
#     [$ENV: set in script]
#       LIB_NAME
#       MATLAB                  MATLAB root
#       MATLAB_BIN
#       MATLAB_EXTLIB
#       OUTDIRN
#       OUTDIR
#       OUTDIR_LONGPATH
#       RES_NAME
#       RES_PATH
#  
#=======================================================================
sub compile_files
{
    #===================================================================
    # compile_files: Compile files and form list of files to link.
    #===================================================================

    # Loop over @FILES to compile each file.  Keep files we actually
    # compile separate from the ones we don't compile but need to link.
    # This way, we can later clean up all .obj files we created.
    #
    my $file;

    for (;$file = shift(@FILES);) {
        my ($FILEDIR, $FILENAME, $FILEEXT) = fileparts($file);

        if ($FILEEXT =~ /($COMPILE_EXTENSION)$/i ) {
            my ($target_name, $name_arg);
            if ($NAME_OBJECT) {
                if (!$compile_only) {
                    $target_name = mexCatfile($main::temp_dir, "$FILENAME.obj");
                } else {
                    $target_name = mexCatfile($ENV{'OUTDIR'}, "$FILENAME.obj");
                }
                $name_arg = $NAME_OBJECT . smart_quote($target_name);
            }
            else {
                $target_name = "$FILENAME.obj";
                $name_arg = "";
            }

            # The Watcom doesn't handle Long File Names well.
            if ($COMPILER =~ /wcl386/) {
                $file = mexGetShortPathName($file, 1);
            }

            # Create arguments to pass $COMPILER.
            my $args = "$ARG_FLAGS $COMPFLAGS $name_arg $FLAGS " . smart_quote($file);

            if (!$makefilename)
            {
                my $messages = RunCmd("$COMPILER $args");

                # Check for error; $? might not work, so also check for resulting file
                if ($? != 0 || !(-e remove_quotes($target_name) || $main::no_execute)) {
                    print "$messages" unless $verbose; # verbose => printed in RunCmd
                    expire("Error: Compile of '$file' failed.");
                }
                if (!$compile_only)
                {
                    push(@FILES_TO_REMOVE, "$target_name");
                }
            }
            else
            {
                emit_compile_step();
            }

            push(@FILES_TO_LINK, "$LINK_FILE " . smart_quote($target_name));
            push(@FILES_TO_LINK_BASE, smart_quote($target_name));
        }
        elsif ($FILEEXT =~ /lib$/i)
        {
            push(@FILES_TO_LINK, "$LINK_LIB " . smart_quote($file));
            push(@FILES_TO_LINK_BASE, smart_quote($file));
        }
        else
        {
            push(@FILES_TO_LINK, "$LINK_FILE " . smart_quote($file));
            push(@FILES_TO_LINK_BASE, smart_quote($file));
        }
    }
}
#=======================================================================
sub compile_resource
{
    #===================================================================
    # compile_resource: Compile the resource.
    #===================================================================

    my ($rc_line) = '';
    
    my $rc_basename = mexCatfile($ENV{'RES_PATH'}, $ENV{'RES_NAME'});
    $rc_line .= " " . smart_quote("$rc_basename.rc");

    if (!$makefilename)
    {
        my $messages = RunCmd("$RC_COMPILER $rc_line");

        # Check for error; $? might not work, so also check for string "error"
        #
        if ($? != 0 || $messages =~ /\b(error|fatal)\b/i) {
            print "$messages" unless $verbose; # verbose => printed out in RunCmd
            expire("Error: Resource compile of '$ENV{'RES_NAME'}.rc' failed.");
        }
        push(@FILES_TO_REMOVE, "$rc_basename.res");
    }
    else
    {
        emit_resource_compiler();
    }
    
    push(@FILES_TO_LINK, smart_quote("$rc_basename.res"));
}
#=======================================================================
sub do_setup
{
    #===================================================================
    # do_setup: Do only the setup.
    #===================================================================

    my $setupFailure;
    
    if ($setup) { 
        @setup_args = ();
        # 4th arg is 0 == no automode
        $setupFailure = setup(tool_name(), $main::mexopts_directory, 
                  ['ANY'], 0, getUserProfileDir(), \@setup_args, $reglibs, $called_from_matlab); 
    } else {
        # 4th arg is 2 == full automode
        $setupFailure = setup(tool_name(), $main::mexopts_directory, 
            ['ANY'], 2, getUserProfileDir(), \@setup_args, $reglibs, $called_from_matlab);
    }
    
    if (!$setupFailure) {
        describeLargeArrayDimsWarning($called_from_matlab);
    }

    if ($setupFailure) {
        exit(1);
    }

}
#=======================================================================
sub emit_compile_step
{
    #===================================================================
    # emit_compile_step: Output compile step to makefile.
    #===================================================================

    # Emit compile dependency rule
    #
    print MAKEFILE smart_quote($target_name) . " : " . smart_quote($file);
    print MAKEFILE "\n\t$COMPILER $args\n\n";
}
#=======================================================================
sub emit_delete_resource_file
{
    #===================================================================
    # emit_delete_resource_file: Output delete resource file to makefile.
    #===================================================================

    my $res_pathname = mexCatfile($ENV{'OUTDIR'},"$ENV{'RES_NAME'}.res");

    print MAKEFILE "\tif exist \"$res_pathname\" del \"$res_pathname\"\n";
}
#=======================================================================
sub emit_link_dependency
{
    #===================================================================
    # emit_link_dependency: Output link dependency to makefile.
    #===================================================================

    # Emit link dependency rule
    #
    print MAKEFILE mexCatfile($ENV{'OUTDIR'}, "$ENV{'MEX_NAME'}.$bin_extension");
    print MAKEFILE " : @FILES_TO_LINK_BASE\n";
}
#=======================================================================
sub emit_linker_step
{
    #===================================================================
    # emit_linker_step: Output linker step to makefile.
    #===================================================================

    print MAKEFILE "\t$LINKER $ARGS\n";
}
#=======================================================================
sub emit_makedef
{
    #===================================================================
    # emit_makedef: Output makedef step to makefile.
    #===================================================================

    print MAKEFILE "\t$makedef\n";
}
#=======================================================================
sub emit_makefile_terminator
{
    #===================================================================
    # emit_makefile_terminator: Output terminator for makefile.
    #===================================================================

    print MAKEFILE "\n";
}
#=======================================================================
sub emit_pre_or_postlink_step
{
    #===================================================================
    # emit_pre_or_postlink_step: Output prelink or postlink step to makefile.
    #===================================================================
    my ($step) = @_;
    
    print MAKEFILE "\t$step\n";
}

#=======================================================================
sub emit_resource_compiler
{
    #===================================================================
    # emit_resource_compiler: Output resource compile step to makefile.
    #===================================================================

    print MAKEFILE "\t$RC_COMPILER $rc_line\n";
}
#=======================================================================
sub emit_resource_linker_step
{
    #===================================================================
    # emit_resource linker_step: Output resource linker step to makefile
    #===================================================================

    print MAKEFILE "\t$RC_LINKER $rc_line\n";
}
#=======================================================================
sub expand_wildcards
{
    #===================================================================
    # expand_wildcards: Expand possible wildcards in the arguments
    #===================================================================

    my (@a) = map { /\*/ ? glob($_) : $_ } @ARGV;
    if ( "@a" ne "@ARGV" ) {
        @ARGV = @a;
    }
}
#=======================================================================
sub expire
{
    #===================================================================
    # expire: Issue message and exit. This is like "die" except that
    #         it cleans up intermediate files before exiting.
    #         expire("normally") exits normally (doesn't die).
    #===================================================================

    # Clean up compiled files, unless we're only compiling
    #
    unlink @FILES_TO_REMOVE;

    if ($makefilename)
    {
        close(MAKEFILE);
        if ($_[0] ne "normally")
        {
            unlink $makefilename;
        }
    }

    die "\n  $main::cmd_name: $_[0]\n\n" unless ($_[0] eq "normally");
    exit(0);
}
#=======================================================================
sub find_options_file
{
    #===================================================================
    # find_options_file: Find the options file.
    #===================================================================

    # inputs:
    #
    my ($OPTFILE_NAME, $OPTFILE_LONGNAME, $language, $no_setup) = @_;

    # outputs: ($OPTFILE_NAME,$OPTFILE_LONGNAME,$source_dir,$sourced_msg)
    #
    my ($source_dir, $sourced_msg);

    # locals:
    #
    my ($REGISTERED_COMPILER, @JUNK);

    if (-e remove_quotes(mexCatfile(File::Spec->curdir(), $OPTFILE_NAME)))
    {
        chop($source_dir = `cd`);
    }
    elsif (-e remove_quotes(mexCatfile(getUserProfileDir(), $OPTFILE_NAME)))
    {
        $source_dir = getUserProfileDir();
    }
    elsif (-e remove_quotes(mexCatfile($main::mexopts_directory, $OPTFILE_NAME)))
    {
        $source_dir = "$main::mexopts_directory";
    }
    else
    {
        my $setupFailure = 0;
        if (!$no_setup)
        {                        
            # Not a preset so create an empty setup argument list
            # 
            @setup_args = ();

            # No options file found, so try to detect the compiler
            #
            if($silent_setup)
            {
                $setupFailure = setup(tool_name(), $main::mexopts_directory, [uc($lang)], 
                       2, getUserProfileDir(), \@setup_args, undef, $called_from_matlab); # 2 == silent automode
            }
            else
            {
                $setupFailure = setup(tool_name(), $main::mexopts_directory, [uc($lang)],
                      1, getUserProfileDir(), \@setup_args, undef, $called_from_matlab); # 1 == automode
            }
            
            if (!$setupFailure) {
                describeLargeArrayDimsWarning($called_from_matlab);
            }
        }

        if (-e remove_quotes(mexCatfile(getUserProfileDir(), $OPTFILE_NAME)))
        {
            $source_dir = getUserProfileDir();
        }
        elsif ($setupFailure)
        {
            exit(1);
        }
        else
        {
            expire("Error: No compiler options file could be found\n" .
                   "  to compile source code. Please run \"" . tool_name() . " -setup\" to rectify.");
        }
    }
    $OPTFILE_LONGNAME = mexCatfile($source_dir, $OPTFILE_NAME);
    $OPTFILE_NAME = $OPTFILE_LONGNAME;
    $sourced_msg = "-> Default options filename found in $source_dir";

    ($OPTFILE_NAME, $OPTFILE_LONGNAME, $source_dir, $sourced_msg);
}
#=======================================================================
sub fix_common_variables
{
    #===================================================================
    # fix_common_variables: Fix common variables.
    #===================================================================

    $bin_extension = $NAME_OUTPUT;
    $bin_extension =~ s/\"//g;
    $bin_extension =~ s/.*\.([^.]*)$/$1/;

    # Decide how to optimize or debug
    #
    if (! $debug) {                                  # Normal case
        $LINKFLAGS = "$LINKFLAGS $LINKOPTIMFLAGS";
    } elsif (! $optimize) {                          # Debug; don't optimize
        $LINKFLAGS = "$LINKDEBUGFLAGS $LINKFLAGS";
    } else {                                         # Debug and optimize
        $LINKFLAGS = "$LINKDEBUGFLAGS $LINKFLAGS $LINKOPTIMFLAGS ";
    }

    $FLAGS = "$FLAGS -DMX_COMPAT_32" if ( $v7_compat eq "yes" );
}
#=======================================================================
sub fix_flag_variables
{
    #===================================================================
    # fix_flag_variables: Fix the flag variables.
    #===================================================================

    # Based on the language we're using, possibly adjust the flags
    # 
    if ($lang eq "cpp" && $CPPCOMPFLAGS ne "")
    {
        $COMPFLAGS = $CPPCOMPFLAGS;
        $LINKFLAGS = "$LINKFLAGS $CPPLINKFLAGS";
        $DEBUGFLAGS = $CPPDEBUGFLAGS;
        $OPTIMFLAGS = $CPPOPTIMFLAGS;
    }
}
#=======================================================================
sub files_to_remove
{
    #===================================================================
    # files_to_remove: Add files to remove list.
    #===================================================================

    push(@FILES_TO_REMOVE,
         ("$ENV{'MEX_NAME'}.bak"));
}

#=======================================================================

sub init_common
{
    #===================================================================
    # init_common: Common initialization.
    #===================================================================

    $ENV{'MATLAB'} = $main::matlabroot;

    expand_wildcards();

    $sourced_msg = 'none';

    $| = 1;                              # Force immediate output flushing
    open(STDERR,">&STDOUT");             # redirect stderr to stdout for matlab
    select((select(STDERR), $|=1 )[0]);  # force immediate flushing for STDERR

    # Fix the path if necessary.
    #
    rectify_path();

    # Trap case where an invalid options file is used, by checking the
    # value of the compiler.
    #
    $COMPILER = "none";

    # Ensure options file longname is always defined.
    $OPTFILE_LONGNAME = "";

    # Create a temporary directory for temporary files
    #  tempdir will be deleted on exit even if perl script exits early
    if ($ENV{'TEMP'} && -d $ENV{'TEMP'} && -w $ENV{'TEMP'})
    {
        $main::temp_dir = tempdir( tool_name() . "_" . "XXXXXX", DIR => $ENV{'TEMP'}) or
            expire("Error: Could not create directory \"$main::temp_dir\": $!.");
        # Now that we've created a directory, refer to it by its short name.
        $main::temp_dir = mexGetShortPathName($main::temp_dir);
    }
    else
    {
        if ($ENV{'TEMP'} && -d $ENV{'TEMP'} . " " && -w $ENV{'TEMP'} . " ") {
            # This case relies on a bug in the way Perl file test operators handle
            # Shift-JIS 5c character in TEMP.  If they pass the above tests then they
            # likely contain one of these characters.
            expire("Error: " . uc(tool_name()) . " failed to create a temporary\n" .
                   "      directory.  The directory \"$ENV{'TEMP'}\"\n" .
                   "      defined by the environment variable %TEMP% may contain a \n" .
                   "      problematic Shift-JIS character.  Consider changing %TEMP% \n" .
                   "      to another writable directory, for example \"C:\\temp\".");
        } else {
            expire("Error: " . uc(tool_name()) . " failed to create a temporary\n" .
                   "      directory.  The directory \"$ENV{'TEMP'}\"\n" .
                   "      defined by the environment variable %TEMP% either does not exist \n" .
                   "      or is not writable.  Consider changing %TEMP% to a writable directory, \n" .
                   "      for example \"C:\\temp\".");
       }
    }
}

#=======================================================================
sub linker_arguments
{
    #===================================================================
    # linker_arguments: Create response file of linker arguments or just
    #                   string.
    #===================================================================

    # NAME_OUTPUT always goes in the list, but it may be blank (in which
    # case it's harmless to put it in).  Leaving the variable blank is
    # equivalent to assuming that the output will be named after the
    # first object file in the list.
    #

    $ARGS = '';
    if ( $ENV{'RSP_FILE_INDICATOR'} )
    {
        my $response_file;
        if ($makefilename)
        {
            $response_file = mexCatfile($ENV{'OUTDIR'}, "$ENV{'MEX_NAME'}_master.rsp");
        }
        else
        {
            $response_file = mexCatfile($main::temp_dir,
                                                 tool_name() . "_tmp.rsp");
        }
        open(RSPFILE, ">$response_file") || expire("Error: Can't open file '$response_file': $!");

        # The Watcom linker doesn't like things quoted with double quotes--it wants single quotes.
        if ($COMPILER =~ /wcl386/) {
            my @nl = map { $_ =~ s|"|'|g; $_ } @FILES_TO_LINK;
            @FILES_TO_LINK = @nl;
        }

        print RSPFILE " @FILES_TO_LINK";
        close(RSPFILE);

        # The Watcom linker can't handle @ in the output name, unless it is "escaped" with single quotes.
        if ($COMPILER =~ /wcl386/) {
            $NAME_OUTPUT =~ s|(name\s+)(.*)|$1'$2'|;
        }
        # The lcc linker can't handle paths with spaces.
        if ($COMPILER =~ /lcc/ && ($outdir_flag || $output_flag)) {
            my ($flag, $path, $name) = $NAME_OUTPUT =~ m|^([^"]*")(.+)([\\/].*")$|;
            if ($path) {
                $path = mexGetShortPathName($path, 1);
                $NAME_OUTPUT = $flag . $path . $name;
            }
        }
        

        $IMPLICIT_LIBS = getValidInputLinkLibraries();

        $ARGS = "$NAME_OUTPUT $LINKFLAGS " .
                "$ENV{'RSP_FILE_INDICATOR'}" .
                smart_quote(mexGetShortPathName($response_file)) .
                " $IMPLICIT_LIBS $LINKFLAGSPOST";

        # The Watcom linker doesn't like things quoted with double quotes--it wants single quotes.
        if ($COMPILER =~ /wcl386/) {
             $ARGS =~ s|"|'|g;
        }

        if ($verbose && !$makefilename)
        {
            print "    Contents of $response_file:\n";
            print " @FILES_TO_LINK\n\n";
        }
    }
    else
    {
        $IMPLICIT_LIBS = getValidInputLinkLibraries();
        $ARGS = "$NAME_OUTPUT $LINKFLAGS @FILES_TO_LINK $IMPLICIT_LIBS $LINKFLAGSPOST";
    }
}


#=======================================================================
sub getValidInputLinkLibraries
{
    #===================================================================
    # getSpecifiedImplicitLibraries: Search for library names passed 
    # in using -l to link against.  Returns a list of valid libraries 
    # with full paths.  This is designed to behave similar to GCC.
    #===================================================================
    
    # Generate a list of Library Paths to search in.
    my $libPath = $ENV{'LIB'};
    my @libPaths = split(/;/,$libPath);
    # The full list is:
    # 1) The directories specified in environment variable LIB (usually set by
    #    compiler and system configuration)
    # 2) The environment variable LIBLOC usually set in options files pointing
    #    to MathWorks generated link libraries.
    # 3) Directories specified at the command line using -L, and stored in
    #    INPUT_IMPLICIT_LIB_DIRS.
    @libPaths = (@libPaths, $ENV{'LIBLOC'}, @INPUT_IMPLICIT_LIB_DIRS);

    # Loop over all the libraries passed in using -l.
    foreach my $libraryName (@INPUT_IMPLICIT_LIBS) {
        my $windowsStyleFilename = $libraryName . ".lib";
        my $unixStyleFilename = "lib" . $libraryName . ".lib";            
        my $foundLibrary = 0;

        # Loop over all the libraries paths.        
        foreach my $libraryDir (@libPaths) {
            my $windowsStyleFullname = mexCatfile($libraryDir, $windowsStyleFilename);
            my $unixStyleFullname = mexCatfile($libraryDir, $unixStyleFilename);
            
            # If library exists add it to the list of libraries to link against.
            if (-e remove_quotes($windowsStyleFullname)) {
                $IMPLICIT_LIBS .= " " . smart_quote($windowsStyleFullname);
                $foundLibrary = 1;
            } elsif (-e remove_quotes($unixStyleFullname)) {
                $IMPLICIT_LIBS .= " " . smart_quote($unixStyleFullname);
                $foundLibrary = 1;
            }
            if ($foundLibrary) {
                # Break out of loop so that only the first found library is used.
                last;
            }
        }

        # If an input library is not found in any of the library paths then
        # issue warning and do not try to link against it.
        if (!$foundLibrary) {
            $string = join("\n               ",@libPaths);
            print "\nWarning: " . uc(tool_name()) . " could not find the library \"$libraryName\" specified with -l option." .
                  "\n         " . uc(tool_name()) . " looked for a file with one of the names:" .
                  "\n               $windowsStyleFilename" .
                  "\n               $unixStyleFilename" .
                  "\n         " . uc(tool_name()) . " looked for the library in the following directories:" .
                  "\n               $string" .
                  "\n\n";       
        }
    }

    return $IMPLICIT_LIBS;
}

#=======================================================================
sub link_files
{
    #===================================================================
    # link_files: Link files.
    #===================================================================

    if (!$makefilename) {
        my $messages = RunCmd("$LINKER $ARGS");
        my $output_pathname = mexCatfile($ENV{'OUTDIR'}, "$ENV{'MEX_NAME'}.$bin_extension");

        # LCC doesn't pay attention to -"output dir\file" as an option
        # it puts the file into the current directory.  If that's the case
        # move the file to dir
        my $output_pathname = mexCatfile($ENV{'OUTDIR'}, "$ENV{'MEX_NAME'}.$bin_extension");
        my $output_libpathname = mexCatfile($ENV{'OUTDIR'}, "$ENV{'MEX_NAME'}.lib");
        if (($ENV{'COMPILER'} eq "lcc") &&
            !(-e remove_quotes($output_pathname)) &&
            (-e remove_quotes("$ENV{'MEX_NAME'}.$bin_extension"))) {
      
            print "    Renaming $ENV{'MEX_NAME'}.$bin_extension to $output_pathname\n" if $verbose;
            rename("$ENV{'MEX_NAME'}.$bin_extension", $output_pathname) == 1 ||
            expire("Error: Rename of '$output_pathname' failed: $!");
            
            print "    Renaming $ENV{'MEX_NAME'}.lib to $output_libpathname\n" if $verbose;
            rename("$ENV{'MEX_NAME'}.lib", $output_libpathname) == 1 ||
            expire("Error: Rename of '$output_libpathname' failed: $!");
        }

        # Check for error; $? might not work, so also check for resulting file
        if ($? != 0 || !(-e remove_quotes($output_pathname) || $main::no_execute )) {
            print "$messages" unless $verbose; # verbose => printed in RunCmd
            expire("Error: Link of '$output_pathname' failed.");
        }

        # If we got a file, make sure there were no errors
        if ($messages =~ /\b(error|fatal)\b/i) {
            print $messages unless $verbose; # verbose => printed in RunCmd
            expire("Error: Link of '$output_pathname' failed.");
        }
    } else {
        emit_linker_step();
    }
}

#=======================================================================
sub qa_should_use_testing_setup
{
    #===================================================================
    # MATHWORKS ONLY
    # qa_should_use_testing_setup: Check for test environment and a
    #                              compiler that requires extra
    #                              setup for internal testing purposes
    #===================================================================

    my ($OPTFILE_LONGNAME, $optfilePattern, $altEnvVar) = @_;
    return ($OPTFILE_LONGNAME =~ /$optfilePattern/ && $ENV{$altEnvVar})
}

#=======================================================================
sub qa_use_testing_setup
{
    #===================================================================
    # MATHWORKS ONLY
    # qa_use_testing_setup: Use alternate environment variable to locate
    #                       compiler for internal testing purposes
    #===================================================================

    my ($mainEnvVar, $altEnvVar, $variantName) = @_;
    print("Setting $mainEnvVar for use with $variantName (MathWorks-only diagnostic - do not geck)\n");
    $ENV{$mainEnvVar} = $ENV{$altEnvVar};
}

#=======================================================================
sub options_file
{
    #===================================================================
    # options_file: Get options file if not passed as an argument.
    #               Source the options file.
    #===================================================================

    # MATHWORKS ONLY: MathWorks-specific environment variables 
    #                 used only for internal regression testing. 
    if (qa_should_use_testing_setup($OPTFILE_LONGNAME, 'intelf11msvs2008shell', 'MWE_VS90SHELL_COMNTOOLS') ||
        qa_should_use_testing_setup($OPTFILE_LONGNAME, 'intelf12msvs2008shell', 'MWE_VS90SHELL_COMNTOOLS')) {
        qa_use_testing_setup('VS90COMNTOOLS', 'MWE_VS90SHELL_COMNTOOLS', 
            'Microsoft Visual Studio 2008 Shell');
    }

    # Search and locate options file if not specified on the command
    # line.
    #
    if ($sourced_msg eq 'none') {
        ($OPTFILE_NAME, $OPTFILE_LONGNAME, $source_dir, $sourced_msg) = find_options_file($OPTFILE_NAME, $OPTFILE_LONGNAME, $lang, $no_setup);
    }

    # Parse the batch file. DOS batch language is too limited.
    #
    open (OPTIONSFILE, $OPTFILE_NAME) || expire("Error: Can't open file '$OPTFILE_NAME': $!");
    while ($_ = <OPTIONSFILE>) {
        chomp;
        next if (!(/^\s*set /i));     # Ignore everything but set commands
        s/^\s*set //i;                # Remove "set " command itself
        s/\s+$//;                     # Remove trailing whitespace
        s/\\$//g;                     # Remove trailing \'s
        s/\\/\\\\/g;                  # Escape all other \'s with another \
        s/%(\w+)%/'.\$ENV{'$1'}.'/g;  # Replace %VAR% with $ENV{'VAR'}
        s/%%/%/g;                     # Replace %%s with %s
        my $perlvar = '$' . $_ . "\';";
        $perlvar =~ s/=/='/;
        my $dosvar = '$ENV{'."'".$_."';";
        $dosvar =~ s/=/'}='/;
        eval($perlvar);
        eval($dosvar);

        # Watcom doesn't handle Long Path Names properly.
        if ($COMPILER =~ /wcl386/) {
            $MATLAB = mexGetShortPathName(remove_quotes($MATLAB), 1);
            $ENV{'MATLAB'} = $MATLAB;
        }
        $ML_DIR = smart_quote($MATLAB);

        # Set the special MATLAB_BIN environment variable
        #
        if ( (! $ENV{'MATLAB'} eq "") && $ENV{'MATLAB_BIN'} eq "" ) {
            $ENV{'MATLAB_BIN'} = mexCatdir($ML_DIR, "bin", $ARCH);
        }

        # Set the special MATLAB_EXTLIB environment variable
        #
        if ( (! $ENV{'MATLAB'} eq "") && $ENV{'MATLAB_EXT'} eq "" ) {
            $ENV{'MATLAB_EXTLIB'} = mexCatdir($ML_DIR, "extern", "lib", $ARCH);
        }
    }

    close(OPTIONSFILE);
    
    # Validate that the options file matches the target architecture
    if (($MW_TARGET_ARCH) && ($MW_TARGET_ARCH ne $ARCH)) {
        my $archMismatchBaseMessage = "\n" .
            "  Error: Using options file:\n" .
            "         $OPTFILE_NAME\n" .
            "         You cannot use this file with the " . uc($ARCH) . " architecture because it enables\n" .
            "         a compiler for a different architecture.\n";
        my $archMismatchFixMessage;
        if ($dashFused eq "yes") {
            $archMismatchFixMessage = 
            "         Choose a file that is compatible with the " . uc($ARCH) . " architecture."
        } else {
            $archMismatchFixMessage =
            "         Running ". tool_name() . " -setup may resolve this problem."
        }
        my $archMismatchMessage = $archMismatchBaseMessage . $archMismatchFixMessage;
        expire($archMismatchMessage);
    }
}
#=======================================================================
sub parse_common_dash_args
{
    #===================================================================
    # parse_common_dash_args: Parse the common dash arguments.
    #===================================================================

    local ($_) = @_;

    ARGTYPE: { 
      /^-c$/ && do {
          $compile_only = "yes";
          last ARGTYPE;
      };

      /^-D\S*$/ && do {
          $_ =~ s/[=\#]/=/;
          $ARG_FLAGS = "$ARG_FLAGS $_";
          last ARGTYPE;
      };

      /^-U\S*$/ && do {
          $ARG_FLAGS = "$ARG_FLAGS $_";
          last ARGTYPE;
      };

      /^-I(.*)$/ && do {
          $ARG_FLAGS .= " -I" . &smart_quote(mexGetShortPathName($1));
          last ARGTYPE;
      };

      # Look for libraries specified as -l<name> but continue to handle
      # -link and -lang options to mbuild correctly
      /^-l(.*)$/ && (($main::mbuild eq 'no') || (! /^-link$/ && ! /^-lang$/)) && do {
        push(@INPUT_IMPLICIT_LIBS, $1);
        last ARGTYPE;
      };

      /^-L(.*)$/ && do {
          push(@INPUT_IMPLICIT_LIB_DIRS, mexGetShortPathName($1));
          last ARGTYPE;
      };

      /^-f$/ && do {
        $dashFused = "yes";
        $filename = shift(@ARGV);
        if ("$setup_special" eq "yes") {
            $setup_args[2] = $filename;
            last ARGTYPE;
        }
        if (-e remove_quotes($filename)) {
            $OPTFILE_LONGNAME = $filename;
            $OPTFILE_NAME = mexGetShortPathName($OPTFILE_LONGNAME);
        } else {
            my $script_dir_filename = mexCatfile($main::mexopts_directory, $filename);
            if (-e remove_quotes($script_dir_filename)) {
                $OPTFILE_LONGNAME = $script_dir_filename;
                $OPTFILE_NAME = mexGetShortPathName($OPTFILE_LONGNAME);
            }
            else {
                expire("Error: Could not find specified options file\n    '$filename'.");
            }
        }
        $sourced_msg = '-> Options file specified on command line';
        last ARGTYPE;
      };

      # This is an undocumented feature which is subject to change
      #
      /^-silentsetup$/ && do {
          $silent_setup = "yes";
          last ARGTYPE;
      };

      /^-g$/ && do {
          $debug = "yes";
          last ARGTYPE;
      };

      # This is an undocumented feature which is subject to change.
      #
      /^-k$/ && do {
          $makefilename = shift(@ARGV);
          last ARGTYPE;
      };

      /^-setup$/ && do {
          $setup = "yes";
          last ARGTYPE;
      };

      /^-setup:.*$/ && do {
          $setup_special = "yes";
          s/-setup://;
          @setup_args = ($f1,$f2,$f3) = split(/:/);
          if (!$f1) {
              print "\nError: No compiler specified . . .\n\n";
              exit(1);
          }
          last ARGTYPE;
      };

      # This is passed by mex.m 
      #
      /^-called_from_matlab$/ && do {
          $called_from_matlab = "yes";
          last ARGTYPE;
      };

      /^-output$/ && do {
          $output_flag = "yes";
          $mex_name = shift(@ARGV);
          ($link_outdir, $mex_name, $mex_ext) = &fileparts($mex_name);
          $link_outdir = mexGetShortPathName($link_outdir);
          $ENV{'MEX_NAME'}=$mex_name;
          last ARGTYPE;
      };

      /^-O$/ && do {
          $optimize = "yes";
          last ARGTYPE;
      };

      /^-outdir$/ && do {
        $outdir_flag = "yes";
        my $outdir = shift(@ARGV);

        # Lots of compilers can't handle relative paths that start with @ marks.
        $outdir =~ s|^@|.\\@|;

        # Use OUTDIR for most uses as the most robust option.  OUTDIR_LONGPATH
        # can be used for mwregsvr where we want the long path and can handle
        # a quoted string.  This needs to NOT be processed through ShortPath.
        $ENV{'OUTDIR_LONGPATH'} = $outdir . "\\";

        # Use shortnames to handle direcories with spaces.  LCC needs this.
        $outdir = mexGetShortPathName($outdir);
        
        # Cannot use mexCatdir below since it strips the trailing backslash. 
        # The trailing backslashes are needed when %OUTDIR% used in mexopts files.
        $ENV{'OUTDIR'} = $outdir . "\\";

        last ARGTYPE;
      };

      /^-matlab$/ && do {
          $matlab = shift(@ARGV);
          $matlab =~ tr/"//d;
          $ENV{'MATLAB'} = mexGetShortPathName($matlab);
          last ARGTYPE;
      };

      /^-n$/ && do {
          $main::no_execute = 1; # global used by RunCmd
          last ARGTYPE;
      };

      # This is an undocumented feature which is subject to change
      #
      /^-no_setup$/ && do {
          $no_setup = 1;
          last ARGTYPE;
      };

      /^-win(32|64)$/ && do {
         $_ =~ s/-//;
         if ($ARCH ne $_) {
             printf("WARNING: \$ARCH ($ARCH) not set correctly [$_]\n");
         }
         last ARGTYPE;
      };

      return 0;
    }
    return 1;
}

#=======================================================================
sub parse_common_nodash_args
{
    #===================================================================
    # parse_common_nodash_args: Parse the common non-dash arguments.
    #===================================================================

    local ($_) = @_;

    ARGTYPE: {
        /^[A-Za-z0-9_]+[#=].*$/ && do {
            push(@CMD_LINE_OVERRIDES, $_);
            last ARGTYPE;
        };

      /^@(.*)$/ && do {
            if( -e remove_quotes($1) || !(-e remove_quotes($_)) ) {
                @NEW_ARGS = process_response_file($1);
    
                # Expand possible wildcards in the arguments 
                my (@a) = map { /\*/ ? glob($_) : $_ } @NEW_ARGS;
                @NEW_ARGS = @a;
                 
                unshift(@ARGV, @NEW_ARGS);
                last ARGTYPE;
            } 

        };

        return 0;
    }
    
    return 1;
}
#=======================================================================
sub pre_or_postlink
{
    #===================================================================
    # pre_or_postlink: Do prelink or postlink steps.
    #===================================================================

    # Note that error checking is not possible; we don't get a return
    # status, and there's no way of knowing a priori what each task is
    # supposed to do.
    
    my ($step_type_string) = @_;
    
    # Call any commands that may exist  
    my @steps = split(/;/, $ENV{$step_type_string});
    my $step;
    while ($step = shift(@steps)) {
        # Skip if $step is only whitespace
        next if (!($step =~ /\S/));
        $step =~ s%/%\\%g;
        if (!$makefilename)
        {
            RunCmd($step);
        }
        else
        {
            emit_pre_or_postlink_step($step);
        }
    }

    # There can be multiple steps called, for example, POSTLINK_CMDS1,
    # POSTLINK_CMDS2, etc. (where $step_type_string is "POSTLINK_CMDS").
    # So loop through dealing with each.
    $i = 1;
    $step = $ENV{$step_type_string . $i};
    while ($step && $step =~ /\S/)
    {
        if (!$makefilename)
        {
            RunCmd($step);
        }
        else
        {
            emit_pre_or_postlink_step($step);
        }
        $i++;
        $step = $ENV{$step_type_string . $i};
    }
}
#=======================================================================
sub process_env_assignments
{
    #===================================================================
    # process_env_assignments: Process environment variable assignments
    #===================================================================

    # Array passed in by reference, $ASSIGNMENTS is a reference to an
    # array.
    my $ASSIGNMENTS = shift;
    foreach my $override (@$ASSIGNMENTS)
    {
        next if (length($override) == 0);
        $override =~ /^([A-Za-z0-9_]+)[#=](.*)$/;
        $lhs = $1;
        $rhs = $2;

        $rhs =~ s/\\/\\\\/g;              # Escape all other \'s with another \
        $rhs =~ s/"/\\"/g;
        $rhs =~ s|\$(?!\w)|\\\$|g;         # Escape "$" if it's NOT a $ENV
        $rhs =~ s/\$(\w+)/\$ENV{'$1'}/g;  # Replace $VAR with $ENV{'VAR'}

        my $perlvar = '$' . $lhs . " = \"" . $rhs . "\";";
        my $dosvar = "\$ENV{\'" . $lhs . "\'} = \"" . $rhs . "\";";

        # Works around problems handling @-marks.
        $perlvar =~ s|\@|\\\@|g;
        $dosvar =~ s|\@|\\\@|g;

        eval($perlvar);
        eval($dosvar);
    }
}
#=======================================================================
sub process_response_file
{
    #===================================================================
    # process_response_file: Run shellwords on filename argument.
    #===================================================================

    # inputs:
    #
    my ($filename) = @_;

    # locals:
    #
    my ($rspfile);

    open(RSPFILE, $filename) || expire("Error: Can't open response file '$filename': $!");
    while (<RSPFILE>)
    {
        $rspfile .= $_;
    }
    close(RSPFILE);

    # shellwords strips out backslashes thinking they are escape sequences.
    # In DOS we'd rather treat them as DOS path separators.
    #
    $rspfile =~ s/\\/\\\\/g;

    # return output of shellwords
    #
    shellwords($rspfile);
}
#=======================================================================
sub rectify_path
{
    #===================================================================
    # rectify_path: Check path for system directories and add them if
    #               not present.
    #===================================================================
  
    # Fix for Windows NT/2000 systemroot bug
    #
    $ENV{'PATH'} =~ s/\%systemroot\%/$ENV{'systemroot'}/ig;

    # Make sure system path is on path so perl can spawn commands.
    # If %SystemRoot% is unavailable perl may still fail in a very
    # uninformative way.
    #
    my $systemdir = $ENV{'SystemRoot'};
  
    # if we got something make sure it's on the path
    #
    if($systemdir ne "")
    {
        # system32
        my $system32dir = mexCatdir($systemdir, "system32");
        if (index(lc($ENV{'PATH'}), lc($system32dir) . ";") < 0)
        {
            # $system32dir not found on path. Add it.
            $ENV{PATH} = $system32dir . ";" . $ENV{PATH};
        }

        # Root system dir (i.e. WINNT or WINDOWS)
        if (index(lc($ENV{PATH}), lc($systemdir) . ";") < 0)
        {
            # $systemdir not found, add to path
            $ENV{PATH} = $systemdir . ";" . $ENV{PATH};
        }
    }
    else
    {
        print "Warning: %SystemRoot% environment variable is not defined.\n";
    }
}
#=======================================================================
sub resource_linker
{
    #===================================================================
    # resource_linker: Run resource linker. 
    #===================================================================

    my $rc_line = smart_quote(mexCatfile($ENV{'RES_PATH'},"$ENV{'RES_NAME'}.rc")) . " " .
    smart_quote(mexCatfile($ENV{'OUTDIR'}, "$ENV{'MEX_NAME'}.$bin_extension"));

    if (!$makefilename)
    {
        my $messages = RunCmd("$RC_LINKER $rc_line");

        # Check for error; $? might not work, so also check for string "error"
        #
        if ($? != 0 || $messages =~ /\b(error|fatal)\b/i) {
            print "$messages" unless $verbose; # verbose => printed in RunCmd
            expire("Error: Resource link of '$ENV{'RES_NAME'}.rc' failed.");
        }

        push(@FILES_TO_REMOVE, mexCatfile($ENV{'OUTDIR'}, "$ENV{'RES_NAME'}.res"));
    }
    else
    {
        emit_resource_linker_step();
    }
}
#=======================================================================
sub RunCmd
{
    #===================================================================
    # RunCmd: Run a single command.
    #===================================================================

    my ($cmd) = @_;
    my ($rc, $messages);
    
    print "\n--> $cmd\n\n" if ($verbose || $main::no_execute);
    if (! $main::no_execute)
    {
        $messages = `$cmd`;
        $rc = $?;
        print $messages if $verbose;
        $rc = $rc >> 8 if $rc;
    }
    else
    {
        $messages = "";
        $rc = 0;
    }
    wantarray ? ($messages, $rc) : $messages;
}
#=======================================================================
sub search_path
{
    #===================================================================
    # search_path: Search DOS PATH environment variable for
    #              $binary_name.  Return the directory containing the
    #              binary if found on the path, or an empty path
    #              otherwise.
    #===================================================================

    my ($binary_name) = @_;
 
    foreach my $path_entry ( split(/;/,$ENV{'PATH'}) ) {
        my $filename = mexCatfile($path_entry, $binary_name);
        print "checking existence of:  $filename\n" if $ENV{MEX_DEBUG};
        if ( -e remove_quotes($filename) ) {
            print "search_path found: $filename\n" if $ENV{MEX_DEBUG};
            return $path_entry;
        }
    }
    '';
}
#=======================================================================
sub set_common_variables
{
    #===================================================================
    # set_common_variables: Set more common variables.
    #===================================================================

    #Only set OUTDIR env from -output if linking is happening.
    if (!$ENV{'OUTDIR'})
    {
        if (!$compile_only && $link_outdir ne "")
        {
            $ENV{'OUTDIR_LONGPATH'} = mexRel2abs($link_outdir) . "\\";
            $ENV{'OUTDIR'} = mexGetShortPathName(mexRel2abs($link_outdir)) . "\\";
        }
    }

    # Create a unique name for the created import library
    #
    $ENV{'LIB_NAME'} = mexCatfile($main::temp_dir, "templib");

    $RC_LINKER = " ";
    $RC_COMPILER = " ";

}
#=======================================================================
sub smart_quote
{
    #===================================================================
    # smart_quote: Adds quotes (") at the beginning and end of its input
    #              if the input contains a space. The quoted string is
    #              returned as the output. If the input contains no
    #              spaces, the input is returned as the output.
    #===================================================================

    my ($str) = @_;     # input

    $str = "\"$str\"" if ($str =~ / /);
    $str;               # output
}
#=======================================================================
sub remove_quotes
{
    #===================================================================
    # remove_quotes: Removes quotes (") from strings that contain quotes.
    #                The modified string is returned as the output. If
    #                the input contains quotes, the input is returned as
    #                the output.
    #===================================================================

    my ($str) = @_;     # input

    $str =~ s/"//g;
    $str;               # output
}
#=======================================================================
sub start_makefile
{
    #===================================================================
    # start_makefile: Open and write the main dependency to the makefile.
    #===================================================================

    open(MAKEFILE, ">>$makefilename")
        || expire("Error: Cannot append to file '$makefilename': $!");

    # Emit main dependency rule
    #
    print MAKEFILE "bin_target : " .
        mexCatfile($ENV{'OUTDIR'}, "$ENV{'MEX_NAME'}.$bin_extension") . "\n\n";
}
########################################################################
#=======================================================================
# Mex only subroutines:
#=======================================================================
#
# describe:                  Issues mex messages.
# fix_mex_variables:         Fix variables for mex. 
# init_mex:                  Mex specific initialization.
# parse_mex_args:            Parse all arguments including mex.
# set_mex_variables:         Set more variables for mex.
#
#-----------------------------------------------------------------------
#
# Mex variables:
#
#   Perl:
#
#     <none>
#
#   DOS environment:
#
#     <none>
#
#     [$ENV: set in script]
#       MEX_NAME                This is the target name
#       ENTRYPOINT              default is "mexFunction"
#
#     [$ENV: get in script]
#

#=======================================================================
sub printHelp
{
    #===================================================================
    # printHelp: Prints the help text for MEX
    #===================================================================

    my $mexScriptsDir = mexCatdir($main::script_directory,"util","mex");

    my $helpTextFileName = mexCatfile($mexScriptsDir,"mexHelp.txt");
    copy($helpTextFileName,\*STDOUT);
    
    print("\n");
}

#=======================================================================
sub describeLargeArrayDimsWarning
{
    #===================================================================
    # describeLargeArrayDimsWarning: Print message about 64-bit Array API
    #===================================================================
    my $wasCalledFromMatlab = $_[0];
    my $largeArrayDimsURLPart;

    my $largeArrayDimsURL = 'http://www.mathworks.com/help/matlab/matlab_external/upgrading-mex-files-to-use-64-bit-api.html ';

    if ($wasCalledFromMatlab) {
        $largeArrayDimsURLPart = "           <a href=\"matlab:web('$largeArrayDimsURL','-browser')\">$largeArrayDimsURL</a>\n";
    } else {
        $largeArrayDimsURLPart = "           $largeArrayDimsURL\n";
    }

    my $largeArrayDimsMsgPart1 =
         "**************************************************************************\n" .
         "  Warning: The MATLAB C and Fortran API has changed to support MATLAB\n" . 
         "           variables with more than 2^32-1 elements.  In the near future\n" .
         "           you will be required to update your code to utilize the new\n" . 
         "           API. You can find more information about this at:\n";

    my $largeArrayDimsMsgPart2 =
         "           Building with the -largeArrayDims option enables the new API.\n" .
         "**************************************************************************\n";
    
    print $largeArrayDimsMsgPart1;
    print $largeArrayDimsURLPart;
    print $largeArrayDimsMsgPart2;
    print "\n";
}

#=======================================================================
sub describe
{
    #===================================================================
    # describe: Issues mex messages. This way lengthy messages do not
    #           clutter up the main body of code.
    #===================================================================

    local($_) = $_[0];

 DESCRIPTION: {
     /^usage$/ && print(<<'end_usage') && last DESCRIPTION;
    Usage:
        MEX [option1 ... optionN] sourcefile1 [... sourcefileN]
            [objectfile1 ... objectfileN] [libraryfile1 ... libraryfileN]

    Use the -help option for more information, or consult the MATLAB API Guide.

end_usage
     /^invalid_options_file$/ && print(<<"end_invalid_options_file") && last DESCRIPTION;
  
  Error: An options file for MEX was found, but the value for 'COMPILER'
         was not set.  This could mean that the value is not specified
         within the options file, or it could mean that there is a 
         syntax error within the file.

end_invalid_options_file
     /^final_options$/ && print(<<"end_final_options") && last DESCRIPTION;
$sourced_msg
----------------------------------------------------------------
->    Options file           = $OPTFILE_NAME
      MATLAB                 = $MATLAB
->    COMPILER               = $COMPILER
->    Compiler flags:
         COMPFLAGS           = $COMPFLAGS
         OPTIMFLAGS          = $OPTIMFLAGS
         DEBUGFLAGS          = $DEBUGFLAGS
         arguments           = $ARG_FLAGS
         Name switch         = $NAME_OBJECT
->    Pre-linking commands   = $PRELINK_CMDS
->    LINKER                 = $LINKER
->    Link directives:
         LINKFLAGS           = $LINKFLAGS
         LINKDEBUGFLAGS      = $LINKDEBUGFLAGS
         LINKFLAGSPOST       = $LINKFLAGSPOST
         Name directive      = $NAME_OUTPUT
         File link directive = $LINK_FILE
         Lib. link directive = $LINK_LIB
         Rsp file indicator  = $RSP_FILE_INDICATOR
->    Resource Compiler      = $RC_COMPILER
->    Resource Linker        = $RC_LINKER
----------------------------------------------------------------

end_final_options
     /^file_not_found$/ && print(<<"end_file_not_found") && last DESCRIPTION;
  $main::cmd_name:  $filename not a normal file or does not exist.

end_file_not_found
     /^meaningless_output_flag$/ && print(<<"end_meaningless_output_flag")  && last DESCRIPTION;
  Warning: -output ignored (no MEX-file is being created).

end_meaningless_output_flag

    /^compiler_not_found$/ && print(<<"end_compiler_not_found") && last DESCRIPTION;
  Error: Could not find the compiler "$COMPILER" on the DOS path.
         Use mex -setup to configure your environment properly.

end_compiler_not_found

    /^wrong_mexext_in_output_flag$/ && print(<<"end_wrong_mexext_in_output_flag") && last DESCRIPTION;

  Warning: Output file was specified with file extension, "$mex_ext", which
           is not a proper MEX-file extension.  The proper extension for 
           this platform, "$ENV{'MEX_EXT'}", will be used instead.

end_wrong_mexext_in_output_flag

    /^outdir_missing_name_object$/ && print(<<"end_outdir_missing_name_object") && last DESCRIPTION;
  Warning: The -outdir switch requires the mex options file to define
           NAME_OBJECT. Make sure you are using the latest version of
           your compiler's mexopts file.

end_outdir_missing_name_object

    /^fortran_cannot_change_entrypt$/ && print(<<"end_fortran_cannot_change_entrypt") && last DESCRIPTION;
  Warning: -entrypt ignored (FORTRAN entry point cannot be overridden).

end_fortran_cannot_change_entrypt

		/^largeArrayDimsCompatibleArrayDimsNotSelected$/
		  && print(<<"end_largeArrayDimsCompatibleArrayDimsNotSelected") && last DESCRIPTION;
***************************************************************************
  Warning: Neither -compatibleArrayDims nor -largeArrayDims is selected. 
           Using -compatibleArrayDims. In the future, MATLAB will require
	   the use of -largeArrayDims and remove the -compatibleArrayDims 
	   option. For more information, see:
           http://www.mathworks.com/help/matlab/matlab_external/upgrading-mex-files-to-use-64-bit-api.html 
****************************************************************************

end_largeArrayDimsCompatibleArrayDimsNotSelected


		/^largeArrayDimsCompatibleArrayDimsNotSelectedHTML$/
		  && print(<<"end_largeArrayDimsCompatibleArrayDimsNotSelectedHTML") && last DESCRIPTION;
***************************************************************************
  Warning: Neither -compatibleArrayDims nor -largeArrayDims is selected. 
           Using -compatibleArrayDims. In the future, MATLAB will require
	       the use of -largeArrayDims and remove the -compatibleArrayDims 
	       option. For more information, see:
           <a href="matlab:web('http://www.mathworks.com/help/matlab/matlab_external/upgrading-mex-files-to-use-64-bit-api.html ','-browser')">http://www.mathworks.com/help/matlab/matlab_external/upgrading-mex-files-to-use-64-bit-api.html </a>
****************************************************************************
 
end_largeArrayDimsCompatibleArrayDimsNotSelectedHTML

    do {
        print "Internal error: Description for $_[0] not implemented\n";
        last DESCRIPTION;
    };
 }
}
#=======================================================================
sub fix_mex_variables
{
    #===================================================================
    # fix_mex_variables: Fix variables for mex.
    #===================================================================

    if ($verbose) {
        describe("final_options");
    }

    if ($outdir_flag && $NAME_OBJECT eq "") {
        describe("outdir_missing_name_object");
    }

    # Decide how to optimize or debug
    #
    if (! $debug) {                                  # Normal case
        $FLAGS = $OPTIMFLAGS;
    } elsif (! $optimize) {                          # Debug; don't optimize
        $FLAGS = $DEBUGFLAGS;
    } else {                                         # Debug and optimize
        $FLAGS = "$DEBUGFLAGS $OPTIMFLAGS";
    }

    # Include the simulink include directory if it exists
    #
    my $simulink_inc_dir = mexCatdir($ML_DIR, "simulink", "include");
    if (-e remove_quotes($simulink_inc_dir) && !$fortran)
    {
        $FLAGS = "-I$simulink_inc_dir $FLAGS";
    }

    # Add extern/include to the path (it always exists)
    #
    my $extern_include_dir = mexCatdir($ML_DIR, "extern", "include");
    if (!$fortran)
    {
        $FLAGS = "-I$extern_include_dir $FLAGS";
    }

    # Verify that compiler binary exists
    #
    if ($COMPILER eq "none") {
        describe("invalid_options_file");
        expire("Error: Options file is invalid.");
    }
    $COMPILER_DIR = search_path("$COMPILER.exe");
    if ( ! $COMPILER_DIR ) {
        describe("compiler_not_found");
        expire("Error: Unable to locate compiler.");
    }

    # If there are no files, then exit.
    #
    if (!@FILES) {
        describe("usage");
        expire("Error: No file names given.");
    }
}
#=======================================================================
sub init_mex
{
    #===================================================================
    # init_mex: Mex specific initialization.
    #===================================================================

    $main::mexopts_directory = mexCatdir($main::script_directory,
                                                     $ARCH,
                                                     "mexopts");
    $OPTFILE_LONGNAME = "mexopts.bat";
    $OPTFILE_NAME = $OPTFILE_LONGNAME;

    # 32-bit compatibility mode. Default for now
    $v7_compat = "yes";

    # Should always be one of {"c", "cpp", "fortran", "cuda", "all"}
    #
    $lang = "c"; 
    $link = "unspecified";
    $ENV{'ENTRYPOINT'} = "mexFunction";

    $COMPILE_EXTENSION = 'c|f|cc|cxx|cpp|for|f90|cu';
}
#=======================================================================
sub parse_mex_args
{
    #===================================================================
    # parse_mex_args: Parse all mex arguments including common.
    #===================================================================

	$bool_found_compat  = "no";
    for (;$_=shift(@ARGV);) {

        # Perl-style case construct
        ARGTYPE: {

            /^-compatibleArrayDims$/ && do {
                $v7_compat = "yes";
				$bool_found_compat = "yes";
                last ARGTYPE;
            };

            /^-largeArrayDims$/ && do {
                $v7_compat = "no";
				$bool_found_compat = "yes";
                last ARGTYPE;
            };

            /^[-\/](h(elp)?)|\?$/ && do {
                printHelp();
                expire("normally");
                last ARGTYPE;
    	    };

          /^-v$/ && do {
              $verbose = "yes";
              last ARGTYPE;
          };

          if (parse_common_dash_args($_)) {
              last ARGTYPE;
          }

          /^-entrypt$/ && do {
              $ENV{'ENTRYPOINT'} = shift(@ARGV);
              if ($ENV{'ENTRYPOINT'} ne "mexFunction")
              {
                  expire("Error: -entrypt argument must be 'mexFunction'");
              }
              last ARGTYPE;
          };

          # Finished processing all '-' arguments. Error at this
          # point if a '-' argument.
          #
          /^-.*$/ && do {
              describe("usage");
              expire("Error: Unrecognized switch: $_.");
              last ARGTYPE;
          };

            if (parse_common_nodash_args($_)) {
                last ARGTYPE;
            }

            do {

                # Remove command double quotes (put there by mex.m)
                #
                tr/"//d;

                if (/(.*)\.dll$/)
                {
                    expire("Error: " . tool_name() . " cannot link to '$_' directly.\n" .
                            "  Instead, you must link to the file '$1.lib' which corresponds " .
                            "to '$_'.");
                }

                if (!/\.lib$/ && !-e $_) {
                    expire("Error: '$_' not found.");
                }

                # Put file in list of files to compile
                $filename = $_;
                $filename = mexGetShortPathPreservingFilename($filename);
                # If file name starts with an @-mark, then add a ".\" before it.
                $filename =~ s|^@|.\\@|;

                push(@FILES, $filename);

                # Try to determine compiler (C or C++) to use from
                # file extension.
                #
                if (/\.cu$/i)
                {
                    $lang = "cuda";
                }
                if (/\.(cpp|cxx|cc)$/i)
                {
                    $lang = "cpp";
                }
                if (/\.c$/i)
                {
                    $lang = "c";
                }
                if (/\.(f|for|f90)$/i)
                {
                    $lang = "fortran";
                }
				if (   $bool_found_compat eq "no" && $verbose)
				{
					if ($called_from_matlab) {
						describe("largeArrayDimsCompatibleArrayDimsNotSelectedHTML");
					}
					else {
						describe("largeArrayDimsCompatibleArrayDimsNotSelected");
					}
          		}
               last ARGTYPE;
            }
        } # end ARGTYPE block
    } # end for loop 

    if ($lang_override) { $lang = $lang_override; }

    if ($lang eq "fortran" && $ENV{'ENTRYPOINT'} ne "mexFunction")
    {
        describe("fortran_cannot_change_entrypt");
        $ENV{'ENTRYPOINT'} = "mexFunction";
    }

    # Warn user that output target is ignored when compile only.
    #
    if ($compile_only && $output_flag) {
        describe("meaningless_output_flag");
    }
}
#=======================================================================
sub set_mex_variables
{
    #===================================================================
    # set_mex_variables: Set more variables for mex.
    #===================================================================

    # Use the 1st file argument for the target name (MEX_NAME)
    # if not set. Also set $fortran variable if correct extension.
    #
    ($derived_name, $EXTENSION) = ($FILES[0] =~ /([ \w]*)\.(\w*)$/);
    $ENV{'MEX_NAME'} = $derived_name if (!($ENV{'MEX_NAME'}));
    $fortran = "yes" if ($EXTENSION =~ /^(f|for|f90)$/i);

    if ($ARCH eq "win32")
    {
        $ENV{'MEX_EXT'} = ".mexw32";
    }
    elsif ($ARCH eq "win64")
    {
        $ENV{'MEX_EXT'} = ".mexw64";
    }

    if ($RC_COMPILER =~ /\S/) {
        $ENV{'RES_PATH'} = mexCatdir($ENV{'MATLAB'}, "extern", "include") . "\\";
        $ENV{'RES_NAME'} = "";
    }
}
#=======================================================================
sub post_mex_warnings
{
    #===================================================================
    # post_mex_warnings: Print warning message at the end of mexing.
    #===================================================================

    if ( (!$compile_only) && ($mex_ext ne "") && ($mex_ext ne $ENV{'MEX_EXT'}) ) {
        describe("wrong_mexext_in_output_flag");
    }
}

#=======================================================================
########################################################################
#=======================================================================
# Main:
#=======================================================================
init_common();

init_mex();
parse_mex_args();

set_common_variables();
set_mex_variables();    
    
# Do only setup if specified.
#
if ($setup || $setup_special)
{
    do_setup();
    exit(0);
}

options_file();

fix_flag_variables();
process_env_assignments(\@CMD_LINE_OVERRIDES);

fix_mex_variables();
fix_common_variables();

if ($makefilename)
{
    # MAKEFILE is closed in expire()
    #
    start_makefile();
}
compile_files();
expire("normally") if ($compile_only);
if ($makefilename)
{
    emit_link_dependency();
}
pre_or_postlink("PRELINK_CMDS");
files_to_remove();
if ($ENV{'RES_NAME'} =~ /\S/)
{
    compile_resource();
}
linker_arguments();
link_files();
if ($ENV{'RES_NAME'} =~ /\S/ && $RC_LINKER =~ /\S/)
{
    resource_linker();
}
pre_or_postlink("POSTLINK_CMDS");
if ($makefilename)
{
   emit_delete_resource_file();
   emit_makefile_terminator();
}
    
post_mex_warnings();
  
expire("normally");
