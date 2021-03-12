/**************************************************************************
 *
 * ins_itr.cpp - Example program of insert iterator. 
 *               See Class Reference Section
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
#include <iterator>
#include <deque>

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
  // Initialize a deque using an array.
  //
  int arr[4] = { 3,4,7,8 };
  deque<int,allocator<int> > d(arr+0, arr+4);
  //
  // Output the original deque.
  //
  cout << "Start with a deque: " << endl << "     ";
  copy(d.begin(), d.end(), ostream_iterator<int,char,char_traits<char> >(cout," "));
  //
  // Insert into the middle.
  //
  insert_iterator<deque<int,allocator<int> > > ins(d, d.begin()+2);
  *ins = 5; *ins = 6;
  //
  // Output the new deque.
  //
  cout << endl << endl;
  cout << "Use an insert_iterator: " << endl << "     ";
  copy(d.begin(), d.end(), 
       ostream_iterator<int,char,char_traits<char> >(cout," "));
  //
  // A deque of four 1s.
  //
  deque<int,allocator<int> > d2((size_t)4, 1);
  //
  // Insert d2 at front of d.
  //
  copy(d2.begin(), d2.end(), front_inserter(d));
  //
  // Output the new deque.
  //
  cout << endl << endl;
  cout << "Use a front_inserter: " << endl << "     ";
  copy(d.begin(), d.end(), 
       ostream_iterator<int,char,char_traits<char> >(cout," "));
  //
  // Insert d2 at back of d.
  //
  copy(d2.begin(), d2.end(), back_inserter(d));
  //
  // Output the new deque.
  //
  cout << endl << endl;
  cout << "Use a back_inserter: " << endl << "     ";
  copy(d.begin(), d.end(), 
       ostream_iterator<int,char,char_traits<char> >(cout," "));
  cout << endl;
   
  return 0;
}
