/**************************************************************************
 *
 * collate.cpp - Example program of collate facet. 
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


#include <iostream>
#include <locale> 

int main ()
{
#ifndef _RWSTD_NO_NAMESPACE
  using namespace std;
#endif

  locale loc;
  string s1("blue");
  string s2("blues");

  // Get a reference to the collate<char> facet
  const collate<char>& co =
#ifndef _RWSTD_NO_TEMPLATE_ON_RETURN_TYPE
      use_facet<collate<char> >(loc);
#else
      use_facet(loc,(collate<char>*)0);
#endif

  // Compare two strings
  cout << co.compare(s1.begin(),s1.end(),
                     s2.begin(),s2.end()-1) << endl;
  cout << co.compare(s1.begin(),s1.end(),
                     s2.begin(),s2.end()) << endl;

  // Retrieve hash values for two strings
  cout << co.hash(s1.begin(),s1.end()) << endl;
  cout << co.hash(s2.begin(),s2.end()) << endl;

  return 0;
}
