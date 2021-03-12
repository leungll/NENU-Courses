/**************************************************************************
 *
 * equal.cpp - Example program for comparing two ranges for equivalence.
 *             See Class Reference Section
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

#include <algorithm>
#include <vector>
#include <functional>

#ifdef _RW_STD_IOSTREAM
#include <iostream>
#else
#include <iostream.h>
#endif     

int main ()
{
#ifndef _RWSTD_NO_NAMESPACE
   using namespace std;
#endif


   int d1[4] = {1,2,3,4};
   int d2[4] = {1,2,4,3};
   //
   // Set up two vectors.
   //
   vector<int,allocator<int> > v1(d1+0, d1+4), v2(d2+0, d2+4);
   //
   // Check for equality.
   //
   bool b1 = equal(v1.begin(), v1.end(), v2.begin());
   bool b2 = equal(v1.begin(), v1.end(), v2.begin(),equal_to<int>());
   //
   // Both b1 and b2 are false.
   //
   cout << (b1 ? "TRUE" : "FALSE")  << " " 
        << (b2 ? "TRUE" : "FALSE") << endl;
   return 0;
}
