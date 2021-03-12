package mexsetup;

=head1 NAME

mexsetup - Handle setting up a default options file for mex or mbuild

=head1 SYNOPSIS

 use mexsetup;
 &setup($tool_name, # "mex" or "mbuild"
        $opts_dir,  # Dir containing the .stp setup files and .bat opts files
        $desired_languages, # An array reference containing uppercase strings
                            # of the desired programming language for which to
                            # set up. All compilers are listed if any of these
                            # strings are 'ANY'.
        $automode,  # if true, automatically search for compilers, and if only
                    # one is found, install it without bothering the user
        $setup_ref  # reference to setup argument list
        );

 use mexsetup;
 &registry_lookup($key, $value);

=head1 DESCRIPTION

Scans the directory $opts_dir for files with the .stp extension. Dynamically
runs the perl code in those files to gather information about supported
compilers. Uses this information to present a list to the user of supported
compilers. Copies the template options file (also in $opts_dir) corresponding
to the user selected compiler to the user's Profile directory.

A .stp file should contain one function, whose name is the same as the .stp
file, minus the ".stp". The function will be passed one input, a hash
reference with at least the following fields:

    matlab_bin      => a string containing the location <MATLAB>\bin
    registry_lookup => a reference to a function which takes two input strings,
                       a key and a name, and looks them up in the
                       HKEY_LOCAL_MACHINE portion of the Windows Registry. The
                       function returns a string containing the queried data,
                       or an empty string if the data could not be found.
    search_path     => a reference to a function which takes one input string,
                       a filename, and searches for it on the DOS path. The
                       function returns a string containing the directory in
                       which the filename was found, or an empty string if the
                       file could not be found.

The function returns a second hash reference, containing at least the
following fields:

    vendor_name      => The full (vendored) name of the compiler 
                        (e.g. "Microsoft Visual C/C++").
    version          => The version of the compiler, as a string (e.g. "6.0")
    group_id         => A string containing the group to which this setup file
                        belongs.  Usually, each vendor has its own group id.
                        If the vendor changes the name of the compiler, one 
                        can have mexsetup treat the two differently named
                        compilers as just different versions of the same
                        compiler having their .stp files contain the same
                        group_id. The user never sees the group_id.
    serial           => A serial number. Each .stp file with a given group_id
                        must have a unique serial number. The serial number
                        should increase with each new version of the compiler.
                        (e.g. MSVC 4.2 has a serial number of 1.0, MSVC 5.0
                        has a serial number of 2.0, and MSVC 6.0 has a serial
                        number of 3.0.)
    optfile_name     => The base name of the template options file to copy to
                        the user's Profile directory. This file must reside in
                        $opts_dir as well. (e.g. "msvc60opts.bat".)
    default_location => A string containing the location where the compiler's
                        installer installs the compiler by default.         
    language_handled => A reference to an array of strings of supported languages
                        supported by this compiler.  Current strings can be 
                        "C", "CPP", and "FORTRAN".
    locate           => A reference to a function with no inputs, which
                        returns a reference to an array of strings, each of
                        which represents a directory where the compiler is
                        located. The array can legally have zero, one, or more
                        entries. Setup() considers the leftmost entry which
                        has not also been returned by a locate function from
                        a .stp file with a higher serial number to be the
                        directory where the compiler is located. This allows
                        setup() to locate multiple versions of the same
                        compiler.
    root_var         => The name of the environment variable in the template
                        options file that setup() will burn with the location
                        of the compiler.  When setup() copies the template
                        options file from $opts_dir to the user's Profile
                        directory, it will search for a line of the form:
                         
                                set <root_var>=%<anystring>%
                      
                        It will replace %<anystring>% with the output of the
                        root_val entry actual (see below), which usually is 
                        the location of the compiler.
    root_val         => A reference to a function which takes one string input,
                        containing the base location of the compiler, and
                        returns a string, containing the value to burn into
                        the options file copied to the user's Profile
                        directory. Under most circumstances this function can
                        simply return its input as its output. However, see
                        msvc60opts.stp for an example of a .stp file where it
                        does not.
    post_setup_fcn   => (optional) A reference to a function with no inputs or
                        outputs. If this entry exists, it is called by setup()
                        after copying the template options file to the user's
                        Profile directory.

