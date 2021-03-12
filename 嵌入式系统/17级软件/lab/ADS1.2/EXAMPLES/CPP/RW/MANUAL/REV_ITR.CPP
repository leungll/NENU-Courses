/**************************************************************************
 *
 * rev_itr.cpp - Example program of reverse iterator.
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
  // Initialize a vector using an array.
  //
  int arr[4] = {3,4,7,8};
  vector<int,allocator<int> > v(arr+0, arr+4);
  //
  // Output the original vector.
  //
  cout << "Traversing vector with iterator: " << endl << "     ";
  for(vector<int,allocator<int> >::iterator i = v.begin(); i != v.end(); i++)
    cout << *i << " ";
  //
  // Declare the reverse_iterator.
  //
  vector<int,allocator<int> >::reverse_iterator rev(v.end());
  vector<int,allocator<int> >::reverse_iterator rev_end(v.begin());
  //
  // Output the vector backwards.
  //
  cout << endl << endl;
  cout << "Same vector, same loop, reverse_itertor: " << endl << "     ";
  for(; rev != rev_end; rev++)
    cout << *rev << " ";
  cout << endl;
  return 0;
}
