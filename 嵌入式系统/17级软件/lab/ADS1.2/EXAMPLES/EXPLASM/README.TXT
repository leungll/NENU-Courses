Additional Assembler Examples
=============================

The examples within the explasm directory show various techniques which may 
be useful when writing assembler code.  

Example utoa1.s shows Integer to String Conversion, but also shows use of 
the stack and a recursive function.  This example also uses files udiv10.s 
and utoatest.c

Example divc.c generates assembler code for dividing by a constant. One 
sample of this generated code is used in testing the above utoa1.s example.

Example random.s shows an assembler routine for generating pseudo-random 
numbers.  This example also uses the file randtest.c to test the example. 

Example bytedemo.c shows how byte order reversal can be achieved in just 
four instructions.


1      utoa1.s - Integer to String Conversion

This example shows how to:

* convert an integer to a string in ARM assembly language
* use a stack in an ARM assembly language program
* write a recursive function in ARM assembly language

Its dtoa entry point converts a signed integer to a string of decimal 
digits (possibly with a leading '-'); its utoa entry point converts an 
unsigned integer to a string of decimal digits.

1.1    Algorithm

Converts a signed integer to a decimal string, generates a '-' and negates 
the number if it is negative; then converts the remaining unsigned value.

Converts a given unsigned integer to a decimal string by dividing it by 10, 
yielding a quotient and a remainder. The remainder is in the range 0-9 and 
is used to create the last digit of the decimal representation. If the 
quotient is non-zero it is dealt with in the same way as the original 
number, creating the leading digits of the decimal representation; 
otherwise the process has finished.

1.2    Explanation

On entry, a2 contains the unsigned integer to be converted and a1 
addresses a buffer to hold the character representation of it.

On exit, a1 points immediately after the last digit written.

Both the buffer pointer and the original number have to be saved across 
the call to udiv10. This could be done by saving the values to memory. 
However, it turns out to be more efficient to use two 'variable' registers, 
v1 and v2 (which, in turn, have to be saved to memory).

Because utoa calls other functions, it must save its return link address 
passed in lr. The function therefore begins by stacking v1, v2 and lr 
using STMFD sp!, {v1,v2,lr}.

In the next block of code, a1 and a2 are saved (across the call to udiv10) 
in v1 and v2 respectively and the given number (a2) is moved to the first 
argument register (a1) before calling udiv10 with a BL Branch with Link) 
instruction.

On return from udiv10, 10 times the quotient is subtracted from the 
original number (preserved in v2) by two SUB instructions. The remainder 
(in v2) is ready to be converted to character form (by adding ASCII '0') 
and to be stored into the output buffer.

But first, utoa has to be called to convert the quotient, unless that is 
zero. The next four instructions do this, comparing the quotient (in a1) 
with 0, moving the quotient to the second argument register (a2) if not 
zero, moving the buffer pointer to the first argument/result register 
(a1), and calling utoa if the quotient is not zero.

Note that the buffer pointer is moved to a1 unconditionally: if utoa is 
called recursively, a1 will be updated but will still identify the next 
free buffer location; if utoa is not called recursively, the next free 
buffer location is still needed in a1 by the following code which plants 
the remainder digit and returns the updated buffer location (via a1).

The remainder (in a2) is converted to character form by adding '0' and is 
then stored in the location addressed by a1. A post-incrementing STRB is 
used which stores the character and increments the buffer pointer in a 
single instruction, leaving the result value in a1.

Finally, the function is exited by restoring the saved values of v1 and 
v2 from the stack, loading the stacked link address into pc and popping 
the stack using a single multiple-load instruction:

LDMFD sp!, {v1,v2,pc}

1.3    Creating a runnable example

You can run the utoa routine described here under armsd. To do this, you 
must assemble the example and the udiv10 function, compile a simple test 
harness written in C, and link the resulting objects together to create a 
runnable program.

Copy utua1.s, udiv10.s and utuatest.c from directory examples/explasm to 
your current working directory. Then issue the following commands to build 
and run the program.

armasm utoa1.s -o utoa1.o
armasm udiv10.s -o udiv10.o
armcc -c utoatest.c
armlink utoa1.o udiv10.o utoatest.o -o utoatest
armsd utoatest

