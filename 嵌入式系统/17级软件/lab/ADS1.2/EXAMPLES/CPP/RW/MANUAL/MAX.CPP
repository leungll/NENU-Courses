/**************************************************************************
 *
 * max.cpp - Example program for finding maximum of a pair of values.
 *           See Class Reference Section
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
#include <functional>

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

  double  d1 = 10.0, d2 = 20.0;  
  // 
  // Find minimum.
  //
  double val1 = min(d1, d2);                  
  // 
  // The greater comparator returns the greater of the two values.     
  //
  double val2 = min(d1, d2, greater<double>());
  // 
  // Find minimum.
  //
  double val3 = max(d1, d2);                  
  // 
  // The less comparator returns the smaller of the  two values.
  // Note that, like every comparison in the STL, max is 
  // defined in terms of the < operator, so using less here
  // is the same as using the max algorithm with a default
  // comparator.
  //
  double val4 = max(d1, d2, less<double>());
  
  cout << val1 << " " << val2 << " " << val3 << " " << val4 << endl;
  
  return 0;
}
