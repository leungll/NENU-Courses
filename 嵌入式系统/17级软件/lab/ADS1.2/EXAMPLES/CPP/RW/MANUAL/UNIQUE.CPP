/**************************************************************************
 *
 * unique.cpp - Example program of unique algorithm.
 *              See Class Reference Section
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

  //
  // Initialize two vectors.
  //
  int a1[20] = {4, 5, 5, 9, -1, -1, -1, 3, 7, 5, 
                5, 5, 6, 7, 7, 7, 4, 2, 1, 1};
  vector<int,allocator<int> > v(a1+0, a1+20), result;
  //
  // Create an insert_iterator for results.
  //
  insert_iterator<vector<int,allocator<int> > > ins(result, result.begin());
  //
  // Demonstrate includes.
  //
  cout << "The vector: " << endl << "    ";
  copy(v.begin(),v.end(),ostream_iterator<int,char,char_traits<char> >(cout," "));
  //
  // Find the unique elements.
  //
  unique_copy(v.begin(), v.end(), ins);
  //
  // Display the results.
  //
  cout << endl << endl << "Has the following unique elements:"
       << endl << "     ";
  copy(result.begin(),result.end(), ostream_iterator<int,char,char_traits<char> >(cout," "));
  cout << endl;

  return 0;
}
