/**************************************************************************
 *
 * vector.cpp - Example program of vector. See Class Reference Section
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
 
#ifdef _RW_STD_IOSTREAM
#include <iostream>
#else
#include <iostream.h>
#endif     

#ifndef _RWSTD_NO_NAMESPACE
using namespace std;
#endif

ostream& operator<< (ostream& out, const vector<int,allocator<int> >& v)
{
  copy(v.begin(), v.end(), ostream_iterator<int,char,char_traits<char> >(out, " "));
  return out;
}

int main ()
{
  //
  // Create a vector of doubles, and one of integers.
  //
  vector<int,allocator<int> >         vi;
  int                 i;

  for (i = 0; i < 10; ++i)
    //
    // Insert values before the beginning.
    //
    vi.insert(vi.begin(), i);
  //
  // Print out the vector.
  //
  cout << vi << endl;
  //
  // Now let's erase half of the elements.
  //
  int half = vi.size() / 2;

  for (i = 0; i < half; ++i)
    vi.erase(vi.begin());
  //
  // Print it out again.
  //
  cout << vi << endl;
  
  return 0;
}
