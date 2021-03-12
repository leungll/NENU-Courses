/**************************************************************************
 *
 * distance.cpp - Example program for distance between two iterators.
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

#include<iterator>
#include<vector>

#ifdef _RW_STD_IOSTREAM
#include <iostream>
#else
#include <iostream.h>
#endif     

int main()
{
#ifndef _RWSTD_NO_NAMESPACE
   using namespace std;
#endif

   //
   // Initialize a vector using an array.
   //
   int arr[6] = {3,4,5,6,7,8};
   vector<int,allocator<int> > v(arr+0, arr+6);
   //
   // Declare a list iterator, s.b. a ForwardIterator.
   //
   vector<int,allocator<int> >::iterator itr = v.begin()+3;
   //
   // Output the original vector.
   //
   cout << "For the vector: ";
   copy(v.begin(), v.end(), ostream_iterator<int,char,char_traits<char> >(cout," "));
   cout << endl << endl;

   cout << "When the iterator is initialized to point to " << *itr << endl;
   //
   // Use of distance.
   //
   vector<int,allocator<int> >::difference_type dist = 0;
   distance(v.begin(), itr, dist);
   cout << "The distance between the beginning and itr is " << dist << endl;

   return 0;
}
