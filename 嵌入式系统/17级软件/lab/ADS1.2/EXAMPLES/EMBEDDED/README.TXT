Writing Code for ROM Examples
=============================

This directory contains three embeddable examples, configured to run on an 
ARM Integrator Board.  These compliment the material in the 
"Writing Code for ROM" chapter 6 of the ADS Developer Guide:

1) The "embed" directory illustrates a simple C program, suitable for embedded 
applications.  It calls subroutines to show the use of printf(), sprintf(), 
floating point printf() and malloc().

2) The "embed_cpp" directory presents a basic C++ program with a simple class 
and shows how it can be made into an embedded application.  The default 
constructor for the class illustrates dynamic memory allocation.

3) The "rps_irq" directory illustrates a RPS-based interrupt-driven timer, 
suitable for embedded applications.  It initializes and starts two RPS timers.  
When a timer expires, an interrupt is generated.  When an interrupt is 
detected, a message is displayed.

4) The "ledflash" directory shows a simple interrupt-driven LED flasher.


These examples can be built using the CodeWarrior project (.mcp) files or 
the batch files provided.  Alternatively, create your own make files.

The "embed", "embed_cpp" and "rps_irq" projects can be built in three different 
ways, in increasing order of complexity:

a. Non-embedded (build_a.bat)
b. Embedded, with ROM fixed at 0x0, scatterloaded (build_b.bat)
c. Embedded, ROM/RAM remapped, scatterloaded (build_c.bat)

The non-embedded ('hosted') versions of these examples can be compiled/linked 
on their own and executed in the semihosting environment under ARMulator, 
Angel or Multi-ICE.

The embedded versions of these examples are built with no semihosting, but can 
still be executed under ARMulator, Angel or Multi-ICE, either by 
loading the ARM Executable (.axf) file into a debugger, or downloading a plain 
binary (.bin) 'ROMmable' image into the FLASH memory of an ARM Integrator Board.

To ensure that no semihosting-SWI-using function is linked in from the C 
library, the embedded versions use __use_no_semihosting_swi.

