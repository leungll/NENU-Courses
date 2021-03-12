/**************************************************************************
 *
 * map.cpp - Example program of map. See Class Reference Section
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

#include <compnent.h>
#include <string>
#include <map>

#ifdef _RW_STD_IOSTREAM
#include <iostream>
#else
#include <iostream.h>
#endif     

#ifndef _RWSTD_NO_NAMESPACE
namespace std {
#endif        

  typedef map<string, int, less<string>,allocator<string> > months_type;

  //
  // Print out a pair.
  //
  template <class First, class Second>
  ostream& operator<< (ostream& out, const pair<First,Second> & p)
  {
    cout << p.first << " has " << p.second << " days";
    return out;
  }

  //
  // Print out a map.
  //
  ostream& operator<< (ostream& out, const months_type & l)
  {
    copy(l.begin(),l.end(), ostream_iterator
         <months_type::value_type,char,char_traits<char> >(cout,"\n"));
    return out;
  }

#ifndef _RWSTD_NO_NAMESPACE
} 
#endif        

int main ()
{
#ifndef _RWSTD_NO_NAMESPACE
  using namespace std;
#endif
  //
  // Create a map of months and the number of days in the month.
  //
  months_type months;

  typedef months_type::value_type value_type;
  // 
  // Put the months in the multimap.
  //
  months.insert(value_type(string("January"),   31));
  months.insert(value_type(string("Febuary"),   28));
  months.insert(value_type(string("Febuary"),   29));
  months.insert(value_type(string("March"),     31));
  months.insert(value_type(string("April"),     30));
  months.insert(value_type(string("May"),       31));
  months.insert(value_type(string("June"),      30));
  months.insert(value_type(string("July"),      31));
  months.insert(value_type(string("August"),    31));
  months.insert(value_type(string("September"), 30));
  months.insert(value_type(string("October"),   31));
  months.insert(value_type(string("November"),  30));
  months.insert(value_type(string("December"),  31));
  //
  // Print out the months.  Second Febuary is not present.
  //
  cout << months << endl;
  //
  // Find the Number of days in June.
  //
  months_type::iterator p = months.find(string("June"));
  //
  // Print out the number of days in June.
  //
  if (p != months.end())
    cout << endl << *p << endl;
  
  return 0;
}


