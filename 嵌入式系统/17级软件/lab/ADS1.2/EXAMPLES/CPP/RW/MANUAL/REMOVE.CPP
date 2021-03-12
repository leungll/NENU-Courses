/**************************************************************************
 *
 * remove.cpp - Example program of remove algorithm.
 *              See Class Reference Section
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
#include <vector>
#include <iterator>
#include <functional>
 
#ifdef _RW_STD_IOSTREAM
#include <iostream>
#else
#include <iostream.h>
#endif     

#ifndef _RWSTD_NO_NAMESPACE
using namespace std;
#endif

template<class Arg>
struct not_zero : public unary_function<Arg, bool>
{
  bool operator() (const Arg& a) { return a != 0; }
};

int main ()
{
  int arr[10] = {1,2,3,4,5,6,7,8,9,10};
  vector<int,allocator<int> > v(arr+0, arr+10);

  copy(v.begin(),v.end(),ostream_iterator<int,char,char_traits<char> >(cout," "));
  cout << endl << endl;
  //
  // Remove the 7.
  //
  vector<int,allocator<int> >::iterator result = remove(v.begin(), v.end(), 7);
  //
  // Delete dangling elements from the vector.
  //
  v.erase(result, v.end());

  copy(v.begin(),v.end(),ostream_iterator<int,char,char_traits<char> >(cout," "));
  cout << endl << endl;
  //
  // Remove everything beyond the fourth element.
  //
  result = remove_if(v.begin()+4, v.begin()+8, not_zero<int>());
  //
  // Delete dangling elements.
  //
  v.erase(result, v.end());

  copy(v.begin(),v.end(),ostream_iterator<int,char,char_traits<char> >(cout," "));
  cout << endl << endl;
  //
  // Now remove all 3s on output.
  // 
  remove_copy(v.begin(), v.end(), ostream_iterator<int,char,char_traits<char> >(cout," "), 3);
  cout << endl << endl;
  //
  // Now remove everything satisfying predicate on output.
  // Should yield a NULL vector.
  //
  remove_copy_if(v.begin(), v.end(), ostream_iterator<int,char,char_traits<char> >(cout," "),
                 not_zero<int>());
 
  return 0;
}
