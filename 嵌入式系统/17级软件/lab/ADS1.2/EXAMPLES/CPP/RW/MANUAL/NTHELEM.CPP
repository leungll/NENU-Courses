/**************************************************************************
 *
 * nthelem.cpp - Example program for rearranging a collection based on nth
 *               element. See Class Reference Section
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
 
#include<algorithm>
#include<vector>
 
#ifdef _RW_STD_IOSTREAM
#include <iostream>
#else
#include <iostream.h>
#endif     


template<class RandomAccessIterator>
void quik_sort(RandomAccessIterator start, RandomAccessIterator end)
{
#ifndef _RWSTD_NO_NAMESPACE
  using std::distance;
  using std::nth_element;
  using std::swap;
#endif

  size_t dist = 0;
  distance(start, end, dist);
  //
  // Stop condition for recursion.
  //
  if(dist > 2)
  {
    //
    // Use nth_element to do all the work for quik_sort.
    //
    nth_element(start, start+(dist/2), end);
    //
    // Recursive calls to each remaining unsorted portion.
    //
    quik_sort(start, start+(dist/2-1));
    quik_sort(start+(dist/2+1), end);
  }

  if(dist == 2 && *end < *start)
    swap(start, end);
}

int main ()
{
#ifndef _RWSTD_NO_NAMESPACE
  using namespace std;
#endif

  //
  // Initialize a vector using an array of integers.
  //
  int arr[10] = {37, 12, 2, -5, 14, 1, 0, -1, 14, 32};
  vector<int,allocator<int> > v(arr+0, arr+10);
  //
  // Print the initial vector.
  //
  cout << "The unsorted values are: " << endl << "     ";
  vector<int,allocator<int> >::iterator i; 
  for(i = v.begin(); i != v.end(); i++)
    cout << *i << ", ";
  cout << endl << endl;
  //
  // Use the new sort algorithm.
  //
  quik_sort(v.begin(), v.end());
  //
  // Output the sorted vector.
  //
  cout << "The sorted values are: " << endl << "     ";
  for(i = v.begin(); i != v.end(); i++)
    cout << *i << ", ";
  cout << endl << endl;

  return 0;
}
