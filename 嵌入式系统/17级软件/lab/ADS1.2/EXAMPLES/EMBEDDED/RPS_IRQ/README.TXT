rps_irq
=======

This example illustrates an RPS-based interrupt-driven timer, suitable for
embedded applications.

This may be executed on an ARM Integrator board or (with some modification) 
under the ARMulator.
The ARMulator's default model of timer and interrupt controller peripherals 
(registers, base addresses, register offsets from base addresses) matches that 
implemented on an ARM Development (PID) board, but may be modified to match 
that of an Integrator board.  See examples\embedded\rps_irq.

The main C program is contained in main.c.  int_handler.c contains an interrupt
handler (written in C, using __irq) which handles timer interrupts from an RPS 
timer and interrupt controller.  The two C files main.c and int_handler.c can 
be compiled/linked together on their own and executed in the semihosting 
environment (build_a.bat).  Alternatively, the project can be built as an 
embedded application with no semihosting (builds b & c).

This example can be built in three different ways, in increasing order of 
complexity:
a. Non-embedded (semihosted), scatterloaded
b. Embedded, with ROM fixed at 0x0, scatterloaded
c. Embedded, ROM/RAM remapped, scatterloaded

These create an ELF image (rps_irq.axf) suitable for loading into an ARM
debugger.  A Motorola32 ROM image (rps_irq.m32) is also created, suitable for 
loading into a target, for example, downloading into the flash memory of an 
ARM Integrator board.

See embedded\embed\readme.txt for a description of the additional files used to
build an embeddable application (vectors.s, init.s, retarget.c, serial.c), and 
for the Memory Map diagrams for each different build.

Building for Thumb
------------------

The supplied batch files (build_a.bat, build_b.bat, build_c.bat) and supplied 
CodeWarrior project file (rps_irq.mcp) build ARM-only versions of this code.

To build ARM/Thumb interworking versions of this example, where the bulk
of the C code is compiled for Thumb, change the invocations of 'armcc'
into 'tcc -apcs /interwork', so that e.g. build_c.bat becomes:

armasm -g vectors.s
armasm -g -PD "ROM_RAM_REMAP SETL {TRUE}" init.s
armasm -g stack.s
armasm -g heap.s
REM Use the following two lines to build without using the serial port. 
armcc -apcs /interwork -c -g -O1 main.c -I..\include -DEMBEDDED -DROM_RAM_REMAP
tcc -apcs /interwork -c -g -O1 retarget.c
tcc -apcs /interwork -c -g -O1 uart.c -I..\include
REM Use the following two lines to build using the serial port. 
REM armcc -apcs /interwork -c -g -O1 main.c -I..\include -DEMBEDDED -DROM_RAM_REMAP -DUSE_SERIAL_PORT
REM tcc -apcs /interwork -c -g -O1 retarget.c -DUSE_SERIAL_PORT
tcc -apcs /interwork -c -g -O1 uart.c -I..\include
tcc -apcs /interwork -c -g -O1 serial.c -I..\include
armcc -apcs /interwork -c -g -O1 int_handler.c -I..\include
armlink vectors.o init.o main.o retarget.o uart.o serial.o stack.o heap.o int_handler.o -scatter scat_c.scf -o rps_irq.axf -entry 0x24000000 -info totals -info unused
fromelf rps_irq.axf -bin -o rps_irq.bin
fromelf rps_irq.axf -m32 -o rps_irq.m32

Note:
main.c must be compiled with armcc (not tcc), because it uses '__inline' MSR 
and MSR instructions.
int_handler.c must also be compiled with armcc (not tcc), because it uses '__irq'.

