/*
 * Copyright (C) ARM Limited, 1998. All rights reserved.
 */

#include <stdio.h>
#include "swi.h"

unsigned *swi_vec = (unsigned *)0x08;

extern void SWI_Handler(void);


/*
Install_Handler() updates contents of 'vector' to contain
Branch instruction to reach 'routine' from 'vector'.
Function returns original contents of 'vector'.
*/
unsigned Install_Handler( unsigned routine, unsigned *vector )
{
    unsigned vec, old_vec;

    vec = (routine - (unsigned)vector - 8) >> 2;
    if (vec & 0xff000000)
    {
        printf("Handler greater than 32MBytes from vector");
    }
    vec = 0xea000000 | vec;     /* OR in 'branch always' code */

    old_vec = *vector;
    *vector = vec;
    return (old_vec);
}


/*
Note:  If you are using a processor with separate instruction and data caches, 
such as StrongARM, or ARM940T, you must ensure that cache coherence problems 
do not prevent the new contents of the vectors from being used. 
The data cache (or at least the entries containing the modified vectors) must 
be cleaned to ensure the new vector contents are written to main memory. You 
must then flush the instruction cache to ensure that the new vector contents 
are read from main memory.  For details of cache clean and flush operations, 
see the datasheet for your target processor.
*/


int main( void )
{
    int result1, result2;
    struct four_results res_3;

    Install_Handler( (unsigned) SWI_Handler, swi_vec );

    printf("result1 = multiply_two( 2, 4 ) = %d\n", result1 = multiply_two( 2, 4 ));

    printf("result2 = multiply_two( 3, 6 ) = %d\n", result2 = multiply_two( 3, 6 ));

    printf("add_two( result1, result2 ) = %d\n", add_two( result1, result2 ));

    printf("add_multiply_two( 2, 4, 3, 6 ) = %d\n", add_multiply_two( 2, 4, 3, 6 ));

    res_3 = many_operations( 12, 4, 3, 1 );

    printf("res_3.a = %d\n", res_3.a );
    printf("res_3.b = %d\n", res_3.b );
    printf("res_3.c = %d\n", res_3.c );
    printf("res_3.d = %d\n", res_3.d );

    return 0;
}

