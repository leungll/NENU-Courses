Data Abort Handler
==================

"dabort.txt" contains the (design) documentation for the data abort handler.

The main source file is "dabort.s": with suitable -PreDefines or 
a corresponding "options-setting" file, it assembles to the data
abort veneer. This is described in detail in the documentation.

The "dabort.h" file contains definitions of some constants used
in the data abort veneer's interface to the rest of the system
- again, this is described in the documentation.

The "option.s" file is an example "options-setting" file.

For an overview of the principles of a Data Abort handler, see the 
ADS Developer Guide, chapter 5.
