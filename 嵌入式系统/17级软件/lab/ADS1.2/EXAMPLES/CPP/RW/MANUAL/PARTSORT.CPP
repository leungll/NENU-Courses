/**************************************************************************
 *
 * partsort.cpp - Example program of partial sort. See Class Reference Section
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

   int d1[20] = {17, 3,  5,  -4, 1, 12, -10, -1, 14, 7,
                 -6, 8, 15, -11, 2, -2,  18,  4, -3, 0};
   //
   // Set up a vector.
   //
   vector<int,allocator<int> > v1(d1+0, d1+20);
   //
   // Output original vector.
   //
   cout << "For the vector: ";
   copy(v1.begin(), v1.end(), ostream_iterator<int,char,char_traits<char> >(cout," "));
   //
   // Partial sort the first seven elements.
   //
   partial_sort(v1.begin(), v1.begin()+7, v1.end());
   //
   // Output result.
   //
   cout << endl << endl << "A partial_sort of seven elements gives: " 
        << endl << "     ";
   copy(v1.begin(), v1.end(), ostream_iterator<int,char,char_traits<char> >(cout," "));
   cout << endl;
   //
   // A vector of ten elements.
   //
   vector<int,allocator<int> > v2((size_t) 10, 0);
   //
   // Sort the last ten elements in v1 into v2.
   //
   partial_sort_copy(v1.begin()+10, v1.end(), v2.begin(), v2.end());
   //
   // Output result.
   //
   cout << endl << "A partial_sort_copy of the last ten elements gives: " 
        << endl << "     ";
   copy(v2.begin(), v2.end(), ostream_iterator<int,char,char_traits<char> >(cout," "));
   cout << endl;

   return 0;
}
