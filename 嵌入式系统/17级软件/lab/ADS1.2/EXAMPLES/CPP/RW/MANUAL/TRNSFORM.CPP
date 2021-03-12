/**************************************************************************
 *
 * trnsform.cpp - Example program of transform algorithm. 
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

#include <functional>
#include <deque>
#include <algorithm>
 
#ifdef _RW_STD_IOSTREAM
#include <iostream>
#include <iomanip>
#else
#include <iostream.h>
#include <iomanip.h>
#endif     

int main ()
{
#ifndef _RWSTD_NO_NAMESPACE
  using namespace std;
#endif

  //
  // Initialize a deque with an array of integers.
  //
  int arr1[5] = {99, 264, 126, 330, 132};
  int arr2[5] = {280, 105, 220, 84, 210};
  deque<int,allocator<int> > d1(arr1+0, arr1+5), d2(arr2+0, arr2+5);
  //
  // Print the original values.
  //
  cout << "The following pairs of numbers: " << endl << "     ";
  deque<int,allocator<int> >::iterator i1;
  for (i1 = d1.begin(); i1 != d1.end(); i1++)
    cout << setw(6) << *i1 << " ";
  cout << endl << "     ";
  for (i1 = d2.begin(); i1 != d2.end(); i1++)
    cout << setw(6) << *i1 << " ";
  //
  // Transform the numbers in the deque to their 
  // factorials and store in the vector.
  //
  transform(d1.begin(), d1.end(), d2.begin(), d1.begin(), multiplies<int>());
  //
  // Display the results.
  //
  cout << endl << endl;
  cout << "Have the products: " << endl << "     ";
  for (i1 = d1.begin(); i1 != d1.end(); i1++)
    cout << setw(6) << *i1 << " ";
  cout << endl;

  return 0;
}
