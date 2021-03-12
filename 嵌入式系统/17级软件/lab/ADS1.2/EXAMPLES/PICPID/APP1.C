/*
 * Copyright (C) ARM Limited 1999. All rights reserved.
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
#define N_DATA  64
static int data[N_DATA];


/*
 * This "service" just initializes an array of integers
 * passed to it as an argument.
 */
static void s1_1(unsigned sub_service, void *arg)
{
    int j;
    int *p;

    printf("s1_1(%u, %.8p) at %.8p, sb = %.8p\n",
        sub_service, arg, s1_1, sb);
    
    if ((p = (int *)arg) != NULL)
    {
        for (j = 0;  j < N_DATA;  ++j)
        {
            p[j] = j + 1;
        }
    }
}


/*
 * This "service" calls "one.1" to initialize its data,
 * then checks that "one.1" initialized the right data.
 */
static void s1_2(unsigned sub_service, void *arg)
{
    int j, rc;

    printf("s1_2(%u, %.8p) at %.8p, sb = %.8p\n",
        sub_service, arg, s1_1, sb);
    
    rc = kernel_Call("one.1", 255, (void *)data);

    if (rc != KERNEL_OK)
    {
        printf("Call to \"one.1\" failed, rc = %d\n", rc);
    }
    else
    {
        for (j = 0;  j < N_DATA;  ++j)
        {
            if (data[j] != j+1)
            {
                break;
            }
        }
        if (j < N_DATA)
        {
            printf("Failed to initialise data[%u] - is %u, should be %u\n",
                j, data[j], j + 1);
        }
        else
        {
            printf("\"one.2\" completed successfully\n");
        }
    }
}


/*
 * This function is referenced from the application header that
 * define bss_size and the magic string "*** Service ***".
 */
void register_services(void)
{
    kernel_Register("one.1", s1_1, bss_size);
    kernel_Register("one.2", s1_2, bss_size);
}

