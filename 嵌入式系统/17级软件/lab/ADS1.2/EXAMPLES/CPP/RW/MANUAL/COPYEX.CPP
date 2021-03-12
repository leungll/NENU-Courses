/**************************************************************************
 *
 * copyex.cpp - Example program for copy. See Class Reference Section
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

   int d1[4] = {1,2,3,4};
   int d2[4] = {5,6,7,8};
   //
   // Set up three vectors.
   //
   vector<int,allocator<int> > v1(d1+0, d1+4), v2(d2+0, d2+4), v3(d2+0, d2+4);
   //
   // Set up one empty vector.
   //
   vector<int,allocator<int> > v4;
   //
   // Copy v1 to v2.
   //
   copy(v1.begin(), v1.end(), v2.begin());
   //
   // Copy backwards v1 to v3.
   //
   copy_backward(v1.begin(), v1.end(), v3.end());
   //
   // Use insert iterator to copy into empty vector.
   //
   copy(v1.begin(), v1.end(), back_inserter(v4));
   //
   // Copy all four to cout.
   //
   ostream_iterator<int,char,char_traits<char> > out(cout," ");
   copy(v1.begin(),v1.end(),out);
   cout << endl;
   copy(v2.begin(),v2.end(),out);
   cout << endl;
   copy(v3.begin(),v3.end(),out);
   cout << endl;
   copy(v4.begin(),v4.end(),out);
   cout << endl;
   
   return 0;
}
