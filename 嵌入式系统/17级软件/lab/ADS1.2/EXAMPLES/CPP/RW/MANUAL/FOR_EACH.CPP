/**************************************************************************
 *
 * for_each.cpp - Example program for applying a function to each element 
 *                in a range. See Class Reference Section
 *
 * $Id: for_each.cpp,v 1.12 1996/08/28 01:16:49 smithey Exp $
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
#include <functional>

#ifdef _RW_STD_IOSTREAM
#include <iostream>
#else
#include <iostream.h>
#endif     

#ifndef _RWSTD_NO_NAMESPACE
  using namespace std;
#endif

//
// Function class that outputs its argument times x.
//
template <class Arg>
class out_times_x :  private unary_function<Arg,void>
{
private:
  Arg multiplier;
public:
  out_times_x(const Arg& x) : multiplier(x) { }
  void operator()(const Arg& x) { cout << x * multiplier << " " << endl; }
};

int main ()
{
  int sequence[5] = {1,2,3,4,5};  
  //
  // Set up a vector.
  //
  vector<int,allocator<int> > v(sequence+0, sequence+5);
  // 
  // Setup a function object.
  //
  out_times_x<int> f2(2);
  
  for_each(v.begin(),v.end(),f2);   // Apply function
  
  return 0;
}
