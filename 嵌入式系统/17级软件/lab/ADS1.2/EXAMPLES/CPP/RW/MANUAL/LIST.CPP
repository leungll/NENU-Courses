/**************************************************************************
 *
 * list.cpp - Example program of list class. See Class Reference Section
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
#include <list>
#include <string>

#ifdef _RW_STD_IOSTREAM
#include <iostream>
#else
#include <iostream.h>
#endif     

#ifndef _RWSTD_NO_NAMESPACE
  using namespace std;
#endif

//
// Print out a list of strings.
//
ostream& operator<< (ostream& out, const list<string,allocator<string> >& l)
{
  copy(l.begin(), l.end(), 
       ostream_iterator<string,char,char_traits<char> >(out," "));
  return out;
}

int main ()
{
  //
  // Create a list of critters.
  //
  list<string,allocator<string> > critters;
  int i;
  //
  // Insert several critters.
  //
  critters.insert(critters.begin(),"antelope");
  critters.insert(critters.begin(),"bear");
  critters.insert(critters.begin(),"cat");
  //
  // Print out the list.
  //
  cout << critters << endl;
  // 
  // Change cat to cougar.
  //
  *find(critters.begin(),critters.end(),"cat") = "cougar";
  cout << critters << endl;
  //
  // Put a zebra at the beginning, an ocelot ahead of antelope,
  // and a rat at the end.
  //
  critters.push_front("zebra");
  critters.insert(find(critters.begin(),critters.end(),"antelope"),"ocelot");
  critters.push_back("rat");
  cout << critters << endl;
  //
  // Sort the list (Use list's sort function since the 
  // generic algorithm requires a random access iterator 
  // and list only provides bidirectional)
  //
  critters.sort();
  cout << critters << endl;
  //
  // Now let's erase half of the critters.
  //
  int half = critters.size() / 2;
  for (i = 0; i < half; ++i)
    critters.erase(critters.begin());
  cout << critters << endl;
  
  return 0;
}




