C++ Examples
============

This directory contains (in the 'rw' subdirectory), the examples from the 
RogueWave manual and tutorial.

This directory also contains some simple C++ examples which can be compiled 
with the ARM or Thumb C++ compilers, armcpp or tcpp.

bmw     - creates virtual base classes with virtual functions.
newtst  - illustrates the use of 'new' and 'delete'.
shapes  - uses virtual functions and object constructors
strmtst - shows the use of C++ streams.

To build these examples, use the supplied CodeWarrior project files.
Alternatively, build from the command-line with e.g.:

armcpp -c -g shapes.cpp -o shapes.o
armlink shapes.o -o shapes.axf

This produces an ELF executable file which can be loaded into an ARM debugger.

