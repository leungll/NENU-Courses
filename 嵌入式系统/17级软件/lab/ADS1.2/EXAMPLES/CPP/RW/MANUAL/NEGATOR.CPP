/**************************************************************************
 *
 * negator.cpp - Example program for reversing the sense of predicate 
 *               function objects by using function adaptors and function
 *               objects. See Class Reference Section
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
#include<functional>
#include<algorithm>

#ifdef _RW_STD_IOSTREAM
#include <iostream>
#else
#include <iostream.h>
#endif     

#ifndef _RWSTD_NO_NAMESPACE
using namespace std;
#endif

#ifndef _RWSTD_NO_NAMESPACE
using std::unary_function;
#endif
//
// Create a new predicate from unary_function.
//
template<class Arg>
class is_odd : public unary_function<Arg, bool>
{
public:
  bool operator() (const Arg& arg1) const
  {
    return (arg1 % 2 ? true : false);
  }
};

int main ()
{
#ifndef _RWSTD_NO_NAMESPACE
using namespace std;
#endif

  less<int> less_func;
  //
  // Use not2 on less.
  //
  cout << (less_func(1,4) ? "TRUE" : "FALSE") << endl;
  cout << (less_func(4,1) ? "TRUE" : "FALSE") << endl;
  cout << (not2(less<int>())(1,4) ? "TRUE" : "FALSE") << endl;
  cout << (not2(less<int>())(4,1) ? "TRUE" : "FALSE") << endl;   
  //
  // Create an instance of our predicate.
  //
  is_odd<int> odd;
  //
  // Use not1 on our user defined predicate.
  //
  cout << (odd(1) ? "TRUE" : "FALSE") << endl;
  cout << (odd(4) ? "TRUE" : "FALSE") << endl;
  cout << (not1(odd)(1) ? "TRUE" : "FALSE") << endl;
  cout << (not1(odd)(4) ? "TRUE" : "FALSE") << endl;

  return 0;
}
