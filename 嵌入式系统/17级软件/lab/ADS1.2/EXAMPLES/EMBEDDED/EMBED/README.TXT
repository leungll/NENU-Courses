embed
=====

This example illustrates a simple C program, suitable for embedded 
applications.

The main C program is contained in main.c.  This has a main() function, which 
calls subroutines to show the use of printf(), sprintf(), floating point 
printf() and malloc().  This can be compiled/linked on its own and executed 
in the semihosting environment (see build a below).  Alternatively, the project 
can be built as an embedded application with no semihosting (builds b & c).

This example can be built in three different ways, in increasing order of
complexity:
a. Non-embedded (semihosted), scatterloaded
b. Embedded, with ROM fixed at 0x0, scatterloaded
c. Embedded, ROM/RAM remapped, scatterloaded

For options b and c, all hard coded addresses are located in the scatterfile

To build the example, either:

- use the supplied batch files (build_a.bat, build_b.bat, build_c.bat), or 

- use the supplied CodeWarrior project file (embed.mcp, with 3 targets:
  Semihosted, EmbeddedScatter, EmbeddedScatterRemap), or

- create your own make files.

These create an ELF image (embed.axf) suitable for loading into an ARM
debugger.  A Motorola32 ROM image (embed.m32) is also created, suitable
for loading into a target, for example, downloading into the flash memory
of an ARM Integrator board.

To convert it into an embeddable application, additional files are provided:

1. vectors.s contains exception vectors and exception handlers. Where there
   is ROM fixed at 0x0 (build_b), these are hard-coded at 0x0.
   Where ROM/RAM remapping occurs (build_c), these are copied from ROM to
   RAM.

2. init.s performs ROM/RAM remapping (if required), initializes stack
   pointers and interrupts for each mode, and finally branches to __main
   in the C library (which eventually calls main()).

3. retarget.c implements a 'retarget' layer for low-level I/O.  Typically,
   this would contain your own target-dependent implementations of
   fputc(), ferror(), etc.  This example provides implementations of
   fputc(), ferror(), _sys_exit(), _ttywrch() and
   __user_initial_stackheap().  Here, semihosting SWIs are used to
   display text onto the console of the host debugger.  This mechanism is
   portable across ARMulator, Angel and Multi-ICE.
   Alternatively, to output characters from the serial port of an ARM
   Integrator Board (see serial.c), use '#define USE_SERIAL_PORT' or 
   compile with '-DUSE_SERIAL_PORT'.

4. serial.c implements a simple (polled) RS232 serial driver for the ARM
   Integrator Board.  It outputs single characters on Serial
   Port A at 38400 Baud, 8 bit, no parity, 1 stop bit.  To monitor the
   characters output, use a null-modem cable to connect Serial Port A to
   an RS232 terminal or PC running a terminal emulator, e.g. HyperTerminal.

5. In addition the files stack.s and heap.s are used to create dummy variables
   which are placed in memory by the scatter load file. These can then be used
   to place the stack and heap respectively.

6. Finally uart.c instantiates a struction corresponding to the layout of
   the uart registers. This structure is located in memory by the scatter load
   file.


To ensure that no functions which use semihosting SWIs are linked in from the 
C library, __use_no_semihosting_swi is used for the 2 'embeddable' builds.


The 3 different builds can be executed either on the ARMulator, or on real 
hardware (e.g. Integrator board via Multi-ICE).  To run the examples on real
hardware, please note:
 i. For Semihosted (build_a) build targets, set $top_of_memory to a suitable 
value via the debugger.  The (unexpanded) Integrator CM has 256KB of SSRAM 
fitted, so set $top_of_memory=0x40000.  If additional SDRAM is fitted, set 
$top_of_memory appropriately.  It is not necessary to set $top_of_memory for 
the other builds, because they implement __user_initial_stackheap().
 ii. For EmbeddedScatter (build_b.bat) and EmbeddedScatterRemap (build_c.bat)
build targets, set $vector_catch=0 to prevent exceptions being caught, and to
free up a watchpoint unit in the EmbeddedICE Logic.
 iii. EmbeddedScatterRemap (build_c.bat) is intended to be downloaded into Flash 
(see below).


Building for Thumb
------------------

The supplied batch files (build_a.bat, build_b.bat, build_c.bat) and supplied 
CodeWarrior project files build ARM-only versions of this code.

To build ARM/Thumb interworking versions of this example, where the bulk
of the C code is compiled for Thumb, change the invocations of 'armcc'
into 'tcc -apcs /interwork', so that e.g. build_c.bat becomes:

