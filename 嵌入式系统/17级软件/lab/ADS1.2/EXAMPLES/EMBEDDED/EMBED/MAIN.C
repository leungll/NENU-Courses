/*
** Copyright (C) ARM Limited, 2001. All rights reserved.
*/


/*
** This example illustrates a simple C program, suitable for embedded 
** applications.  This has a main() function, which calls subroutines to show
** the use of printf(), sprintf(), floating point and malloc().
**
** This can be compiled/linked on its own and executed in the
** semihosting environment.
**
** Alternatively it can be built as an embedded application with no semihosting
**      #define EMBEDDED, or compile with -DEMBEDDED
**
** When built as an embedded application, this program uses 
** __use_no_semihosting_swi to ensure that no functions which use 
** semihosting SWIs are linked in from the C library.
*/


#include <stdio.h>
#include <stdlib.h>
#include <math.h>


void demo_printf(void)
{
  printf("Hello World\n");
}


void demo_sprintf(void)
{
  int x;
  char buf[20];

  for (x=1; x<=5; x++)
  {
    sprintf(buf, "Hello Again %d\n", x);
    printf("%s", buf);
  }
}


float f1=3.1415926535898, f2=1.2345678;


void demo_float_print(void)
{
  double f3=3.1415926535898, f4=1.2345678;

  printf("Float: f1 x f2 = %f x %f = %f\n", f1, f2, f1*f2);
  printf("Double: f3 x f4 = %14.14f x %14.14f = %14.14f\n", f3, f4, f3*f4);
}


int  *p;

void demo_malloc(void)
{
  p = (int *)malloc(0x1000);

  if (p==NULL)
  {
    printf("Out of memory\n");
  }
  else
  {
    printf("Allocated p at %p\n", (void *)p);
  }

  if (p)
  {
    free(p);
    printf("Freed p\n");
  }
}


#ifdef EMBEDDED
extern void init_serial_A(void);
#endif

int main(void)
{
#ifdef EMBEDDED
  #pragma import(__use_no_semihosting_swi)  // ensure no functions that use semihosting 
                                            // SWIs are linked in from the C library 
#ifdef USE_SERIAL_PORT
  init_serial_A();            // initialize serial port A
#endif
#endif

  printf("C Library Example\n");

#ifdef EMBEDDED
#ifdef ROM_RAM_REMAP
  printf("Embedded (ROM/RAM remap, no SWIs) version\n");
#else
  printf("Embedded (ROM at 0x0, no SWIs) version\n");
#endif
#else
  printf("Normal (RAM at 0x8000, semihosting) version\n");
#endif

  demo_printf();
  demo_sprintf();
  demo_float_print();
  demo_malloc();

  return 0;
}

