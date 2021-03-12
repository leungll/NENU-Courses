/*
 * Copyright (C) ARM Limited 1999. All rights reserved.
 */

#ifndef kernel_h
#define kernel_h

/*
 * The type of a kernel service function.
 */
typedef void kernel_Service(unsigned sub_function, void *arg);

/*
 * Return codes from kernel functions..
 */
#define KERNEL_OK      0
#define KERNEL_BADARGS 1
#define KERNEL_MEMFULL 2

int kernel_Register(
    char const *service_name,
    kernel_Service *service_function,
    unsigned bss_size);
/*
 * Return KERNEL_OK if registered successfully.
 * Return KERNEL_MEMFULL if the table fills up.
 */

int kernel_Call(
    char const *service_name,
    unsigned sub_function,
    void *arg);
/*
 * Return KERNEL_OK if called successfully.
 * Return KERNEL_BADARGS if not found.
 * Return KERNEL_MEMFULL if out of static data space.
 */

#endif
