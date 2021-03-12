/**************************************************************************
 *
 * swap.cpp - Example program of swap algorithm. See Class Reference Section
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

  int d1[] = {6, 7, 8, 9, 10, 1, 2, 3, 4, 5};
  //
  // Set up a vector.
  //
  vector<int,allocator<int> > v(d1+0, d1+10);
  //
  // Output original vector.
  //
  cout << "For the vector: ";
  copy(v.begin(), v.end(), ostream_iterator<int,char,char_traits<char> >(cout," "));
  //
  // Swap the first five elements with the last five elements.
  //
  swap_ranges(v.begin(), v.begin()+5, v.begin()+5);
  //
  // Output result.
  //
  cout << endl << endl
       << "Swaping the first five elements with the last five gives: "
       << endl << "     ";
  copy(v.begin(), v.end(), ostream_iterator<int,char,char_traits<char> >(cout," "));
  //
  // Now an example of iter_swap -- swap first and last elements.
  //
  iter_swap(v.begin(), v.end()-1);
  //
  // Output result.
  //
  cout << endl << endl
       << "Swaping the first and last elements gives: "
       << endl << "     ";
  copy(v.begin(), v.end(), ostream_iterator<int,char,char_traits<char> >(cout," "));
  cout << endl;

  return 0;
}
