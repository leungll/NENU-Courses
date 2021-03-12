A PIC-PID Example
=================

Contents
1	INTRODUCTION
1.1	Quick Start
1.1.1	Building under Windows
1.1.2	Building under Unix
1.1.3	Executing the ROM image
1.2	Terms and abbreviations
2	THE EXAMPLE IN DETAIL
2.1	The kernel
2.1.1	Module services
2.1.2	Registering services
2.1.3	Calling services
2.1.4	Locating service modules
2.1.5	The CLI
2.1.6	Accessing the static base
2.2	Linking the kernel
2.2.1	Placement of data
2.2.2	The symdefs file
2.3	Application modules
2.3.1	The module header
2.3.2	The kernel entry vector
2.3.3	Linking an application module
2.4	Making a ROM image
2.5     Debugging the example


1 INTRODUCTION

This example system consists of a kernel at a fixed address in ROM (or FLASH) 
together with a collection of application modules that extend the functionality 
of the kernel. There is a separate RAM space managed by the kernel.

Application modules are poured into the memory following the kernel. The address 
at which a module might be loaded is unknown when the module is linked. Modules 
must, therefore, be position-independent (ROPI, PIC).

A module implements a set of named services. When the kernel starts, it scans 
the ROM (or FLASH) looking for module registration functions. Each module 
registration function calls the kernel to register one or more named services.

Services can be multiply instated and can call one another via the kernel. When 
a service is called, the kernel creates an instance of its static data and then 
passes control to the service, which may call back to the kernel. Modules must, 
therefore, have position-independent data (RWPI, PID).

The kernel is not position-independent and cannot be instated more than once.  
The kernel is linked at a fixed address. When it is linked, the linker creates 
a list of symbol definitions to input to the link steps that create application 
modules. When an application module calls the kernel, it does so by calling a 
fixed address defined when the kernel was linked.

1.1 Quick Start

To build and run this example, use the following ready-made scripts:

1.1.1 Building under Windows

Execute the following batch files sequence:
    clean
    bldkern
    bldapps
    bldrom

1.1.2 Building under Unix

Execute the Makefile with make

1.1.3 Executing the ROM image

The ROM image may be loaded into an ARM debugger (armsd or AXD) and 
executed under the ARMulator or on real target hardware.

For example, to execute the ROM image with armsd under the ARMulator use:
    getfile romimage 0x8000
    pc=0x8000
    sp=0x80000
    go

For AXD:
    select ‘File->Load Memory From File’ with load address 0x8000
    set the PC to 0x8000
    set the SP to 0x80000
    run the code

1.2 Terms and abbreviations

This document uses the following terms and abbreviations.
Term	Meaning
PIC	Position-independent code. Code that can execute wherever it is loaded.
PID	Position-independent data. An application has position-independent data 
	if its writable data segments can be loaded at any address.
ROPI	Read-only position independence. An application is ROPI if its read-only 
	segments can be loaded at any address.
RWPI	Read-write position independence. An application is RWPI if its writable 
	data segments can be loaded at any address.


2 THE EXAMPLE IN DETAIL

This section describes the example in detail.

2.1 The kernel

The kernel is a simple program written in C. It has a main function and it is 
linked at a fixed address. There is a single source file (kernel.c), and one 
header (kernel.h) shared with application modules. The kernel:
1. Provides a registration service to application modules.
2. Provides a module calling service to application modules.
3. Provides a printf() service to application modules.
Note: Any C library function that has no static state, or that has static state 
that is correctly owned by the kernel (rather than being separately instated for 
each client), can be exported.
4. Manages the available RAM (modelled as two static arrays).
5. On starting:
* Locates modules and calls their registration functions.
* Lists modules registered in order of registration.
* Enters a simple command loop that supports calling named modules.

2.1.1 Module services

In this model, an application module implements services of type:
    typedef void kernel_Service(unsigned sub_function, void *arg);

A module's service registration function (register_services) calls kernel_Register 
to register its services.

2.1.2 Registering services

You register a service function with the kernel by calling:
    int kernel_Register(
        char const *service_name, kernel_Service *service_function, unsigned bss_size);

For example:
    rc = kernel_Register("one.1", s1_1, my_bss_size);