The first two armasm commands assemble the utoa function and the udiv10 
function, creating object files utoa1.o and udiv10.o.

The armcc command compiles the test harness. The -c flag tells armcc to compile 
only (not to link).

The armlink command links the three objects with the ARM C library to create 
an executable (here called utoatest), which can be run under armsd.

Alternatively, use the CodeWarrior project file (utoa.mcp) provided.



1.5    Further Notes - Stacks in assembly language

In this example, three words are pushed on to the stack on entry to utoa 
and popped off again on exit. By convention, ARM software uses r13, 
usually called sp, as a stack pointer pointing to the last-used word of 
a downward growing stack (a so-called 'full, descending' stack). However, 
this is only a convention and the ARM instruction set supports equally all 
four stacking possibilities: FD, FA, ED, EA.

The instruction used to push values on the stack was:

STMFD  sp!, {v1, v2, lr}

The action of this instruction is as follows:

* Subtract 4 * number-of-registers from sp

* Store the registers named in {...} in ascending register number 
  order to memory at [sp], [sp,4], [sp,8] ...

The matching pop instruction was:

LDMFD  sp!, {v1, v2, pc}

Its action is:

* Load the registers named in {...} in ascending register number 
  order from memory at [sp], [sp,4], [sp,8] ...

* Add 4 * number-of-registers to sp.

Many, if not most, register-save requirements in simple assembly language 
programs can be met using this approach to stacks.

A more complete treatment of run-time stacks requires a discussion of:

* stack-limit checking (and extension)
* local variables and stack frames

In the utoa program, you must assume the stack is big enough to deal with 
the maximum depth of recursion, and in practice this assumption will be 
valid. The biggest 32-bit unsigned integer is about four billion, or ten 
decimal digits. This means that at most 10 x 3 registers = 120 bytes have 
to be stacked. Because the ARM Procedure Call Standard guarantees that 
there are at least 256 bytes of stack available when a function is called, 
and because we can guess (or know) that udiv10 uses no stack space, we can 
be confident that utoa is quite safe if called by an APCS-conforming 
caller such as a compiled C test harness.

The stacking technique illustrated here conforms to the ARM Procedure Call 
Standard only if the function using it makes no function calls. Since utoa 
calls both udiv10 and itself, it really ought to establish a proper stack 
frame. If you really want to write functions that can 'plug and play' together 
you will have to follow the APCS exactly.

However, when writing a whole program in assembly language you often know 
much more than when writing a program fragment for general, robust 
service. This allows you to gently break the APCS in the following way:

* Any chain of function/subroutine calls can be considered compatible with 
the APCS provided it uses less than 256 bytes of stack space.

So the utoa example is APCS compatible, even though it is not APCS 
conforming.

Be aware however that if you call any function whose stack use is unknown 
(but which is believed to be APCS-conforming), you court disaster unless 
you establish a proper APCS call frame and perform APCS stack limit 
checking on function entry.  



2     divc.c & divc_thumb.c - Division by a Constant

The ARM instruction set was designed following a RISC philosophy. One of 
the consequences of this is that the ARM core has no divide instruction, 
so divides must be performed using a subroutine. This means that divides 
can be quite slow, but this is not a major issue as divide performance is 
rarely critical for applications.

It is possible to do better than the general divide in the special case 
when the divisor is a constant. The divc.c example shows how the 
divide-by-constant technique works by generating ARM assembler code for 
divide-by-constant.

This section explains:

* how to improve on the general divide code for the case when the 
  divisor is a constant
* the simple case for divide-by-2^n using the barrel shifter
* how to use divc.c to generate ARM code for divide-by-constant

A version which generates Thumb assembler (divc_thumb.c) is also provided.

In the special case when dividing by 2^n, a simple right shift is all 
that is required.

There is a small caveat which concerns the handling of signed and unsigned 
numbers. For signed numbers, an arithmetic right shift is required, as 
this performs sign extension (to handle negative numbers correctly). In 
contrast, unsigned numbers require a 0-filled logical shift right:

    MOV    a2, a1, lsr #5      ; unsigned division by 32
    MOV    a2, a1, asr #10     ; signed division by 1024

2.1    Explanation of divide-by-constant ARM code

The divide-by-constant technique basically does a multiply in place of 
the divide. Given that:

        x/y == x * (1/y)
           
