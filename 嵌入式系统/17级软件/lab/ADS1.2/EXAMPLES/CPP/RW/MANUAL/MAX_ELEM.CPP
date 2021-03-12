/**************************************************************************
 *
 * max_elem.cpp - Example program for finding maximum value in a range.
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

   typedef vector<int,allocator<int> >::iterator iterator;							   	 
   int d1[5] = {1,3,5,32,64}; 			 				
   // 
   // Set up vector.
   //
   vector<int,allocator<int> > v1(d1+0, d1+5);	 
   //
   // Find the largest element in the vector.
   //
   iterator it1 = max_element(v1.begin(), v1.end());
   // 
   // Find the largest element in the range from
   // the beginning of the vector to the 2nd to last.
   //
   iterator it2 = max_element(v1.begin(), v1.end()-1, less<int>());   
   // 
   // Find the smallest element.
   //
   iterator it3 = min_element(v1.begin(), v1.end());  
   // 
   // Find the smallest value in the range from
   // the beginning of the vector plus 1 to the end.
   //
   iterator it4 = min_element(v1.begin()+1, v1.end(), less<int>());      

   cout << *it1 << " " << *it2 << " " << *it3 << " " << *it4 << endl;
 
   return 0;
}
	