How to discover an application's static data size (here BSS size) is explained 
in section 2.3.1, The module header.

2.1.3 Calling services

You call a registered service by calling:
    int kernel_Call( char const *service_name,  unsigned sub_function, void *arg);

For example:
    rc = kernel_Call("one.1", 255, (void *)data);

The kernel creates an instance of the service's static data. Alternatively, it 
could locate a statically allocated instance of the data, or locate the instance 
appropriate to this instantiation of the module. These details are crucial to 
real systems, but are not important to this example.

2.1.4 Locating service modules

The kernel locates a module offering services by scanning the memory for the 
string "*** Service ***". This string is immediately followed by the offset to 
the module's service registration function.

Creating an offset to a function is easy in assembly language, but not possible 
in C (which has only address types, not offset types).

2.1.5 The CLI

The toy CLI supports three single-letter commands:
* Q (or q)-quit from the CLI.
* L (or l)-list the registered services (name, address of service function, 
sizes of module data).
* C (or c)-call a registered service. C must be followed by the name of a service, 
then optionally by a sub-service number and an argument address. An omitted argument 
address defaults to NULL. An omitted sub-service number defaults to zero.

2.1.6 Accessing the static base

The static base register (SB) is r9, also called v6. To gain access to the static 
base register from a C program you can declare:
    __global_reg(6) char *sb;

You can declare it with any convenient 32-bit type (such as char *, void *, 
unsigned, int, ...). Thereafter, you can read and write sb like any other C variable.

Note: In the remainder of the compilation unit containing this declaration, the 
compiler will not use v6 (except where you refer to sb).
Note: Code compiled /rwpi makes no use of sb other than as the static base.

2.2 Linking the kernel

Essentially, the kernel is linked using:
    armlink -ro-base 0x8000 -rw-base 0x40000 kernel.o -symdefs kernel.sym ...

2.2.1 Placement of data

Because binary application modules will be concatenated with a plain binary derived 
from this program image to make a ROM image, it is important that the kernel's data 
be placed well away from end of the kernel code. Otherwise, creation of the kernel's 
ZI data may overwrite the application modules' code.

2.2.2 The symdefs file

The intended use of symdefs is:
* You write a list of symbols to be exported from the program being linked.
* The linker updates the definitions of the symbols whenever it is run.

If the list of symbols does not exist when armlink is run, armlink lists all the 
global symbols. You can then edit this to remove any you do not want to export.

2.3 Application modules

Application modules must be built ROPI and RWPI. With both the compiler and the 
assembler simply use:
    -apcs /ropi/rwpi
There are several issues associated with making application modules in C.
* How to define a module header that contains an offset to my service 
registration function?
* How to ensure that the module header is included when the module is linked, 
even if the linker removes unused sections?
* How to discover how much static data is used?
* How to call exported kernel functions at fixed addresses?

The first three issues are solved in a simple assembly language module header.  
The fourth requires a kernel entry vector to be linked into each application 
module.

2.3.1 The module header

The module header exports bss_size - the size of the module's static data. 
Because this is referred to in the module, inclusion of the header is assured.
In assembly language it is straightforward to create a PC-relative offset to a 
function, as is illustrated below.

For each execution region, the linker creates symbols describing the base, limit, 
and ZI length. You can use the linker-created symbol describing the length of the 
linker-created region ER_ZI (the name for the ZI execution region unless scatter 
loading is used) directly, as shown below.

	EXPORT    bss_size
	IMPORT    register_services
	IMPORT    |Image$$ER_ZI$$ZI$$Length|
application_header
	DCB       "*** Service ***", 0
	DCD       register_services - {PC}
bss_size
	DCD       |Image$$ER_ZI$$ZI$$Length|

None of the example applications use any statically initialized static data. 
How to handle this is left as an exercise.

2.3.2 The kernel entry vector

Application modules are built ROPI. They can be loaded at any address. It is 
clear, therefore, that a module cannot call the kernel directly using a BL 
instruction (C language function call).

There are two solutions to this problem:

1. For each kernel entry point the module uses, define a (const) function pointer 
variable, statically initialized to the entry point. This can be done in C, but 
there are some hazards. The initialization must be hidden from the compiler's 
value propagation (by, for example, initializing in a separate compilation unit). 
Otherwise what appears to be a call through a statically initialized function 
pointer may be converted into a direct call to a known symbol (which cannot work, 
because a position-independent BL cannot reach a fixed address).

In a C source separate from the source that uses the entry points declare 
function pointers like this:
    extern char kernel_Register;  /* Not really char, but as good as anything */
    typedef int kernel_RegisterFn(char const *, kernel_Service *, unsigned);
    kernel_RegisterFn * const k_register = &kernel_Register;

In your application module, you must use k_register(...) in place of 
kernel_Register(...).


2. Make a true entry vector in assembly language. This is the solution used in 
kveneer.s.  Within the application, there is the illusion of calling, say, 
kernel_Register. Indeed, the compiler generates a BL to kernel_Register. In the 
entry vector, kernel_Register labels an instruction that loads the fixed address 
of the real kernel_Register.

Define an entry vector that intercepts references to exported symbols. You do 
this using the symbol prefixes $Sub$$ (sub-class) and $Super$$ (super-class). 
For example:

	IMPORT |$$Super$$$$kernel_Register|
	EXPORT |$$Sub$$$$kernel_Register|
|$$Sub$$$$kernel_Register|
	LDR    pc, {PC}+4
	DCD    |$$Super$$$$kernel_Register|

Note: To include a dollar '$' character in a symbol or string, you must write 
two of the characters ('$$') in the source file for armasm. See kveneer.s

When this object is linked with your application object and the list of exported 
symbol definitions, armlink resolves references to kernel_Register to the 
sub-class symbol $Sub$$kernel_Register. References to the super-class symbol 
$Super$$kernel_register resolve to the original definition of kernel_Register 
from the symbol definition file. In this way, calls to kernel_Register are made 
PC-relative to the veneer, which loads the absolute address of the target 
function directly into the program counter.

2.3.3 Linking an application module

Essentially, an application module is linked using:
    armlink -ropi -ro-base 0 -rwpi -rw-base 0 -symdefs kveneer.o apphdr.o app1.o ...

The flags -ropi and -rwpi tell the linker that there are two separate execution 
regions, both position-independent. You must give an RW base address (-rw-base) 
otherwise -rwpi is ignored.

For position-independent regions, base addresses are significant only to debug 
tables, symbols, and linker maps. The linker uses the addresses you specify for 
all three purposes. For low-level debugging, a base of zero makes the arithmetic 
easy. To debug symbolically (at the source level or the machine level) you must 
load the regions at the addresses you specified to armlink.

2.4 Making a ROM image

Use FromELF to create binary versions of the kernel and each application, then 
concatenate the kernel binary with the application binaries using:

(Windows) copy /b kernel.bin+app1.bin+app2.bin+... romimage
(Unix) cat kernel.bin app1.bin app2.bin ... > romimage

2.5 Debugging the example

The kernel part of the ROM image can be debugged at C source-level as follows:
a.  Ensure the code is built with -g (to add debug symbols)

b.  Load the ROM image into the target (or ARMulator) with:
For armsd use: getfile romimage.bin 0x8000
For AXD, select ‘File->Load Memory From File’ with load address 0x8000

c.  Read the debug symbols from kernel.axf into the debugger with:
For armsd, use: readsyms kernel.axf
For AXD, select ‘File->Load Debug Symbols’ and specify kernel.axf

This will allow you to debug the kernel, but not the applications (which are ROPI).  
To debug the PI parts of the image at source level, you have to perform some 
additional steps (this works for AXD only, not armsd):

d.  
- Find out what addresses the PI parts of the image are loaded at.  You can do this 
by looking at the linkers -map file output.
- Link them again, at THIS address (remember, they are still really ROPI), to 
produce new .axf file(s) containing symbols at their correct addresses, e.g:
armlink -o app1.axf -ropi -ro-base 0xb3ec -rwpi -rw-base 0x4000000 -map -symbols -list app1.map kernel.sym kveneer.o app1.o apphdr.o
- Ignore the warning "Image does not have an entry point."
- Load the symbols from the app1.axf file into the debugger
- Repeat for app2.axf