consider the underlined portion as a 0.32 fixed-point number (truncating 
any bits past the most significant 32). 0.32 means 0 bits before the 
decimal point and 32 after it.

        == (x * (2^32/y)) / 2^32
            
the underlined portion here is a 32.0 bit fixed-point number:

        == (x * (2^32/y)) >> 32

This is effectively returning the top 32-bits of the 64-bit product of x 
and (2^32/y).

If y is a constant, then (2^32/y) is also a constant.

For certain y, the reciprocal (2^32/y) is a repeating pattern in binary:

   y                  (2^32/y)

   2      10000000000000000000000000000000    #
   3      01010101010101010101010101010101    *
   4      01000000000000000000000000000000    #
   5      00110011001100110011001100110011    *
   6      00101010101010101010101010101010    *
   7      00100100100100100100100100100100    *
   8      00100000000000000000000000000000    #
   9      00011100011100011100011100011100    *
  10      00011001100110011001100110011001    *
  11      00010111010001011101000101110100
  12      00010101010101010101010101010101    *
  13      00010011101100010011101100010011
  14      00010010010010010010010010010010    *
  15      00010001000100010001000100010001    *
  16      00010000000000000000000000000000    #
  17      00001111000011110000111100001111    *
  18      00001110001110001110001110001110    *
  19      00001101011110010100001101011110
  20      00001100110011001100110011001100    *
  21      00001100001100001100001100001100    *
  22      00001011101000101110100010111010
  23      00001011001000010110010000101100
  24      00001010101010101010101010101010    *
  25      00001010001111010111000010100011

The lines marked with a '#' are the special cases 2^n, which have already 
been dealt with.  The lines marked with a '*' have a simple repeating 
pattern.

Note how regular the patterns are for y=2^n+2^m or y=2^n-2^m (for n>m):

  n     m       (2^n+2^m)       n       m       (2^n-2^m)

  1     0       3       1       0       1
  2     0       5       2       1       2
  2     1       6       2       0       3
  3     0       9       3       2       4
  3     1       10      3       1       6
  3     2       12      3       0       7
  4     0       17      4       3       8
  4     1       18      4       2       12
  4     2       20      4       1       14
  4     3       24      4       0       15
  5     0       33      5       4       16
  5     1       34      5       3       24
  5     2       36      5       2       28
  5     3       40      5       1       30
  5     4       48      5       0       31

For the repeating patterns, it is a relatively easy matter to calculate 
the product by using a multiply-by-constant method.

The result can be calculated in a small number of instructions by taking 
advantage of the repetition in the pattern.

The actual multiply is slightly unusual due to the need to return the top 
32 bits of the 64-bit result. It efficient to calculate just the top 32 
bits.

Consider this fragment of the divide-by-ten code (x is the input dividend 
as used in the above equations):

SUB  a1,  x,  x, lsr #2   ; a1 = x*%0.11000000000000000000000000000000
ADD  a1, a1, a1, lsr #4   ; a1 = x*%0.11001100000000000000000000000000
ADD  a1, a1, a1, lsr #8   ; a1 = x*%0.11001100110011000000000000000000
ADD  a1, a1, a1, lsr #16  ; a1 = x*%0.11001100110011001100110011001100
MOV  a1, a1, lsr #3       ; a1 = x*%0.00011001100110011001100110011001

The SUB calculates (for example):

a1 = x - x/4
   = x - x*%0.01
   = x*%0.11

Therefore, just five instructions are needed to perform the multiply.

A small problem is caused by calculating just the top 32 bits, as this 
ignores any carry from the low 32 bits of the 64-bit product. Fortunately, 
this can be corrected. A correct divide would round down, so the remainder 
can be calculated by:

x - (x/10)*10 = 0..9

By making good use of the ARM's barrel shifter, it takes just two ARM 
instructions to perform this multiply-by-10 and subtract. In the case 
when (x/10) is too small by 1 (if carry has been lost), the remainder 
will be in the range 10..19, in which case corrections must be applied. 
This test would require a compare-with-10 instruction, but this can be 
combined with other operations to save an instruction (see below).

When a lost carry is detected, both the quotient and remainder must be 
fixed up (one instruction each).

The following fragment should explain the full divide-by-10 code:

