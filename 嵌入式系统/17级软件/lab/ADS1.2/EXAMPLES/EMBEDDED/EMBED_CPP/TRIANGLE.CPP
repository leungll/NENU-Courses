/*                                                              */
/* triangle.cpp - Example driver program for Triangle class     */
/*                                                              */
/* Copyright (C) ARM Limited, 1999. All rights reserved.        */
/*                                                              */

/*
This example presents a basic C++ program with a simple class and shows how 
it can be made into an embedded application.  The default constructor for the 
class illustrates dynamic memory allocation.

This can be compiled/linked on its own and executed in the semihosting environment.
Alternatively, as an embedded application, it can be built with no semihosting
(#define EMBEDDED, or compile with -DEMBEDDED).

When built as an embedded application, this program uses __use_no_semihosting_swi 
to ensure that no functions which use semihosting SWIs are linked in from the C library.
*/


#include <stdio.h>
#include "tri.h"

#ifdef EMBEDDED
  extern "C" void init_serial_A(void);
#endif


int main(void)
{
#ifdef EMBEDDED
  #pragma import(__use_no_semihosting_swi)  /* ensure no functions that use semihosting SWIs 
                                               are linked in from the C library */
  #ifdef USE_SERIAL_PORT
    init_serial_A();            /* initialize serial A port */
  #endif
#endif

  printf("C++ Library Example\n\n");

  #ifdef EMBEDDED
    #ifdef ROM_RAM_REMAP
      printf("Embedded (ROM/RAM remap, no SWIs) version\n");
    #else
      printf("Embedded (ROM at 0x0, no SWIs) version\n");
    #endif
  #else
    printf("Normal (RAM at 0x8000, semihosting) version\n");
  #endif

  Triangle triangle;              // Instantiate an object.

  triangle.display();             // Display its default attributes.

  printf ("\n   Triangle is ");   // Determine and report triangle type.
  TriangleType type = triangle.type();
  if (type == EQUILATERAL)
    printf("equilateral; ");
  else if (type == ISOSCELES)
    printf("isosceles; ");
  else
    printf("scalene; ");

  double perim = triangle.perimeter();  // Determine and report perimeter.
  printf("its perimeter is %2.2f",perim);
  printf(" units.\n\n");
  return 0;
}

