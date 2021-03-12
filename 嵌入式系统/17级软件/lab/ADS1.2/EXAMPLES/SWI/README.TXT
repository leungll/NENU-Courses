SWI Example
===========

This directory illustrates an example SWI handler as a standalone project.

The files provided are:

main.c    - contains the main() function, which installs the SWI vector in the 
            exception table, then calls some SWIs (0, 1, 2 & 3) via __swi()

ahandle.s - is the top-level SWI handler, written in assembler.  It is entered 
            via the SWI vector of the execption table.  Both ARM & Thumb SWIs 
            are identified and passed to chandle.c for processing.

chandle.c - is a second-level SWI handler, called from ahandle.s.  
            SWIs 0, 1, 2 & 3 execute some simple arithmetic.

swi.h     - contains the definitions of __swi(0), __swi(1), __swi(2) & __swi(3).
            __swi(3) has an associated __value_in_regs structure for returning 
            values in registers.


To build this example, use the CodeWarrior project file supplied (swi.mcp), 
alternatively, to build from the command-line, use:

armasm -g ahandle.s
armcc -c -g -O1 main.c
armcc -c -g -O1 chandle.c
armlink ahandle.o main.o chandle.o -o swi.axf

This produces an ELF executable file (swi.axf) which can be loaded into an 
ARM debugger.

For an overview of the principles of a SWI handler, see the ADS Developer Guide, 
chapter 5.

