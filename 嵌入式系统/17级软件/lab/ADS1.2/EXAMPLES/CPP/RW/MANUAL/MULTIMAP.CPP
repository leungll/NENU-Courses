/**************************************************************************
 *
 * multimap.cpp - Example program for multimap class.
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
  typedef multimap<int, string, less<int>,allocator<int>  > months_type;

  //
  // Print out a pair.
  //
  template <class First, class Second>
  ostream& operator<< (ostream& out, const pair<First,Second>& p)
  {
    out << p.second << " has " << p.first << " days";
    return out;
  }

  //
  // Print out a multimap.
  //
  ostream& operator<< (ostream& out, months_type l)
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
  // Create a multimap of months and the number of days in the month.
  //
  months_type months;

  typedef months_type::value_type value_type;
  // 
  // Put the months in the multimap.
  //
  months.insert(value_type(31, string("January")));
  months.insert(value_type(28, string("Febuary")));
  months.insert(value_type(31, string("March")));
  months.insert(value_type(30, string("April")));
  months.insert(value_type(31, string("May")));
  months.insert(value_type(30, string("June")));
  months.insert(value_type(31, string("July")));
  months.insert(value_type(31, string("August")));
  months.insert(value_type(30, string("September")));
  months.insert(value_type(31, string("October")));
  months.insert(value_type(30, string("November")));
  months.insert(value_type(31, string("December")));
  //
  // Print out the months.
  //
  cout << "All months of the year" << endl << months << endl;
  //
  // Find the Months with 30 days.
  //
  pair<months_type::iterator,months_type::iterator> p = 
  months.equal_range(30);
  //
  // Print out the 30 day months.
  //
  cout << endl << "Months with 30 days" << endl;
  copy(p.first,p.second,ostream_iterator<months_type::value_type,char,char_traits<char> >(cout,"\n"));
  
  return 0;
}


