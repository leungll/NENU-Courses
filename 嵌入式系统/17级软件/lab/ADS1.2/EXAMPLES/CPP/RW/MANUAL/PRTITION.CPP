/**************************************************************************
 *
 * prtition.cpp - Example program for partition. See Class Reference Section
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
// Create a new predicate from unary_function.
//
template<class Arg>
class is_even : public unary_function<Arg, bool>
{
public:
  bool operator()(const Arg& arg1) { return (arg1 % 2) == 0; } 
};

int main ()
{
  //
  // Initialize a deque with an array of integers.
  //
  int init[10] = { 1,2,3,4,5,6,7,8,9,10 };
  deque<int,allocator<int> > d1(init+0, init+10);
  deque<int,allocator<int> > d2(init+0, init+10);
  //
  // Print out the original values.
  //
  cout << "Unpartitioned values: " << "\t\t";
  copy(d1.begin(), d1.end(), ostream_iterator<int,char,char_traits<char> >(cout," "));
  cout << endl;
  //
  // A partition of the deque according to even/oddness.
  //
  partition(d2.begin(), d2.end(), is_even<int>());
  //
  // Output result of partition.
  //
  cout << "Partitioned values: " << "\t\t";
  copy(d2.begin(), d2.end(), ostream_iterator<int,char,char_traits<char> >(cout," "));
  cout << endl;
  //
  // A stable partition of the deque according to even/oddness.
  //
  stable_partition(d1.begin(), d1.end(), is_even<int>());
  //
  // Output result of partition.
  //
  cout << "Stable partitioned values: " << "\t";
  copy(d1.begin(), d1.end(), ostream_iterator<int,char,char_traits<char> >(cout," "));
  cout << endl;

  return 0;
}
