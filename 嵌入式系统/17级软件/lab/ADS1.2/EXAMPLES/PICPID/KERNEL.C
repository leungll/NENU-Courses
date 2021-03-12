/*
 * Copyright (C) ARM Limited 1999. All rights reserved.
 */

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#include "kernel.h"

#define  SERVICE_NAME_LEN   32
#define  BSS_SIZE         4096

typedef struct Service Service;
struct Service
{
    char name[SERVICE_NAME_LEN];
    kernel_Service *fn;
    unsigned bss_size;
};

#define N_SERVICES  10
static Service services[N_SERVICES];
static unsigned n_services;

static char data_space[BSS_SIZE];
static unsigned data_space_used;

/* Define the static base register as v6 */
__global_reg(6) char *sb;


int kernel_Register(
    char const *service_name,
    kernel_Service *service_function,
    unsigned bss_size)
{
    if (n_services >= N_SERVICES)
    {
        return KERNEL_MEMFULL;
    }
    else
    {
        Service *s = services + n_services;
        ++n_services;

        strncpy(s->name, service_name, SERVICE_NAME_LEN);
        s->name[SERVICE_NAME_LEN-1] = 0;
        s->fn = service_function;
        s->bss_size = bss_size;

        return KERNEL_OK;
    }
}


int kernel_Call(
    char const *service_name,
    unsigned sub_function,
    void *arg)
{
    unsigned j;
    Service *s;

    for (j = 0;  j < n_services;  ++j)
    {
        s = services + j;
        if (strcmp(s->name, service_name) == 0)
        {
            break;
        }
    }

    if (j >= n_services)
    {
        return KERNEL_BADARGS;
    }
    else if (data_space_used + s->bss_size > BSS_SIZE)
    {
        return KERNEL_MEMFULL;
    }
    else
    {
        char *saved_sb = sb;
        sb = data_space + data_space_used;
        data_space_used += s->bss_size;

        s->fn(sub_function, arg);

        data_space_used -= s->bss_size;
        sb = saved_sb;

        return KERNEL_OK;
    }
}


extern char Image$$RO$$Limit;
typedef void ServiceInitFn(void);

static void find_and_register_services(void)
{
    char *base = &Image$$RO$$Limit;
    char *limit = base + 128*1024;   /* <= 128KB of apps */
    char *p;

    for (p = base;  p < limit;  ++p) 
    {
        if (*p == '*' && strcmp(p, "*** Service ***") == 0)
        {
            int *f = (int *)(p + 16);
            if (*f == 0)
            {
                break;
            }
            else
            {
                ((ServiceInitFn *)((char *)f + *f))();
            }
        }
    }
}


static void list_services(void)
{
    unsigned j;

    if (n_services > 0)
    {
        printf(" -Address- -bss- ---Name---\n");
        for (j = 0;  j < n_services;  ++ j)
        {
            Service *s = services + j;
            printf("0x%.8x %5u %s\n", (unsigned)s->fn, s->bss_size, s->name);
        }
    }
    else
    {
        printf("No services registered\n");
    }
}


static void call_service(char const *s)
{
    char sname[SERVICE_NAME_LEN];

    while (*s != 0 && !isspace(*s)) ++s;
    while (isspace(*s)) ++s;
    if (*s == 0)
    {
        printf("C service-name [sub-function] [argument]\n");
        return;
    }
    else
    {
        int j = 0, rc;
        char *rest;
        unsigned sub_fn, arg;

        while (!isspace(*s))
        {
            if (j < (SERVICE_NAME_LEN-1))
            {
                sname[j++] = *s;
            }
            ++s;
        }
        sname[j] = 0;
        sub_fn = strtoul(s, &rest, 0);
        arg = strtoul(rest, NULL, 0);
        
        rc = kernel_Call(sname, sub_fn, (void *)arg);

        if (rc == KERNEL_BADARGS)
        {
            printf("Service \"%s\" not found\n", sname);
        }
        else if (rc == KERNEL_MEMFULL)
        {
            printf("No memory left to call Service \"%s\"\n", sname);
        }
    }
}


static void do_commands(void)
{
    char cmdbuf[64];
    char *s;

    printf("\nCommands are Quit, List, Call\n\n");
    for (;;)
    {
        fputs("-> ", stdout);
        if (fgets(cmdbuf, sizeof(cmdbuf), stdin) == NULL)
        {
            break;
        }
        else
        {
            cmdbuf[sizeof(cmdbuf)-1] = 0;
        }
        for (s = cmdbuf;  *s != 0 && isspace(*s);)
        {
            ++s;
        }
        switch (*s)
        {
        case 'c':
        case 'C':
            call_service(s);
            break;
        case 'l':
        case 'L':
            list_services();
            break;
        case 'q':
        case 'Q':
            return;
        default:
            break;
        }
    }
}


int main(void)
{
    n_services = 0;
    data_space_used = 0;

    find_and_register_services();

    list_services();

    do_commands();

    return 0;
}
