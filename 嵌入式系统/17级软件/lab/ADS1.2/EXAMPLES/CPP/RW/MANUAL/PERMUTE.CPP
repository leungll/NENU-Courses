/**************************************************************************
 *
 * permute.cpp - Example program of permutations. See Class Reference Section
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

#include <numeric>    // For accumulate.
#include <vector>     // For vector.
#include <functional> // For less.

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
  // Initialize a vector using an array of integers.
  //
  int  a1[] = {0,0,0,0,1,0,0,0,0,0};
  char a2[] = "abcdefghji";
  //
  // Create the initial set and copies for permuting.
  //
  vector<int,allocator<int> >  m1(a1+0, a1+10); 
  vector<int,allocator<int> >  prev_m1((size_t)10), next_m1((size_t)10);
  vector<char,allocator<char> > m2(a2+0, a2+10);
  vector<char,allocator<char> > prev_m2((size_t)10), next_m2((size_t)10);

  copy(m1.begin(), m1.end(), prev_m1.begin());
  copy(m1.begin(), m1.end(), next_m1.begin());
  copy(m2.begin(), m2.end(), prev_m2.begin());
  copy(m2.begin(), m2.end(), next_m2.begin());
  //
  // Create permutations.
  //
  prev_permutation(prev_m1.begin(), prev_m1.end(), less<int>());
  next_permutation(next_m1.begin(), next_m1.end(), less<int>());
  prev_permutation(prev_m2.begin(), prev_m2.end(), less<int>());
  next_permutation(next_m2.begin(), next_m2.end(), less<int>());
  //
  // Output results.
  //
  cout << "Example 1: " << endl << "     ";
  cout << "Original values:      ";
  copy(m1.begin(), m1.end(), ostream_iterator<int,char,char_traits<char> >(cout," "));
  cout << endl << "     ";
  cout << "Previous permutation: ";
  copy(prev_m1.begin(), prev_m1.end(), ostream_iterator<int,char,char_traits<char> >(cout," "));

  cout << endl<< "     ";
  cout << "Next Permutation:     ";
  copy(next_m1.begin(), next_m1.end(), ostream_iterator<int,char,char_traits<char> >(cout," "));
  cout << endl << endl;

  cout << "Example 2: " << endl << "     ";
  cout << "Original values: ";
  copy(m2.begin(), m2.end(), ostream_iterator<char,char,char_traits<char> >(cout," "));     
  cout << endl << "     ";
  cout << "Previous Permutation: ";
  copy(prev_m2.begin(), prev_m2.end(), ostream_iterator<char,char,char_traits<char> >(cout," "));
  cout << endl << "     ";

  cout << "Next Permutation:     ";
  copy(next_m2.begin(), next_m2.end(), ostream_iterator<char,char,char_traits<char> >(cout," "));  
  cout << endl << endl;

  return 0;
}
