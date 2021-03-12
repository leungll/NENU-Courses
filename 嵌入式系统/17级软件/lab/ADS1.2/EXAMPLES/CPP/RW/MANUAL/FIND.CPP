/**************************************************************************
 *
 * find.cpp - Example program for finding an occurence of value in a 
 *            sequence. See Class Reference Section
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

#include <vector>
#include <algorithm>
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

   typedef vector<int,allocator<int> >::iterator iterator;
   int d1[10] = {0,1,2,2,3,4,2,2,6,7}; 
   //
   // Set up a vector.
   //
   vector<int,allocator<int> > v1(d1+0, d1+10);
   //
   // Try find.
   //
   iterator it1 = find(v1.begin(), v1.end(), 3);
   //
   // Try find_if.
   //
   iterator it2 = find_if(v1.begin(), v1.end(), bind1st(equal_to<int>(), 3));
   //
   // Try both adjacent_find variants.
   //
   iterator it3 = adjacent_find(v1.begin(), v1.end());
   iterator it4 = adjacent_find(v1.begin(), v1.end(), equal_to<int>());
   //
   // Output results.
   //
   cout << *it1 << " " << *it2 << " " << *it3 << " " << *it4 << endl;

   return 0;
}
