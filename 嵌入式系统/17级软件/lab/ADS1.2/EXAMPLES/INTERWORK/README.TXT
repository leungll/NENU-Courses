interwork
=========

This directory contains two simple projects to illustrate ARM/Thumb interworking 
with C code.  CodeWarrior project files and script (batch) files are provided.

For details, see the Developer Guide, Chapter 3, "Interworking ARM and Thumb".

The two projects show:
1. An ARM main() calling a Thumb subroutine
2. A Thumb main() calling an ARM subroutine

In both cases, the linker pulls in the appropriate C library, and adds interworking 
veneers.  The added veneers are shown with the linker '-info veneers' option.


1. ARM (main) code calling a Thumb subroutine

The two files in this project are armmain.c and thumbsub.c.
Use the CodeWarrior project file ARM_to_Thumb.mcp to build the project.
Alternatively execute the command-line script armtothumb.bat.

armcc -c -g -O1 -apcs /interwork armmain.c
tcc   -c -g -O1 -apcs /interwork thumbsub.c
armlink armmain.o thumbsub.o -o armtothumb.axf -info veneers


2. Thumb (main) code calling an ARM subroutine

The two files in this project are thumbain.c and armsub.c.
Use the CodeWarrior project file Thumb_to_ARM.mcp to build the project.
Alternatively execute the command-line script thumbtoarm.bat:

tcc   -c -g -O1 -apcs /interwork thumbmain.c
armcc -c -g -O1 -apcs /interwork armsub.c
armlink thumbmain.o armsub.o -o thumbtoarm.axf -info veneers
