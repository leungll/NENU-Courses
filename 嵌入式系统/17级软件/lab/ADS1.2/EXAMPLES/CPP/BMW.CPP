/*
 * bmw.cpp: This example illustrates virtual base classes with virtual functions.
 * It is modelled after Stroustup's BMW (Borders, Menu, Window) example from
 * section 10.10c of the A.R.M. (p233-235).
 *
 * The source is split into two parts to illustrate how armlink eliminates
 * all but one copy of the virtual function tables. Try armlink -map for
 * finer details.
 */

#include <stdio.h>
#include "bmw.h"

extern void gg();  // Defined in bmw1.c to force a second copy of the
                   // vtables for BMW to be generated. Later eliminated
                   // by armlink.

void g(BMW *pbmw)
{
    pbmw->f();     // should be BW::f():
    pbmw->g();     // should be MW::g();
    pbmw->h();     // should be BMW::h();
    pbmw->k();     // should be W::k();
}

void h(BMW *pbmw)
{
    MW *pmw = pbmw;
    pmw->f();      // should be BW::f()... 
}

BMW bmw;

static char *bw = (char *)&bmw.__B_BW;   // This exploits the implementation
static char *mw = (char *)&bmw.__B_MW;   // and is not portable C++...
static char *pw = (char *)&bmw.__V_W;

void MW::g(void)
{
    printf("MW::g(), this %s mw\n", (char *)this == mw ? "==" : "!=");
}

void BW::f(void)
{
    printf("BW::f(), this %s bw\n", (char *)this == bw ? "==" : "!=");
}

void BMW::h(void)
{
    printf("BMW::h(), this %s bmw\n",
        (char *)this == (char *)&bmw ? "==" : "!=");
}

void W::k(void)
{
    printf("W::k(), this %s pw\n", (char *)this == pw ? "==" : "!=");
}

int main()
{
    printf("\nExpected output from g():\n\
            BW::f(), this == bw\n\
            MW::g(), this == mw\n\
            BMW::h(), this == bmw\n\
            W::k(), this == pw\n");
    printf("........calling g()........\n");
    g(&bmw);
    printf("\nExpected output from h():\n\
            BW::f(), this == bw\n");
    printf("........calling h()........\n");
    h(&bmw);
    printf("\nExpected output from gg():\n\
            BW::f(), this != bw\n\
            MW::g(), this != mw\n\
            BMW::h(), this != bmw\n\
            W::k(), this != pw\n");
    printf("........calling gg()........\n");
    gg();
    return 0;
}

