 /**************************************************************************
 *
 * eqlrange.cpp - Example program for finding the valid range for insertion 
 *                of a value in a container. See Class Reference Section
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
   int d1[11] = {0,1,2,2,3,4,2,2,2,6,7};
   //
   // Set up a vector.
   //
   vector<int,allocator<int> > v1(d1+0, d1+11);
   //
   // Try equal_range variants.
   //
   pair<iterator,iterator> p1 = equal_range(v1.begin(),v1.end(),3);
   pair<iterator,iterator> p2 = equal_range(v1.begin(),v1.end(),2,less<int>()); 
   //
   // Output results.
   //
   cout << endl  << "The equal range for 3 is: "
        << "( " << *p1.first << " , " 
        << *p1.second << " ) " << endl << endl; 

   cout << endl << "The equal range for 2 is: "
        << "( " << *p2.first << " , " 
        << *p2.second << " ) " << endl; 

   return 0;
}