armasm -g vectors.s
armasm -g -PD "ROM_RAM_REMAP SETL {TRUE}" init.s
armasm -g stack.s
armasm -g heap.s
REM Use the following two lines to build without using the serial port. 
tcc -apcs /interwork -c -g -O1 main.c -DEMBEDDED -DROM_RAM_REMAP
tcc -apcs /interwork -c -g -O1 retarget.c
REM Use the following two lines to build using the serial port. 
REM tcc -apcs /interwork -c -g -O1 main.c -DEMBEDDED -DROM_RAM_REMAP -DUSE_SERIAL_PORT
REM tcc -apcs /interwork -c -g -O1 retarget.c -DUSE_SERIAL_PORT
tcc -apcs /interwork -c -g -O1 uart.c -I..\include
tcc -apcs /interwork -c -g -O1 serial.c -I..\include
armlink vectors.o init.o main.o retarget.o uart.o serial.o stack.o heap.o -scatter scat_c.scf -o embed.axf -entry 0x24000000 -info totals -info unused
fromelf embed.axf -bin -o embed.bin
fromelf embed.axf -m32 -o embed.m32


Downloading to Flash
--------------------

Follow the instrictions below to download the 'Embedded, scatterloaded' 
examples 'build_b' and 'build_c' to the flash memory of an ARM Integrator 
board, so that you can execute/debug the image at source level.

Use the debugger's File->Flash-download feature, which uses flash.li/.bi.
This requires a plain binary image to be built with:
  fromelf embed.axf -bin -o embed.bin
See 'AXD and armsd Debuggers Guide', Appendix D, "Using the Flash Downloader".

Alternatively:

Follow the steps 1-8 below to download using the Integrator's Boot Loader:
These steps require a terminal emulator such as 'HyperTerminal'.

1. Connect the Integrator board to the host computer using a null modem
   serial cable.

2. Invoke the terminal emulator and ensure it has the following settings:
   - Baud rate 38400
   - Data bits 8
   - No parity
   - Stop bits 1
   - Flow control Xon/Xoff

3. Ensure switches 1 and 4 on the Integrator board are in the 'ON'
   position and reset the board.

4. Enter 'l' to load flash image at the Boot Loader prompt in the terminal
   window.

5. Transfer the 'embed.m32' file via the serial cable using the terminal
   tools.  In Hyperterminal this is done by selecting 
   'Transfer->Send Text File' from the menu and navigating to the
   embed.m32 file.

6. Once the image has loaded (approx 25 seconds) terminate the flash
   transfer by pressing Ctrl-C.

7. Ensure switch 1 is returned to the 'OFF' position.

8. The image is now present in flash and will be executed when the board
   is reset.  Output from the image will be sent to the terminal window
   only if the image was built using the -USE_SERIAL_PORT option.
   Otherwise output must be viewed using AXD with the image debug
   symbols via a connection to the board such as Multi-Ice.


Memory Maps
-----------

The following diagrams illustrate the Memory Maps for this example, for each 
different build:

build_a.bat:
                  0x08000000 (ARMulator) or
     +----------+ 0x00040000 (Integrator board)
     |  stack   | 
     |    VV    |
     ~          ~
     |    ^^    |
     |   heap   |
     +----------+ Image$$ZI$$Limit
     |  ZI data |
     +----------+
     |  RW data |
     +----------+
     |          |
     |          |
     | program  |
     | (RO+RW)  |
     |          |
     |          |
     +----------+ 0x8000


build_b.bat

 --- +----------+ 0x28080000 (stack_base)
     |  stack   |
     |    VV    |
     |          |
     |    ^^    |
 RAM |   heap   |
     +----------+ Image$$RAM$$ZI$$Limit (heap_base)
     |  ZI data |
     +----------+
     |  RW data |
 --- +----------+ 0x28000000
     ~          ~
     |          |
 ROM | program  |
     | (RO+RW)  |
     |          |
     |          |
 --- +----------+ 0x0


build_c.bat:

At moment of reset:              Following ROM/RAM remapping:

 --- +----------+ 0x28080000       --- +----------+ 0x28080000
     |          |                      |          | 
     |          |                      |          | 
 RAM |          |                  RAM |          | 
     |          |                      |          | 
     |          |                      |          |
  -- +----------+ 0x28000000       --- +----------+ 0x28000000
     |          |                      |          |
     | program  |                      | program  | 
 ROM | (RO+RW)  |                  ROM | (RO+RW)  |
     |          |                      |          |
     |          |                      |          |
 --- +----------+ 0x24000000  +------->+----------+ 0x24000000
     ~  other   ~             |        |          |
     | RAM/ROM  |             |        |          |
     ~ & I/O    ~             |        |          |
 --- +----------+             |    --- +----------+ 0x40000
     |          |             |        |  stack   |
     |          |             |        |    vv    |
     |          |             |        |          |  
     |          |             |        |    ^^    |
     |          |             |        |   heap   |
 ROM | program  |             |   RAM  +----------+
     | (RO+RW)  |             |        | ZI data  |
     |          |             |        +----------+  
     |          |             |        | RW data  |
     |          |     branch  |        +----------+
     |          |-------------+        | vectors  |
 --- +----------+ 0x0              --- +----------+ 0x0

On reset, an aliased copy of the 'real' ROM at 0x24000000 appears at 0x0.
Following reset, RAM is remapped to address 0x0, by writing to REMAP register.
This is how the ROM/RAM remapping is implemented on an ARM Integrator board.

