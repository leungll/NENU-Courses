Assembler Examples
==================

This directory contains some examples of assembler level programming for the ARM.

These examples are described in more detail in the ADS Assembler Guide (chapter 2)
and the ADS Developer Guide (section 5.4.3).

To build these examples, use the supplied CodeWarrior project files.
Alternatively, build from the command-line with e.g.:

armasm -g armex.s -o armex.o
armlink armex.o -o armex.axf

This produces an ELF executable file which can be loaded into an ARM debugger.

