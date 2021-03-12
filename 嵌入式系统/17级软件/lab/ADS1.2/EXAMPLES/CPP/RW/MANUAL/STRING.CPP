/**************************************************************************
 *
 * string.cpp - Example program of string. See Class Reference Section
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

  string test;
  //
  // Type in a string over five characters long.
  //
  while (test.empty() ||  test.size() < 5)
  {
    cout << "Type a string between 5 and 100 characters long. " << endl;
    cin >> test;
  }
  //
  // Try operator[] access.
  //
  cout << "Changing the third character from " << test[2] << " to * " << endl;
  test[2] = '*';
  cout << "now its: " << test << endl << endl;
  //
  // Try the insertion member function.
  //
  test.insert(test.size() / 2, "(the middle is here!)");
  cout << "Identifying the middle: " << test << endl << endl;
  //
  // Try replacement.
  //
  test.replace(test.find("middle",0), 6, "center");
  cout << "I didn't like the word 'middle', so instead, I'll say: "
       << endl << test << endl; 

  return 0;
}
