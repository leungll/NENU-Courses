/*
 * bmw1.cpp: This example illustrates virtual base classes with virtual functions.
 * It is modelled after Stroustup's BMW (Borders, Menu, Window) example from
 * section 10.10c of the A.R.M. (p233-235).
 *
 * Here, we force a second copy of the vtables for BMW to be compiled.
 * armlink will eliminate all but one copy.
 */

#include "bmw.h"

static BMW bmw;

void gg()
{
    BMW *pbmw = &bmw;
    pbmw->f();     // should be BW::f():
    pbmw->g();     // should be MW::g();
    pbmw->h();     // should be BMW::h();
    pbmw->k();     // should be W::k();
}

