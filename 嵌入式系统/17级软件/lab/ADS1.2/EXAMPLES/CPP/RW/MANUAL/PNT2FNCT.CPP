/**************************************************************************
 *
 * pnt2fnct.cpp - Example program of pointer to function.
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

#include<functional>
#include<deque>
#include<vector>
#include<algorithm>

#ifdef _RW_STD_IOSTREAM
#include <iostream>
#else
#include <iostream.h>
#endif     

#ifndef _RWSTD_NO_NAMESPACE
using namespace std;
#endif
//
// Create a function.
//
int factorial (int x)
{
  int result = 1;
  for(int i = 2; i <= x; i++)
    result *= i;
  return result;
}

int main ()
{
  //
  // Initialize a deque with an array of integers.
  //
  int init[7] = {1,2,3,4,5,6,7};
  deque<int,allocator<int> > d(init+0, init+7);
  //
  // Create an empty vector to store the factorials.
  //
  vector<int,allocator<int> > v((size_t)7);
  //
  // Transform the numbers in the deque to their factorials and store
  // in the vector.
  //
  transform(d.begin(), d.end(), v.begin(), ptr_fun(factorial));
  //
  // Print the results.
  //
  cout << "The following numbers: " << endl << "     ";
  copy(d.begin(), d.end(), ostream_iterator<int,char,char_traits<char> >(cout," "));

  cout << endl << endl;
  cout << "Have the factorials: " << endl << "     ";
  copy(v.begin(), v.end(), ostream_iterator<int,char,char_traits<char> >(cout," "));
  cout << endl;

  return 0;
}
