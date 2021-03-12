/**************************************************************************
 *
 * inr_prod.cpp - Example program computes the inner product A X B of two
 *                ranges A and B. See Class Reference Section
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
#include <numeric>       // For inner_product.
#include <list>          // For list.
#include <vector>        // For vectors.
#include <functional>    // For plus and minus.

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
   // Initialize a list and an int using arrays of ints.
   //
   int a1[3] = {6, -3, -2};
   int a2[3] = {-2, -3, -2};

   list<int,allocator<int> >   l(a1+0, a1+3);
   vector<int,allocator<int> > v(a2+0, a2+3);
   //
   // Calculate the inner product of the two sets of values.
   //
   int inner_prod = inner_product(l.begin(), l.end(), v.begin(), 0);
   //
   // Calculate a wacky inner product using the same values.
   //
   int wacky = inner_product(l.begin(), l.end(), v.begin(), 0,
                             plus<int>(), minus<int>());
   //
   // Print the output.
   //
   cout << "For the two sets of numbers: " << endl << "     ";
   copy(v.begin(),v.end(),
        ostream_iterator<int,char,char_traits<char> >(cout," "));
   cout << endl << " and  ";
   copy(l.begin(),l.end(),
        ostream_iterator<int,char,char_traits<char> >(cout," "));

   cout << "," << endl << endl;
   cout << "The inner product is: " << inner_prod << endl;
   cout << "The wacky result is: " << wacky << endl;

   return 0;
}
