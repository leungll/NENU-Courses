/**************************************************************************
 *
 * mismatch.cpp - Example program of comparing elements from two sequences
 *                and returning the first two elements that don't 
 *                match each other. See Class Reference Section
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

   typedef vector<int,allocator<int> >::iterator  iterator;
   int d1[4] = {1,2,3,4};
   int d2[4] = {1,3,2,4};
   //
   // Set up two vectors.
   //
   vector<int,allocator<int> > vi1(d1+0, d1+4), vi2(d2+0, d2+4);
   //
   // p1 will contain two iterators that point to the first pair of
   // elements that are different between the two vectors.
   //
   pair<iterator, iterator> p1 = mismatch(vi1.begin(), vi1.end(), vi2.begin());	
   //
   // Find the first two elements such that an element in the
   // first vector is greater than the element in the second vector.
   //
   pair<iterator, iterator> p2 = mismatch(vi1.begin(), vi1.end(),
                                          vi2.begin(), less_equal<int>());
   //
   // Output results.
   //
   cout << *p1.first << ", " << *p1.second << endl;
   cout << *p2.first << ", " << *p2.second << endl;

   return 0;
}
