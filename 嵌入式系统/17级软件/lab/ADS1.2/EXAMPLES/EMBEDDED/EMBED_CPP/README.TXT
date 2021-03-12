embed_cpp
=========

This example presents a basic C++ program with a simple class and shows how it 
can be made into an embedded application.

The main C++ program is contained in "triangle.cpp".  This has a main() 
function, which calls subroutines to instantiate an object of class "Triangle", 
access some of its member functions and generate simple output.  
"triangle.cpp" is linked to the class implementation file, "tri.cpp". This 
file contains the implementation of the functions described in "tri.h". The 
default constructor for the triangle class also illustrates some simple 
dynamic memory allocation.
 
This C++ project can be compiled/linked and executed in the semihosting 
environment (see build a below).  Alternatively, the project can be built 
as an embedded application with no semihosting (builds b & c).

This example can be built in three different ways, in increasing order of 
complexity:
a. Non-embedded (semihosted), scatterloaded
b. Embedded, with ROM fixed at 0x0, scatterloaded
c. Embedded, ROM/RAM remapped, scatterloaded

To build the example, either:
- use the supplied batch files (build_a.bat, build_b.bat, build_c.bat), or 
- use the supplied CodeWarrior project file (embed_cpp.mcp, with 3 targets: 
  Semihosted, EmbeddedScatter, EmbeddedScatterRemap), or
- create your own make files.

These create an ELF image (embed.axf) suitable for loading into an ARM debugger.
A Motorola32 ROM image (embed.m32) is also created, suitable for loading into a 
target, for example, downloading into the flash memory of an ARM Integrator board.

See embedded\embed\readme.txt for a description of the additional files used to 
build an embeddable application (vectors.s, init.s, retarget.c and serial.c), 
and for the Memory Map diagrams for each different build.


Building for Thumb
------------------

The supplied batch files (build_a.bat, build_b.bat, build_c.bat) and 
supplied CodeWarrior project file (embed_cpp.mcp) build ARM-only versions of this code.

To build ARM/Thumb interworking versions of this example, where the bulk of the C code 
is compiled for Thumb, change the invocations of 'armcpp' into 'tcpp -apcs /interwork', 
so that e.g. build_c.bat becomes:

armasm -g vectors.s
armasm -g -PD "ROM_RAM_REMAP SETL {TRUE}" init.s
armasm -g stack.s
armasm -g heap.s
tcpp -apcs /interwork -c -g -O1 tri.cpp
tcpp -apcs /interwork -c -g -O1 triangle.cpp -DEMBEDDED -DROM_RAM_REMAP
tcc  -apcs /interwork -c -g -O1 retarget.c
tcc  -apcs /interwork -c -g -O1 uart.c -I..\include
tcc  -apcs /interwork -c -g -O1 serial.c -I..\include
armlink vectors.o init.o tri.o triangle.o retarget.o uart.o serial.o stack.o heap.o -scatter scat_c.scf -o embed.axf -entry 0x24000000 -info totals -info unused
fromelf embed.axf -bin -o embed.bin
fromelf embed.axf -m32 -o embed.m32

