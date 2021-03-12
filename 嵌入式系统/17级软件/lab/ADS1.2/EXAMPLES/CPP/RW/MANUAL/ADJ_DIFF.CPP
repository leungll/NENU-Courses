 /**************************************************************************
 *
 * adj_diff.cpp - Example program for adjacent_difference. 
 *                See Class Reference Section
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

#include <numeric>       // For adjacent_difference.
#include <vector>        // For vector.
#include <functional>    // For times.

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
   // Initialize a vector of ints from an array.
   //
   int arr[10] = {1,1,2,3,5,8,13,21,34,55};
   vector<int,allocator<int> > v(arr+0, arr+10);
   //
   // Two uninitialized vectors for storing results.
   //
   vector<int,allocator<int> > diffs(10), prods(10);
   //
   // Calculate difference(s) using default operator (minus).
   //
   adjacent_difference(v.begin(),v.end(),diffs.begin());
   // 
   // Calculate difference(s) using the times operator.
   //
   adjacent_difference(v.begin(), v.end(), prods.begin(), multiplies<int>());
   //
   // Output the results.
   //
   cout << "For the vector: " << endl << "     ";
   copy(v.begin(),v.end(),ostream_iterator<int,char,char_traits<char> >(cout," "));
   cout << endl << endl;

   cout << "The differences between adjacent elements are: " << endl << "    ";
   copy(diffs.begin(),diffs.end(), ostream_iterator<int,char,char_traits<char> >(cout," "));
   cout << endl << endl;

   cout << "The products of adjacent elements are: " << endl << "     ";
   copy(prods.begin(),prods.end(), ostream_iterator<int,char,char_traits<char> >(cout," "));
   cout << endl;

   return 0;
}
