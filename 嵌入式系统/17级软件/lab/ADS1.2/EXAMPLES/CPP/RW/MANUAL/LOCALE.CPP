/**************************************************************************
 *
 * locale.cpp - Example program for the  locale class. 
 *               See Class Reference Section
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
#include <vector>

#include <iostream>
#include "codecvte.h"


int main ()
{
#ifndef _RWSTD_NO_NAMESPACE
  using namespace std;
#endif

  locale loc;  // Default locale

  // Construct new locale using default locale plus
  // user defined codecvt facet
  // This facet converts from ISO Latin 
  // Alphabet No. 1 (ISO 8859-1) to 
  // U.S. ASCII code page 437
  // This facet replaces the default for
  // codecvt<char,char,mbstate_t>
  locale my_loc(loc,new ex_codecvt);

  // imbue modified locale onto cout
  locale old = cout.imbue(my_loc);
  cout << "A \x93 jolly time was had by all" << endl;

  cout.imbue(old);
  cout << "A jolly time was had by all" << endl;

  // Create a vector of strings 
  vector<string,allocator<string> > v;
  v.insert(v.begin(),"antelope");
  v.insert(v.begin(),"bison");
  v.insert(v.begin(),"elk");

  copy(v.begin(),v.end(),
       ostream_iterator<string,char,char_traits<char> >(cout," "));
  cout << endl;

  // Sort the strings using the locale as a comparitor
  sort(v.begin(),v.end(),loc);

  copy(v.begin(),v.end(),
       ostream_iterator<string,char,char_traits<char> >(cout," "));

  cout << endl;
  return 0;
}