Many .stp files are provided in <MATLAB>/bin/<ARCH>/mexopts and 
<MATLAB>/bin/<ARCH>/mbuildopts. These can be used as examples for creating
.stp files for other (non-MathWorks supported) compilers.

=head1 COPYRIGHT

Copyright (c) 1999-2011 The MathWorks, Inc. All rights reserved.

=cut


use Exporter ();
@ISA = qw(Exporter);

@EXPORT = qw(setup callstpfile correct_version find_highest_build_of);

use strict;
use mexutils;

use File::Basename;
use Cwd;
use List::Util qw(max);

# Sort routine to sort compiler setup records by vendor name,
# with serial number as a secondary key.
sub by_vendor_and_serial
{
    if ($a->{"vendor_name"} lt $b->{"vendor_name"}) {
        return -1;
    } elsif ($a->{"vendor_name"} eq $b->{"vendor_name"}) {
        return $b->{"serial"} <=> $a->{"serial"};
    } else {
        return 1;
    }
}

# Sort routine to sort compiler setup records by group id,
# with serial number as a secondary key.
sub by_group_and_serial
{
    if ($a->{"group_id"} lt $b->{"group_id"}) {
        return -1;
    } elsif ($a->{"group_id"} eq $b->{"group_id"}) {
        return $b->{"serial"} <=> $a->{"serial"};
    } else {
        return 1;
    }
}

# Given a string S and a reference to an array of strings A, return
# true if any element of A equals S.
sub is_in
{
    my ($elem, $set_ref) = @_;
    my $set_elem;

    foreach $set_elem (@$set_ref) {
        if ($set_elem eq $elem) {
            return 1;
        }
    }
    
    return 0;
}    

sub query_info 
{
# queries and verifies that the 'var_value' is between the
# 'lower_limit' and the 'upper_limit'.  if not, then query for the
# 'request', citing the 'problem' as the reason.
# (this is used by 'setup')
    my ($lower_limit, $upper_limit, $problem, $request) = @_;
    my $var_value;

    chop($var_value=<STDIN>);
    # Verify that the value is with in the boundaries. It must be an integer.
    while (!($var_value =~ /^[0-9]+$/ ) ||
           $var_value<$lower_limit|$var_value>$upper_limit) {

        print "$problem\n";
        print "$request";
        chop($var_value=<STDIN>);
    }

    $var_value;
}

sub ensure_dir
{
    # Check for existence of a directory. If it doesn't exist, make it.
    # This function returns a status: 0 for failure, 1 for success.  (Opposite of setup)
    my ($dir) = @_;

    # The usual file test operator -d does not work with Shift-JIS 5c characters,
    # so we are utilizing a bug that if we add an empty space to the directory,
    # even directories with Shift-JIS 5c characters are found to exist.
    if (!(-d $dir . " ")) {
        my $parent_dir = $dir;
        $parent_dir =~ s/\\[^\\]+$//;
        &ensure_dir($parent_dir);
        if (mkdir($dir, 777) == 0) {
            print "Error: Cannot create directory \"$dir\"\n";
            return(0);
        }
    }
    return(1);
} # end of ensure_dir

