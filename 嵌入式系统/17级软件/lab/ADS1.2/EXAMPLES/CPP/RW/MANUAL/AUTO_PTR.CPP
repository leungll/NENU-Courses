/**************************************************************************
*
* auto_ptr.cpp - Example program of auto_ptr.  See Class Reference Section
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
#include <memory>

#ifdef _RW_STD_IOSTREAM
#include <iostream>
#else
#include <iostream.h>
#endif     

//
// A simple structure.
//

struct X
{
    X (int i = 0) : m_i(i) { }
    int get() const { return m_i; }
    int m_i;
};

int main ()
{

#ifndef _RWSTD_NO_NAMESPACE
  using namespace std;
#endif
  //
  // b will hold a pointer to an X.
  //
    auto_ptr<X> b(new X(12345));
    //
    // a will now be the owner of the underlying pointer.
    //
    auto_ptr<X> a = b;
    //
    // Output the value contained by the underlying pointer.
    //
    cout << a->get() << endl;
    //
    // The pointer will be delete'd when a is destroyed on leaving scope.
    //    
    return 0;
}
