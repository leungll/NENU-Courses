Dhrystone Benchmarking and MIPs performance
===========================================


Dhrystone
---------

The Dhrystone program by Reinhold Weicker can be used to measure the integer 
processing performance of a system.

There are two different versions of the Dhrystone benchmark commonly quoted:
      Dhrystone 1.1 
      Dhrystone 2.1 
ARM quotes Dhrystone 2.1 figures.

The Dhrystone performance is calculated from:
      Dhrystones per sec = Processor clock * Number of Runs/Execution time

For the result to be valid, the Dhrystone code must be executed for at least 
two seconds.


Building the Dhrystone code
---------------------------

This directory contains:
- The Dhrystone program in three C files: dhry_1.c, dhry_2.c & dhry.h.
- A CodeWarrior project file (dhry.mcp), which you can use to build/run Dhrystone.
- An armsd.map file, which describes the memory configuration of your system 
(memory width & wait-states) to ARMulator.

As an alternative to the CodeWarrior project file, you can also build Dhrystone 
using the command-line in a single step:

    armcc -W -Otime -DMSC_CLOCK dhry_1.c dhry_2.c -o dhry.axf

or (equivalently) as separate compile & link steps:

    armcc -c -W -Otime -DMSC_CLOCK dhry_1.c dhry_2.c
    armlink dhry_1.o dhry_2.o -o dhry.axf -info totals

The '-Otime' switch results in code optimized for speed, rather than space 
(the default).  The '-DMSC_CLOCK' switch results in the C library function 
clock() being used for timing measurements.

To build a Thumb version, simply compile with 'tcc' instead of 'armcc'.

For benchmarking comparisons, it is advised not to use the '-g' switch to add 
debug information, because this reduces the amount of optimization which can be 
done.  Similarly, if you are using the CodeWarrior project file, ensure you use 
the 'Release' variant (maximum optimization, no debug) to create any benchmarks.

Note that dhry_1.c & dhry_2.c contains 'old-style' K&R function declarations, 
which produce warnings when compiled.  The warnings can be disabled with the 
compiler '-W' switch.  However, if these function declarations are updated to 
ANSI-C-style, and function prototypes added, then the ARM compiler can produce 
smaller, faster code (with fewer warnings), and consequently better benchmark 
figures.  A version of Dhrystone modified in this way is provided in the 
'dhryansi' subdirectory.


MIPS
----

The MIPS figures ARM (and most of the industry) quotes are "Dhrystone VAX MIPs".
The idea behind this measure is to compare the performance of a machine (in our 
case, an ARM system) against the performance of a reference machine.  The 
industry adopted the VAX 11/780 as the reference 1 MIP machine.  The VAX 11/780 
achieves 1757 Dhrystones per second.

The MIPS figure is calculated by measuring the number of Dhrystones per second 
for the system, and then dividing that figure by the number of Dhrystone per 
second achieved by the reference machine. 

So "80 MIPS" means "80 Dhrystone VAX MIPS", which means 80 times faster than a 
VAX 11/780. 

The reason for comparing against a reference machine is that it avoids the need 
to argue about differences in instruction sets.  RISC processors tend to have 
lots of simple instructions.  CISC machines like x86 and VAX tend to have fewer, 
more complex instructions.  If you just counted the number of instructions per 
second of a machine directly, then machines with simple instructions would get 
higher instructions-per-second results, but may not get the job done any faster. 
By comparing how fast a machine gets a given piece of work done against how fast 
other machines get that work done, the question of the different instruction 
sets is avoided.

The maximum performance of the ARM7 family is 0.9 Dhrystone VAX MIPS per MHz.
The maximum performance of the ARM9 family is 1.1 Dhrystone VAX MIPS per MHz.
The maximum performance of the ARM10 family is 1.3 Dhrystone VAX MIPS per MHz. 

These figures assume ARM code running from 32-bit wide, zero wait-state memory.  
If there are wait-states, or (for cores with caches) the caches are disabled, 
then the performance figures will be lower. 


CPI
---

To estimate how many ARM instructions are executed per second then simply divide 
the frequency by the average CPI (Cycles Per Instruction) for the core.

The average CPI for the ARM7 family is about 1.9 cycles per instruction.
The average CPI for the ARM9 family is about 1.5 cycles per instruction.
The average CPI for the ARM10 family is about 1.3 cycles per instruction.


