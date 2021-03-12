Debug Communication Channel (DCC)
=================================

The example code in this directory illustrates the use of the Debug 
Communication Channel (DCC) as described in the ADS Developer Guide, chapter 8.
Please refer to this for details on how to build and execute these examples.

DCC is available on ARM cores which contain EmbeddedICE logic, e.g. ARM7TDMI, 
ARM9TDMI, etc.  DCC is accessed by the target via coprocessor 14 using the 
ARM instructions MCR and MRC.

The two assembler source files provided are:
outchan.s for 'Target to debugger communication'
inchan.s  for 'Debugger to target communication'

These implement a simple polling mechanism to send/receive bytes.

To build outchan.s, use:
armasm -g outchan.s
armlink outchan.o -o outchan.axf

To build inchan.s, use:
armasm -g inchan.s
armlink inchan.o -o inchan.axf

The file 'input' contains a test string for use with inchan.axf and armsd.

