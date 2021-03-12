ANSI-Dhrystone 
==============

This directory contains a MODIFIED version of the Dhrystone 2.1 Benchmark program.
The original version by Reinhold Weicker is provided in the 'dhry' directory.

The only changes which have been made are:
1) the 'old-style' K&R function declarations have been replaced with 
'ANSI-C-style' function declarations (in dhry_1.c and dhry_2,c), and
2) function prototypes have been added (in dhry.h)

These changes allow an ANSI-C compiler to produce more efficient code, with 
no warnings.

For an explanation of the MIPS & CPI figures, see the readme.txt file in the 
'dhry' directory.


Building the Dhrystone code
---------------------------

This directory contains:
- The Dhrystone program in three C files: dhry_1.c, dhry_2.c & dhry.h.
- A CodeWarrior project file (dhryansi.mcp), which you can use to build/run Dhrystone.

As an alternative to the CodeWarrior project file, you can also build Dhrystone 
using the command-line in a single step:

    armcc -Otime -DMSC_CLOCK dhry_1.c dhry_2.c -o dhry.axf

or (equivalently) as separate compile & link steps:

    armcc -c -Otime -DMSC_CLOCK dhry_1.c dhry_2.c
    armlink dhry_1.o dhry_2.o -o dhry.axf -info totals

The '-Otime' switch results in code optimized for speed, rather than space 
(the default).  The '-DMSC_CLOCK' switch results in the C library function 
clock() being used for timing measurements.

To build a Thumb version, simply compile with 'tcc' instead of 'armcc'.

For benchmarking comparisons, it is advised not to use the '-g' switch to add 
debug information, because this reduces the amount of optimization which can be 
done.  Similarly, if you are using the CodeWarrior project file, ensure you use 
the 'Release' variant (maximum optimization, no debug) to create any benchmarks.

