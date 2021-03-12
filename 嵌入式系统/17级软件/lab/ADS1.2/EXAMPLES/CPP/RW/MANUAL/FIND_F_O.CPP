/**************************************************************************
 *
 * find_f_o.cpp - Example program for finding a subsequence. 
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
#include <vector>
#include <algorithm>
#include <functional>

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

   typedef vector<int,allocator<int> >::iterator iterator;
   int d1[10] = {0,1,2,2,3,4,2,2,6,7};
   int d2[2] = {6,4};
   //
   // Set up two vectors.
   //
   vector<int,allocator<int> > v1(d1+0, d1+10), v2(d2+0, d2+2);
   //
   // Try both find_first_of variants.
   //
   iterator it1 = find_first_of(v1.begin(), v1.end(), v2.begin(), v2.end()); 

   find_first_of(v1.begin(), v1.end(), v2.begin(), v2.end(), equal_to<int>());
   //
   // Output results.
   //
   cout << "For the vectors: ";
   copy(v1.begin(),v1.end(), 
        ostream_iterator<int,char,char_traits<char> >(cout," " ));
   cout << " and ";
   copy(v2.begin(),v2.end(), 
        ostream_iterator<int,char,char_traits<char> >(cout," " ));
   cout << endl << endl
        << "both versions of find_first_of point to: "  << *it1;
   cout << endl; 
   
   return 0;
}
