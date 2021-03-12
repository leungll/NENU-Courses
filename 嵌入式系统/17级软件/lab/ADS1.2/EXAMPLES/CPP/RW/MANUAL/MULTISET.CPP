/**************************************************************************
 *
 * multiset.cpp - Example program for multiset class.
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
#include <set>

#ifdef _RW_STD_IOSTREAM
#include <iostream>
#else
#include <iostream.h>
#endif     

#ifndef _RWSTD_NO_NAMESPACE
using namespace std;
#endif

typedef multiset<int,less<int>,allocator<int>  > set_type;

ostream& operator<< (ostream& out, const set_type& s)
{
  copy(s.begin(),s.end(),ostream_iterator<set_type::value_type,char,char_traits<char> >(cout," "));
  return out;
}

int main ()
{
  //
  // Create a multiset of integers.
  //
  set_type  si;
  int       i;
  
  for (int j = 0; j < 2; j++)
  {
    for (i = 0; i < 10; ++i)
      //
      // Insert values with a hint.
      //
      si.insert(si.begin(), i);
  }
  //
  // Print out the multiset.
  //
  cout << si << endl;
  //
  // Make another int multiset and an empty multiset.
  //
  set_type si2, siResult;
  for (i = 0; i < 10; i++)
    si2.insert(i+5);
  cout << si2 << endl;
  //
  // Try a couple of set algorithms.
  //
  set_union(si.begin(),si.end(),si2.begin(),si2.end(),
            inserter(siResult,siResult.begin()));
  cout << "Union:" << endl << siResult << endl;
  
  siResult.erase(siResult.begin(),siResult.end());
  set_intersection(si.begin(),si.end(),si2.begin(),si2.end(),
                   inserter(siResult,siResult.begin()));
  cout << "Intersection:" << endl << siResult << endl;
  
  return 0;
}
