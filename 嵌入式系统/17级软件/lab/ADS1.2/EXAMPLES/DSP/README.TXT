Supporting Files for DSP Headers
================================

This example directory contains a small source file that is required
in order to make full use of the header file <dspfns.h>.

<dspfns.h> defines a set of DSP-type primitive operations, such as
16-bit and 32-bit saturating arithmetic. The operations it provides
are similar to the ones used by the ITU for publishing
specifications of DSP algorithms. These operations require a small
amount of persistent static state, so a small source file is
required to be linked into code that uses <dspfns.h>.

(<dspfns.h> is intended as an example implementation. It
demonstrates how to use the inline assembly feature in the ARM
compilers, to construct intrinsic functions that provide C-language
access to the ARM9E's DSP capability. You _can_ use it in production
code, but this is not necessarily recommended.)

To build dspfns.c, use:
armcc [options] -c dspfns.c
with 'options' selected to match the rest of your build.