div10
; takes argument in a1
; returns quotient in a1, remainder in a2
; cycles could be saved if only divide or remainder is required
    SUB    a2, a1, #10             ; keep (x-10) for later
    SUB    a1, a1, a1, lsr #2
    ADD    a1, a1, a1, lsr #4
    ADD    a1, a1, a1, lsr #8
    ADD    a1, a1, a1, lsr #16
    MOV    a1, a1, lsr #3
    ADD    a3, a1, a1, lsl #2
    SUBS   a2, a2, a3, lsl #1      ; calc (x-10) - (x/10)*10
    ADDPL  a1, a1, #1              ; fix-up quotient
    ADDMI  a2, a2, #10             ; fix-up remainder
    MOV    pc, lr

The optimisation which eliminates the compare-with-10 instruction is to 
keep (x-10) for use in the subtraction to calculate the remainder. This 
means that compare-with-0 is required instead, which is easily achieved 
by adding an S (to set the flags) to the SUB opcode. This also means that 
the subtraction has to be undone if no rounding error occurred (which is 
why the ADDMI instruction is used).

2.2     How to generate divide-by-constant sequences

For suitable numbers, the details of the divide-by-constant technique can 
be avoided completely by using the divc program. This is supplied in 
ANSI C source in directory examples/explasm. You can compile it either 
with your host system's C compiler, or with armcc:

armcc divc.c

Alternatively, use the CodeWarrior project file (divc.mcp) provided.

To run the executable under armsd to generate the ARM assembler code for 
divide-by-10, type:

armsd divc 10

then enter go at the armsd prompt.
You can get command-line help by running divc with no arguments.

The output is suitable for immediate use as an armasm source file and can 
be seen in the example file udiv10.s for unsigned divide-by-10. It takes 
the unsigned argument in a1, and returns the quotient in a1 and the 
remainder in a2. It conforms fully to the APCS, but the remainder may not 
be available when called from C.

The range of values covered by (2^n-2^m) and (2^n+2^m) contains some 
useful numbers such as 7, 10, 24, 60.



3       random.s - Pseudo Random Number Generation

The file random.s shows how a 32-bit pseudo random number generator can 
be implemented efficiently in ARM Assembly Language.

3.1     Description

It is often necessary to generate pseudo random numbers, and the most 
efficient algorithms are based on shift generators with exclusive-or 
feedback (rather like a cyclic redundancy check generator). Unfortunately, 
the sequence of a 32-bit generator needs more than one feedback tap to be 
maximal length (ie. 2^32-1 cycles before repetition), so this example uses 
a 33 bit register with taps at bits 33 and 20.

The basic algorithm is:

* newbit:=bit33 EOR bit20
* shift left the 33 bit number
* put in newbit at the bottom

This operation is performed for all the newbits needed (ie. 32 bits). The 
entire operation can be coded compactly by making maximal use of the ARM's 
barrel shifter.

3.2     Using this example

This random number generation code is provided as random.s in directory 
examples/explasm. The C test program randtest.c (in the same examples 
directory) can be used to test the random number generator. 

First copy random.s and randtest.c from directory examples/explasm to 
your current directory, and enter the following commands to build and run 
the program:

armasm random.s -o random.o
armcc -c randtest.c
armlink randtest.o random.o -o randtest
armsd randtest

Alternatively, use the CodeWarrior project file (randtest.mcp) provided.



4       bytedemo.c - Byte Order Reversal

Changing the endianness of a word can be a common operation in certain 
applications-for example when communicating word-sized data as a stream 
of bytes to a receiver of the opposite endianness.

Example bytedemo.c shows a compact ARM Instruction Sequence to perform 
byte order reversal; ie. reversing the endianness of a word. This operation 
can be performed efficiently on the ARM, using just four instructions.

To compile the example program and run it under armsd, first copy 
bytedemo.c from directory examples/explasm to your current working 
directory, and then use the following commands:

armcc bytedemo.c -o bytedemo
armsd bytedemo

Alternatively, use the CodeWarrior project file (bytedemo.mcp) provided.

Note:
This program uses ANSI control codes, so should work on most terminal types 
under UNIX.  For a PC, you will need an ANSI driver installed, e.g. ANSI.SYS.
On HP-UX, use an XTERM terminal emulator (not HPTERM).

