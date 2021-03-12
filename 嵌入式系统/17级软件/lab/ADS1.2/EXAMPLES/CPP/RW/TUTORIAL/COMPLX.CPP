/**************************************************************************
 *
 * complx.cpp - Complex Number example program. Section 14.3
 *
 ***************************************************************************
 *
 * Copyright (c) 1994-1999 Rogue Wave Software, Inc.  All Rights Reserved.
 *
 * This computer software is owned by Rogue Wave Software, Inc. and is
 * protected by U.S. copyright laws and other laws and by international
 * treaties.  This computer software is furnished by Rogue Wave Software,
 * Inc. pursuant to a written license agreement and may be used, copied,
 * transmitted, and stored only in accordance with the terms of such
 * license and with the inclusion of the above copyright notice.  This
 * computer software or any other copies thereof may not be provided or
 * otherwise made available to any other person.
 *
 * U.S. Government Restricted Rights.  This computer software is provided
 * with Restricted Rights.  Use, duplication, or disclosure by the
 * Government is subject to restrictions as set forth in subparagraph (c)
 * (1) (ii) of The Rights in Technical Data and Computer Software clause
 * at DFARS 252.227-7013 or subparagraphs (c) (1) and (2) of the
 * Commercial Computer Software – Restricted Rights at 48 CFR 52.227-19,
 * as applicable.  Manufacturer is Rogue Wave Software, Inc., 5500
 * Flatiron Parkway, Boulder, Colorado 80301 USA.
 *
 **************************************************************************/


#include <complex>
#include <utility>

#ifdef _RW_STD_IOSTREAM
#include <iostream>
#else
#include <iostream.h>
#endif
    
#ifndef _RWSTD_NO_NAMESPACE
using namespace std;
#endif

typedef complex<double> dcomplex;

//
// Return roots of a quadratic equation.
//

pair<dcomplex, dcomplex> quadratic (dcomplex a, dcomplex b, dcomplex c)
{
    dcomplex root = sqrt(b * b - 4.0 * a * c);
    a = a * 2.0;
    return make_pair ((-b + root) / a, (-b - root) / a);
}

int main ()
{
    dcomplex a(2, 3);
    dcomplex b(4, 5);
    dcomplex c(6, 7);
    
    pair<dcomplex, dcomplex> ans = quadratic(a, b, c);

    cout << "Roots are " << ans.first << " and " << ans.second  << endl;

    return 0;
}
