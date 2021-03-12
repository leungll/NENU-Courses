Sorts Example
=============

This directory presents a Sorts example, which compares and contrasts an 
'insertion sort', 'shell sort', and 'quick sort' (the built-in C library sort).

To build this example, use the CodeWarrior project file supplied (sorts.mcp), 
alternatively, to build from the command-line, use:

armcc -c -g -O1 sorts.c
armlink sorts.o -o sorts.axf

This produces an ELF executable file (sorts.axf) which can be loaded into an 
ARM debugger.

The code as supplied compiles with:
Warning : C2809W: character sequence /* inside comment
sorts.c line 66

This is deliberate - to highlight the srand() function in the code.
This call must be commented out if you want to obtain reproducible results 
on subsequent runs (e.g. when benchmarking with different cores).

