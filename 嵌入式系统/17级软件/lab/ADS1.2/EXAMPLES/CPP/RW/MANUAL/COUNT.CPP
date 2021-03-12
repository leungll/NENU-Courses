 /**************************************************************************
 *
 * count.cpp - Example program for counting number of elements in container. 
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

   int sequence[10] = {1,2,3,4,5,5,7,8,9,10};
   int i=0,j=0,k=0;
   //
   // Set up a vector.
   //
   vector<int,allocator<int> > v(sequence+0, sequence+10);

   count(v.begin(),v.end(),5,i);	// Count fives 
   count(v.begin(),v.end(),6,j);	// Count sixes 
   // 
   // Count all less than 8.
   //
   count_if(v.begin(), v.end(), bind2nd(less<int>(),8),k);

   cout << i << " " << j << " " << k << endl;

   return 0;
}
 
 
