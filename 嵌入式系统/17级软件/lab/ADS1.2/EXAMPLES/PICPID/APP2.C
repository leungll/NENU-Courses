/*
 * Copyright (C) ARM Limited 1999. All rights reserved.
 *
 * A toy, position-independent application using kernel
 * services at fixed addresses.
 */

#include <stdio.h>
#include "kernel.h"

/* My bss size is defined by my application header... */
extern const unsigned bss_size;


/* Describe the static base register, needed for calling services */
/* This also avoids allocating SB (=v6) to any other purpose.     */
__global_reg(6) void *sb;


/* Each instance of these services gets a separate copy of my data */
#define N_DATA  100
static int data[N_DATA];


/*
 * This "service" calls itself recursively, until it fails.
 */
static void s2_1(unsigned sub_service, void *arg)
{
    int rc, *depth;

    printf("s1_2(%u, %.8p) at %.8p, sb = %.8p\n",
        sub_service, arg, s2_1, sb);
    
    if (sub_service == 0)
    {
        depth = data;
        *depth = 0;
    }
    else
    {
        depth = (int *)arg;
        ++(*depth);
    }

    rc = kernel_Call("two.1", 255, (void *)depth);

    if (rc != KERNEL_OK)
    {
        printf("Call to \"two.1\" failed, rc = %d at depth = %d\n", rc, *depth);
    }
    if (sub_service == 0)
    {
        printf("Calls to \"two.1\" unwound successfully\n");
    }
}


/*
 * This function is referenced from the application header that
 * define bss_size and the magic string "*** Service ***".
 */
void register_services(void)
{
    kernel_Register("two.1", s2_1, bss_size);
}

