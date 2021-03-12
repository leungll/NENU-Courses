/**************************************************************************
 *
 * set_diff.cpp - Example program of set differences algorithm. 
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
#include <set>
 
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
  // Initialize some sets.
  //
  int a1[10] = {1,2,3,4,5,6,7,8,9,10};
  int a2[6]  = {2,4,6,8,10,12};

  set<int, less<int>,allocator<int>  > all(a1+0, a1+10), even(a2+0, a2+6), odd;
  //
  // Create an insert_iterator for odd.
  //
  insert_iterator<set <int, less<int>,allocator<int>  >  > odd_ins(odd, odd.begin());
  //
  // Demonstrate set_difference.
  //
  cout << "The result of:" << endl << "{";
  copy(all.begin(),all.end(), ostream_iterator<int,char,char_traits<char> >(cout," "));
  cout << "} - {";
  copy(even.begin(),even.end(), ostream_iterator<int,char,char_traits<char> >(cout," "));
  cout << "} =" << endl << "{";
  set_difference(all.begin(), all.end(), even.begin(), even.end(), odd_ins);
  copy(odd.begin(),odd.end(), ostream_iterator<int,char,char_traits<char> >(cout," "));
  cout << "}" << endl << endl;

  return 0;
}

