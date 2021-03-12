ledflash
========

This is a simple interrupt-driven LED flasher, which runs on an ARM Integrator 
Board.  It reads the switches on the board to determine the LED flash speed 
and pattern.  The resulting image is intended to be downloaded into Flash.

It features:
- a main application program, written in C
- an interrupt handler, written in C
- init code and exception vectors, written in ARM assembler
- ROM/RAM remapping on reset

Build the (debug) images using the supplied batch-file (build.bat) or the 
CodeWarrior project file (ledflash.mcp).  Alternatively, create your own 
makefile.

This creates an ELF image (ledflash.axf) suitable for loading into an ARM
debugger.  A Motorola32 ROM image (ledflash.m32) is also created, suitable
for downloading into the flash memory of an Integrator board.


Building for Thumb
------------------

The supplied batch file (build.bat) and CodeWarrior project file
(ledflash.mcp) build ARM-only versions of this code.

To build ARM/Thumb interworking versions of this example, where the bulk
of the C code is compiled for Thumb, change the invocations of 'armcc'
into 'tcc -apcs /interwork', so that e.g. build.bat becomes:

armasm -g vectors.s
armasm -g -PD "ROM_RAM_REMAP SETL {TRUE}" init.s
armasm -g stack.s
armasm -g heap.s
tcc -apcs /interwork -c -g -O1 main.c -I..\include
armcc -apcs /interwork -c -g -O1 int_handler.c -I..\include
tcc -apcs /interwork -c -g -O1 retarget.c
armlink vectors.o init.o main.o int_handler.o retarget.o stack.o heap.o -scatter scat.scf -o ledflash.axf -entry 0x24000000 -info totals -info unused
fromelf ledflash.axf -m32 -o ledflash.m32

Note:
int_handler.c must be compiled with armcc (not tcc), because it uses '__irq'.


Downloading to Flash
--------------------

There are two ways to download the ledflash image to the flash memory of an 
ARM Integrator board, so that you can execute/debug the image at source level.

Either:
a) Use the debugger's File->Flash-download feature, which uses flash.li/.bi.
This requires a plain binary image to be built with:
  fromelf ledflash.axf -bin -o ledflash.bin
See 'AXD and armsd Debuggers Guide', Appendix D, "Using the Flash Downloader".

Or:
b) follow the steps 1-8 below to download using the Integrator's Boot Loader:
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

5. Transfer the 'ledflash.m32' file via the serial cable using the terminal
   tools.  In Hyperterminal this is done by selecting 
   'Transfer->Send Text File' from the menu and navigating to the
   ledflash.m32 file.

6. Once the image has loaded (approx 5 seconds) terminate the flash
   transfer by pressing Ctrl-C.

7. Ensure switch 1 is returned to the 'OFF' position.

8. The image is now present in flash and will be executed when the board
   is reset.  Toggle the board's switches to change the speed and pattern
   of the flashing LEDs.
   

Memory Map
----------

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
This is how the ROM/RAM remapping is implemented on an ARM Integrator Board.

