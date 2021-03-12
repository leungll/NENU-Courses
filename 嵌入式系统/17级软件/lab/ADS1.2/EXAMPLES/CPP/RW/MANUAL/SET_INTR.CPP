/**************************************************************************
 *
 * set_intr.cpp - Example program of set intersection algorithm.
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
  int a1[10] = {1,3,5,7,9,11};
  int a3[4]  = {3,5,7,8};
  set<int, less<int>,allocator<int>  > odd(a1+0, a1+6), result, smalll(a3+0, a3+4);
  //
  // Create an insert_iterator for result.
  //
  insert_iterator<set<int, less<int>,allocator<int>  > > res_ins(result, result.begin());
  //
  // Demonstrate set_intersection.
  //
  cout << "The result of:" << endl << "{";
  copy(smalll.begin(),smalll.end(), ostream_iterator<int,char,char_traits<char> >(cout," "));
  cout << "} intersection {";
  copy(odd.begin(),odd.end(), ostream_iterator<int,char,char_traits<char> >(cout," "));
  cout << "} =" << endl << "{";
  set_intersection(smalll.begin(),smalll.end(),odd.begin(),odd.end(),res_ins);
  copy(result.begin(),result.end(), ostream_iterator<int,char,char_traits<char> >(cout," "));
  cout << "}" << endl << endl;

  return 0;
}

