/**************************************************************************
 *
 * setex.cpp - Example program of sets. See Class Reference Section
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

#include <set>
 
#ifdef _RW_STD_IOSTREAM
#include <iostream>
#else
#include <iostream.h>
#endif     

#ifndef _RWSTD_NO_NAMESPACE
using namespace std;
#endif

typedef set<double,less<double>,allocator<double>  > set_type;

ostream& operator<<(ostream& out, const set_type& s)
{
  copy(s.begin(), s.end(), ostream_iterator<set_type::value_type,char,char_traits<char> >(cout," "));
  return out;
}

int main ()
{
  //
  // Create a set of double's, and one of integers.
  //
  set_type   sd;
  int         i;

  for (i = 0; i < 10; ++i)
    //
    // Insert values.
    //
    sd.insert(i);
  //
  // Print out the set.
  //
  cout << sd << endl << endl;
  //
  // Now let's erase half of the elements in the set.
  //
  int half = sd.size() / 2;
  set_type::iterator sdi = sd.begin();
  advance(sdi,half);
  sd.erase(sd.begin(),sdi);
  //
  // Print it out again.
  //
  cout << sd << endl << endl;
  //
  // Make another set and an empty result set.
  //
  set_type sd2, sdResult;
  for (i = 1; i < 9; i++)
    sd2.insert(i+5);
  cout << sd2 << endl;
  //
  // Try a couple of set algorithms.
  //
  set_union(sd.begin(),sd.end(),sd2.begin(),sd2.end(),
            inserter(sdResult,sdResult.begin()));
  cout << "Union:" << endl << sdResult << endl;

  sdResult.erase(sdResult.begin(),sdResult.end());
  set_intersection(sd.begin(),sd.end(), sd2.begin(),sd2.end(),
                   inserter(sdResult,sdResult.begin()));
  cout << "Intersection:" << endl << sdResult << endl;
  
  return 0;
}