sub print_and_ask_yes_or_no
{
    # This function asks the user a yes or no question.  The first argument
    # is the default.  Set default to 1 if yes is the default, otherwise no is the
    # default.  The return value is 1 for yes and 0 for no.
    my ($default) = @_;
    my $status;
    if ($default eq 1) 
    {
        print " [y]/n? ";
    }
    else
    {
        print " y/[n]? ";
    }
    chop($status=<STDIN>);
    $status = lc($status);
    if ($default eq 1)
    {
        if ($status eq "n" || $status eq "no")
        {
            return 0;
        }
        else
        {
            return 1;
        }
    }
    else
    {
        if ($status eq "y" || $status eq "yes")
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
}

# Search DOS PATH environment variable for $binary_name.  Return
# the directory containing the binary if found on the path, or an
# empty path otherwise.
sub search_path 
{
    my ($binary_name) = @_;
    my (@path, $path_entry, $found);

    foreach ( split(/;/,$ENV{'PATH'}) ) {
        if ( -e "$_\\$binary_name" ) {
            return $_;
        }
    }
    '';
} # end of search_path

# Copy a template mex or mbuild options file to the user's profile directory,
# "burning" into it the location of the selected compiler.
# If $ask_no_questions is true, no confirmation notice will be given.
sub install_options_file 
{
    my ($tool_name,       # "mex" or "mbuild"
        $record,          # Compiler setup record for selected compiler
        $opts_dir,        # Directory containing the .stp setup files and
                          # .bat opts files
        $chosen_location, # Directory containing the selected compiler
        $destOptsFile,    # Use if not empty
        $ask_no_questions,# Don't confirm setup if true
        $destOptsDir      # provides user's prefdir
        ) = @_;
    
    my $presetmode = $destOptsFile;

    if (!$ask_no_questions) {
        # before making edits, verify from user that all information is correct
        print "\nPlease verify your choices:\n\n";
        print "Compiler: " . $record->{"vendor_name"} . " " . $record->{"version"} . "\n";
        print "Location: $chosen_location\n";
        print "\nAre these correct";
        if (print_and_ask_yes_or_no(1) ne 1)
        {
            print "\n  $tool_name: No compiler selected. No action taken.\n\n";
            return 0;
        }
    }
    my $root_val_fcn = $record->{"root_val"};
    my ($root_val_err_msg, $root_val_warn_msg) = &$root_val_fcn($chosen_location);
    
    if ($root_val_err_msg ne "") {
        # Error condition where the root directory of the compiler is empty
        # (i.e. most likely not installed properly.)
        print $root_val_err_msg . "\n";
        return(1);
    } elsif ($root_val_warn_msg ne "") {
        print $root_val_warn_msg . "\n";
    }
    my $root_val = $chosen_location;

    my $link_val = $record->{"link_val"};
    # Dereference hash to test existence of link_val key.
    my %record_hash = %{$record};

    if (exists  $record_hash{ "link_val" } && $link_val eq "") {
        return(1);
    }

    # Get the target directory and make sure it exists.
    #
    if (!$destOptsFile) {
        if (!&ensure_dir($destOptsDir)){
            #This means that directory does not exist and a failure has occurred
            return(1);
        }
        
        if ($tool_name eq "mex") {
            $destOptsFile="$destOptsDir\\mexopts.bat";
        } else {
            $destOptsFile="$destOptsDir\\compopts.bat";
        }
    } else {
        #  getcwd() comes back in forward slash (UNIX) form!
        #   
        my $dir;
        my $pwd = getcwd();
        $pwd =~ s@\/@\\@g;
        $dir = dirname($destOptsFile);
        if (!chdir($dir)) {
            print "Error: Directory part of options file does not exist . . .\n";
            print "       Directory = $dir\n";
            print "       Options file = $destOptsFile\n";
            return 1;
        } else {
            my $local_pwd = getcwd();
            $local_pwd =~ s@\/@\\@g;
            $destOptsFile = $local_pwd . "\\" . basename($destOptsFile);
            chdir("$pwd");
        }
    }

    my $srcOptsFile = $opts_dir . "\\" . $record->{"optfile_name"};

    print "\nTrying to update options file: $destOptsFile\n";
    print   "From template:              $srcOptsFile\n";

    # Open and read in the template options file.
    if (!open (OPTIONSFILE, "<$srcOptsFile")) {
        print "\nError: Can't open $srcOptsFile\n";
        return(1);
    }
    my @OptionsFile = <OPTIONSFILE>;
    close(OPTIONSFILE);

    # If the options file is read-only, ask if they want to overwrite it.
    if (-e $destOptsFile && ! -W $destOptsFile && !$presetmode) {
        print "\nThe following options file is read-only \n$destOptsFile. \nOverwrite";
        if (print_and_ask_yes_or_no(0) eq 1)
        {
            printf "\nSaving old options file in $destOptsFile.old\n";
            unlink("$destOptsFile.old");
            rename($destOptsFile,"$destOptsFile.old");
            unlink($destOptsFile);
        } else { 
            printf "\nOptions file not changed.\n\n"; 
            return 0; 
        }
    } elsif (-e $destOptsFile && ! -W $destOptsFile && $presetmode) {
        print "\nError: Options file is read only. Will not try to overwrite . . .\n";
        print "       Options file = $destOptsFile\n";
        return(1);
    }



    # Open the target output file, and write the template file into it.
    # when the Root Environment Variable (root_var) is assigned to, burn in
    # the compiler location.
    if (!open (OPTIONSFILE, ">$destOptsFile")){
        print "\nError: Can't open $destOptsFile\n";
        return(1);
    }
    my $doneComp=0;
    my $doneLink=0;
    foreach (@OptionsFile) {
        if (!$doneComp && /^\s*set $record->{"root_var"}=/) {
            s/=.*$/=$root_val/;
            $doneComp=1;
        }
        if (!$doneLink && /^\s*set LINKERDIR=/) {
            s/=.*$/=$link_val/;
            $doneLink=1;
        }
        print OPTIONSFILE "$_";
    }

    close(OPTIONSFILE);
    print "\nDone . . .\n\n";
    return(0);
} #end of install_options_files

#######################################################################
# Run a single command
#######################################################################
sub sRunCmd {
    my ($cmd) = @_;
    my ($rc, $messages);
    $cmd = "\"$cmd\"" if ( $ENV{OS} eq 'Windows_NT' );
    print "\n--> $cmd\n\n";
    $messages = `$cmd`;
    $rc = $?;
    print $messages;
    $rc = $rc >> 8 if $rc;
    wantarray ? ($messages, $rc) : $messages;
} # sRunCmd



#FUNCTION callstpfile
# Input arguments are 
#      1) MATLAB options file directory 
#      2) STP-file name, relative to mexopts directory
#
# Output argument is record returned from calling the stp file.
sub callstpfile
{

    my ($opts_dir,
	$stpfilename) = @_;

    my $matlab_bin = $opts_dir . "\\..";
    while ($matlab_bin =~ s/\\[^\\.]+\\\.\.//) {}

    my $optfile_inputs = {
        'matlab_bin'      => $matlab_bin,
        'registry_lookup' => \&registry_lookup,
        'search_path'     => \&search_path
	};
    
    require "$opts_dir\\$stpfilename";

    my $stpfuncname = $stpfilename;
    $stpfuncname =~ s/^.*[\\\/]//; # removes partial path
    $stpfuncname =~ s/\.(bat|stp)//; # removes extension

    # $stpfuncname is a string containing the name of a function to call,
    # a so-called "symbolic reference". 'Use strict' disallows this normally,
    # so the no strict/use strict stuff below temporarily allows it.
    no strict 'refs';
    my $record = &$stpfuncname($optfile_inputs);
    use strict 'refs';
    
    return $record;

} # callstpfile 


sub getWinMajorVersion {
#=======================================================================
# getWinMajorVersion: returns the value of dwMajorVersion.  It is used
# to tell the difference between major version of Windows OSes. For more
# info see http://msdn2.microsoft.com/en-us/library/ms724451.aspx
#=======================================================================
    
    my ($dwMajorVersion) = (`ver` =~ / (\d+)\./);

    return $dwMajorVersion;
    
}

sub correct_version {
#===================================================================
# correct_version: A local function to returns true if the version
# of the compiler matches the expected version string.
#===================================================================
    my $executablePath = $_[0];
    my $versionNumber = $_[1];
    my $version=`\"$executablePath\" 2>&1`;
    $versionNumber =~ s/\./\\./;
    return ($version =~ /\D$versionNumber/i);
} # correct_version


sub find_highest_build_of {
#===================================================================
# find_highest_build_of: Look in the registry for a particular product
# with a particular major and minor number.  Return the one with the
# largest build number.
#===================================================================
    my($product, $major_minor_number) = @_;

    # registry path fragments for different products
    # note intel v12 compilers are installed in the same location
    my %registry_keys = ( "intel_fortran_12" => "Intel\\Compilers\\Fortran\\",
                          "intel_c_12"       => "Intel\\Compilers\\Fortran\\",
                          "intel_fortran_13" => "Intel\\Compilers\\Fortran\\",
                          "intel_c_13"       => "Intel\\Compilers\\Fortran\\" );

    my @installed_major_minor;
    my $product_node = $Win32::TieRegistry::Registry->{"HKEY_LOCAL_MACHINE\\SOFTWARE\\" . $registry_keys{$product} };
    if( $product_node ) {
        @installed_major_minor = $product_node -> SubKeyNames;
    } else {
    	$product_node = $Win32::TieRegistry::Registry->{"HKEY_LOCAL_MACHINE\\SOFTWARE\\Wow6432Node\\" . $registry_keys{$product} };
	    if( $product_node ) {
	        @installed_major_minor = $product_node -> SubKeyNames;
	    } else {
	        return ;
	    }
    }
    my @correct_major_minor;
    foreach (@installed_major_minor) {
        my @sp = split( /\./ );
        push( @correct_major_minor, $_ ) if $sp[0] =~ m/$major_minor_number/;
    }

    return $product_node->{max(@correct_major_minor)}->{"ProductDir"}
} #

sub printCompilerList {
#===================================================================
# printCompilerList: A local function to print a list of compilers
# for user and pretty prints them.
#===================================================================
    my ($opts_dir,$found_compilers_ref,$found_compiler_locations_ref);
    my @found_compilers;
    my @found_compiler_locations;
    
    if ($#_ == 2) { #NOTE: $#_ is the number of inputs and is ZERO based
        ($opts_dir,$found_compilers_ref,$found_compiler_locations_ref) = @_;
        @found_compilers = @$found_compilers_ref;
        @found_compiler_locations = @$found_compiler_locations_ref;
    } elsif ($#_ == 1) { #NOTE: $#_ is the number of inputs and is ZERO based
        ($opts_dir,$found_compilers_ref) = @_;
        @found_compilers = @$found_compilers_ref;
    } else {
        # This usage of die is ok.  It is not meant to be an acceptable failure mode.
        die "Internal Error: Subroutine \"printCompilerList\" used with wrong number of inputs.";
    }

    my $count = 1;

    foreach my $record (@found_compilers) {
        print "[$count] " . $record->{"vendor_name"};
        if( $record->{"version"} ){
            print " " . $record->{"version"};
        }
        if (my $link_opt_file = $record->{"linker_optfile_name"}) {
            if (my $record_linker = callstpfile($opts_dir,$link_opt_file . ".stp")) {
                print " \(with " . $record_linker->{"vendor_name"} . " linker\)";
            }
        }
        if (@found_compiler_locations){
            print " in $found_compiler_locations[$count-1]\n";
        } else {
            print "\n";
        }
        
        $count++;
    }
    return $count;
}

# This is the main routine for mexsetup.
# 1. Only &setup, registry_lookup, callstpfile, correct_version, and find_highest_build_of
#    can be called from outside of this module. 
# 2. There are three modes.
#    a. query
#    b. auto
#    c. preset
# 3. They all create and install the appropriate options file.
#
sub setup
{
    my ($tool_name,         # "mex" or "mbuild"
        $opts_dir,          # Dir containing the .stp setup files and .bat opts files
        $desired_languages, # An array reference containing uppercase strings
                            # of the desired programming language for which to 
                            # set up. All compilers are listed if any of these
                            # strings are 'ANY'.
        $automode,          # if true, automatically search for compilers, and if only
                            # one is # found, install it without bothering the user
        $destOptsDir,       # gives the location of user's preference directory
        $setup_ref,         # reference to setup argument list
        $reglibs,           # Flag to decide whether or not to register COM libraries
                            # for .NET and Excel Builders only
        $called_from_matlab # String that reports if setup called from MATLAB                   
        ) = @_;

    my @setup_args = @$setup_ref;

    my @filenames;
    my $filename;
    my $i;
    my $record;
    my @optfile_records;
    my $compiler_location;
    my $ask_no_questions;
    my $presetmode = scalar(@setup_args);

    # Turn off buffered output.
    my $old_pipe = $|;
    $| = 1;

    if (!$automode) {
        # Do not try to make this URL include a hot link.  This will print while MATLAB is
        # blocking the process.  So if this were a hot link nothing would happen till setup 
        # finished.
        my $supportedCompilerURL = mexSupportedCompilerListLocation(0);
        print "\n" .
              "Welcome to $tool_name -setup.  This utility will help you set up \n" .
              "a default compiler.  For a list of supported compilers, see \n" .
              "$supportedCompilerURL\n" .
              "\n";

        print "Please choose your compiler ";
        if ($tool_name eq "mex") {
            print "for building MEX-files:\n\n";
        } else {
            print "for building shared libraries or COM components:\n\n";
        }
    }

    if (!$presetmode) {
        # Get a list of all the *.stp files in $opts_dir.
        #
        if (!opendir(OPTSDIR, "$opts_dir")) {
            print "Error: Couldn't find $opts_dir.\n";
            return(1);
        }
        @filenames = grep /^.*\.stp$/i, readdir OPTSDIR;
        @filenames = map { lc $_ } @filenames;
        closedir OPTSDIR;
    } else {
        # Check that the template options file exists
        #
        my $f;
        if ($tool_name eq "mex") {
            $f = $setup_args[0] . 'opts.stp';
        } else {
            $f = $setup_args[0] . 'compp.stp';
        }
        if (! -e "$opts_dir\\$f") {
            print "Error: Couldn't find setup file:\n$opts_dir\\$f\n";
            return(1);
        }
        @filenames = ($f);
    } 

    # For each .stp file, dynamically include it and call its initialization
    # routine (whose name must be the same as the .stp file minus the ".stp".
    foreach $filename (@filenames) {
        $record = callstpfile($opts_dir,$filename);
        my @language_handled_array = @{$record->{"language_handled"}};

        # Only add the record to the master list (optfile_records) if it
        # can handle at least one of the requested language.
        foreach my $language (@$desired_languages) {
            my $language_is_handled = 0;
            foreach (@language_handled_array) {
                if($_ eq $language) {   
                    $language_is_handled = 1;
                    last;
                }
            }
            if ($language eq "ANY" || $language_is_handled) {
                push(@optfile_records, $record);
                last;
            }
        }
    }
    
    if ($#optfile_records == -1) {
        my $errmsg;

        if ($presetmode) {
            $errmsg = "Error: Could not detect " . $setup_args[0] . 
                      " compiler on local system\n";
            print $errmsg;
            return(1);
        }
        $errmsg = "Error: Could not detect a compiler on local system";

        if ($automode) {
            $errmsg .= "\nwhich can compile the specified input file(s)";
        }
        
        print $errmsg . "\n";
        return(1);
    }

    my $status;
    if ($automode) {
        $status = 1;
    } else {
        print "Would you like $tool_name to locate installed compilers";
        $status = print_and_ask_yes_or_no(1);
    }

    if ($status eq 1) {
    # User wants MEX to find available compilers.
        my @found_compiler_locations = ();
        my @found_compilers=();
        my $group_id;
        my @curr_group_found_compiler_locations = ();
        my @curr_group_found_compilers = ();
        
        @optfile_records = sort by_group_and_serial @optfile_records;
    
        $group_id = "";
        foreach $record (@optfile_records) {

            if ($record->{"group_id"} ne $group_id) {
                # Processing a new group; push all info from old group onto main
                # "found" lists, and clear out "curr_group" lists.
                push(@found_compiler_locations, @curr_group_found_compiler_locations);
                push(@found_compilers, @curr_group_found_compilers);
                @curr_group_found_compiler_locations = ();
                @curr_group_found_compilers = ();
                $group_id = $record->{"group_id"};
            }

            # Call the locate function for the current record:
            my $locate_fcn = $record->{"locate"};
            my @locations = &$locate_fcn;
            my $location;
            
            # The locate function can return an array of directories. Check each 
            # directory against the list of directories already identified by 
            # later records for the same group (remember, the list was sorted 
            # by group and then by serial number.) As soon as we find a directory
            # not already "claimed" by a newer/later compiler record, remember it
            # as the directory where a compiler for $record was found.
            foreach $location (@locations) {
                if (!is_in($location, \@curr_group_found_compiler_locations)) {
                    my $link_opt_file = $record->{"linker_optfile_name"};
                    my @locations_linker = ();
                    my $addCompilerLocationToList = 1;
                    if ($link_opt_file) {
                        if (my $record_linker = callstpfile($opts_dir,$link_opt_file . ".stp")) {
                            my $locate_fcn_linker = $record_linker->{"locate"};
                            @locations_linker = &$locate_fcn_linker;
                            #If no linker is found then $addCompilerLocationToList should be 0.
                            $addCompilerLocationToList = $#locations_linker+1; # add 1 since Perl is 0 based.
                        }
                    }
                    if ($addCompilerLocationToList > 0) {
                        push(@curr_group_found_compiler_locations, $location);
                        push(@curr_group_found_compilers, $record);
                        last;
                    }
                }
            }
        }

        
        # Push the info from the last group on the master list onto main "found" lists.
        push(@found_compiler_locations, @curr_group_found_compiler_locations);
        push(@found_compilers, @curr_group_found_compilers);
        
        my $compiler;
        my $count = 1;

        my $best_choice;
        if ($automode && $#found_compilers == 0) {
            # only one compiler found and we're in automode, so just choose it.
            $compiler = 1;
        } elsif (!$presetmode) {
            foreach $record (@found_compilers) {
                if($record->{"vendor_name"} =~ /Microsoft/i && defined($best_choice) ) {
                    if($found_compilers[$best_choice-1]->{"vendor_name"} =~ /Microsoft/i) {
                        if($found_compilers[$best_choice-1]->{"version"} lt $record->{"version"}) {
                            $best_choice = $count;
                        }
                    } else {
                        $best_choice = $count;
                    }
                } elsif($record->{"vendor_name"} =~ /Watcom/i && defined($best_choice) ) {
                    if($found_compilers[$best_choice-1]->{"vendor_name"} =~ /Microsoft/i) {
                        $count++;
                        next;
                    } elsif($found_compilers[$best_choice-1]->{"vendor_name"} =~ /Watcom/i) {
                        if($found_compilers[$best_choice-1]->{"version"} lt $record->{"version"})                        {
                            $best_choice = $count;
                        }
                    } else {
                        $best_choice = $count;
                    }
                } elsif(!$best_choice) {
                    $best_choice = $count;
                }
                $count++
            }
        } else {	# preset mode
            if ($#found_compilers == -1) {
                print "\nError: Compiler cannot be found on this system . . .\n\n";
                return(1);
            } else {
                print "Error: Same compiler found in multiple locations . . .\n";
                $count = 1;
                foreach $record (@found_compilers) {
                    print "[$count] " . $record->{"vendor_name"};
                    if( $record->{"version"} ne "" ) {
                    	print " version " . $record->{"version"};
                    }
                    print " in $found_compiler_locations[$count-1]\n";
                    $count++;
                }
                print "\n";
                return(1);
            }
        }

        if ($#found_compilers == -1) {
            my $url = mexSupportedCompilerListLocation($called_from_matlab);
            print "\n" .
                  "No supported SDK or compiler was found on this computer.\n" . 
                  "For a list of supported compilers, see \n" .
                  "$url \n\n";
            return(1);
        }

        unless($automode == 2) {
            print "\nSelect a compiler:\n";
            $count = &printCompilerList($opts_dir,\@found_compilers,\@found_compiler_locations);
            
            print "\n[0] None\n\n";
            print "Compiler: ";
            
            $compiler=&query_info(0, $count - 1, "Please select from 0-" . ($count-1), 
                                  "Compiler: ");

            if ($compiler == 0) {
                print "\n  $tool_name: No compiler selected. No action taken.\n\n";
                return 0;
            }
        }
                 
        if($automode == 2 && !$presetmode) {
            print "$tool_name is choosing an appropriate compiler...\n";
            print "$tool_name has selected: " . $found_compilers[$best_choice-1]->{"vendor_name"};
            if( $found_compilers[$best_choice-1]->{"version"} ) {
                print " " . $found_compilers[$best_choice-1]->{"version"};
            }
            print "\n";
            print "You may change this selection by running $tool_name -setup\n";
            $compiler = $best_choice;
        }

        $record = $found_compilers[$compiler-1];
        $compiler_location = $found_compiler_locations[$compiler-1];

        if(defined($best_choice)) {
            $ask_no_questions = $automode && defined($best_choice);
        } else {
            $ask_no_questions = $automode && $#found_compilers == 0;
        }
    # End of section where user wants MEX to find available compilers.
    } elsif (!$presetmode) {
    # User wants a list of all the compilers MEX supports.
        @optfile_records = sort by_vendor_and_serial @optfile_records;
    
        print "\nSelect a compiler:\n";
        my $count = &printCompilerList($opts_dir,\@optfile_records);

        print "\n[0] None\n\n";
        print "Compiler: ";
        
        my $compiler=&query_info(0, $count - 1,
                                 "Please select from 0-" . ($count-1), "Compiler: ");
        
        if ($compiler == 0) {
            print "\n  $tool_name: No compiler selected. No action taken.\n\n";
            return 0;
        }
        
        $record = $optfile_records[$compiler - 1];

        # Try to be helpful by "locating" a compiler of the type selected by the user.
        # This makes an ideal default setting.
        my $locate_fcn = $record->{"locate"};
        my @locations = &$locate_fcn;
        my $chosen_location = "";

        if ($locations[0] ne "" && -e $locations[0]) {
            print "\nYour machine has a ". $record->{"vendor_name"} .
                " compiler located at\n$locations[0]. ";
            print "Do you want to use this compiler";
            
            if (print_and_ask_yes_or_no(1) eq 1) {
                $chosen_location = $locations[0];
            }
        } else {
            print "\nWarning: The default location for " . $record->{"vendor_name"} . " compiler is:" . 
                  "\n         \"" . $record->{"default_location"} . "\"" .
                  "\n         but either that directory does not exist or the configuration" .
                  "\n         is invalid." .
                  "\n" .
                  "\nUse " . $record->{"default_location"} ." anyway";
            if (print_and_ask_yes_or_no(1) eq 1) {
                $chosen_location = $record->{"default_location"};
            }
        }
        
        if ($chosen_location eq "") {
            print "Please enter the location of your compiler: " .
                "[" . $record->{"default_location"} . "] ";
            chop($chosen_location = <STDIN>);
        }
        
        if ($chosen_location eq "") {
            $chosen_location = $record->{"default_location"};
        }
        $compiler_location = $chosen_location;
        $ask_no_questions = 0;
    }

    # Now that we have a compiler selected by the user and a 
    # setup record for it, call install_options_file to copy the 
    # template options file to the correct location.
    #
    my $destination;
    if ($presetmode) {
        $destination = $setup_args[2];
        if ($setup_args[1]) {
            if ($tool_name eq "mex") {
                $record->{"optfile_name"} = $setup_args[0] . $setup_args[1] . 'opts.bat';
            } else {
                $record->{"optfile_name"} = $setup_args[0] . $setup_args[1] . 'compp.bat';
            }
        }
    } else {
        $destination = '';
    }
    if (!&install_options_file($tool_name,
                               $record, 
                               $opts_dir, 
                               $compiler_location, 
                               $destination,
                               $ask_no_questions,
                               $destOptsDir))
    {
    	if ( ($tool_name eq "mbuild") && $reglibs ) {
	    print "\n****************************************************************************************\n";
	    print "Registering mwcomutil.dll and mwcommgr.dll as prompted by $reglibs option \n";
	    my $regDLL = "$ENV{'MATLAB'}\\bin\\$ENV{'ARCH'}\\mwcomutil.dll";
	    if (-e $regDLL)
            {
                sRunCmd("$ENV{'MATLAB'}\\runtime\\$ENV{'ARCH'}\\mwregsvr " . $regDLL);
                if ($? != 0)
                {
                    print("Error: Registration of COM support library failed.  Check the PATH to ensure that \nthe MATLAB shared libraries are present.\n");
                    return(1);
                }
            }

            $regDLL = "$ENV{'MATLAB'}\\bin\\$ENV{'ARCH'}\\mwcommgr.dll";
	    if (-e $regDLL)
            {
                sRunCmd("$ENV{'MATLAB'}\\runtime\\$ENV{'ARCH'}\\mwregsvr " . $regDLL);
                if ($? != 0) {
                    print("Error: Registration of COM support library failed.  Check the PATH to ensure that the \nMATLAB shared libraries are present.\n");
                    return(1);
                }
	    }
	    print "\n****************************************************************************************\n";
            print "\n";
        }
        # If the record for the installed compiler has a post_setup_hook
        # entry, call it (but only if install was successful).
        # Do not apply if in presetmode.
        #  
        my $post_setup_fcn = $record->{"post_setup_hook"};
        if ($post_setup_fcn && !$presetmode) {
            &$post_setup_fcn();
        }

        # Restore old $| (buffered output) setting:
        $| = $old_pipe;
        return(0);
    } else {
        # Restore old $| (buffered output) setting:
        $| = $old_pipe;
        return(1);
    }
}


