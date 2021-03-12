/**************************************************************************
 *
 * accum.cpp - Example program for accumulate. See Class Reference Section
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

#include <compnent.h>
#include <numeric>    // For accumulate.
#include <vector>     // For vector.
#include <functional> // For times.

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

   //
   // Typedef for vector iterators.
   //
   typedef vector<int,allocator<int> >::iterator iterator;
   //
   // Initialize a vector using an array of integers.
   //
   int d1[10] = {1,2,3,4,5,6,7,8,9,10};
   vector<int,allocator<int> > v1(d1+0, d1+10);
   //
   // Accumulate sums and products.
   //
   int sum  = accumulate(v1.begin(), v1.end(), 0);
   int prod = accumulate(v1.begin(), v1.end(), 1, multiplies<int>());
   //
   // Output the results.
   //
   cout << "For the series: ";
   for(iterator i = v1.begin(); i != v1.end(); i++)
	  cout << *i << " ";

   cout << " where N = 10." << endl;
   cout << "The sum = (N*N + N)/2 = " << sum << endl;
   cout << "The product = N! = " << prod << endl;

   return 0;
}

