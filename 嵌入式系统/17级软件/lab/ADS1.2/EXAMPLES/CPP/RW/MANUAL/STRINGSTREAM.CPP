/***************************************************************************
 *
 * stringstream.cpp - stringstream example. See Class Reference Section
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

#include<iostream>
#include<sstream>


int main ( )
{
#ifndef _RWSTD_NO_NAMESPACE
  using namespace std;
#endif 

#ifndef _RWSTD_NO_WIDE_CHAR
  // create a bi-directional wstringstream object 
  wstringstream inout;

  // output characters
  inout << L"Das ist die rede von einem man" << endl;
  inout << L"C'est l'histoire d'un home" << endl;
  inout << L"This is the story of a man" << endl;

  wchar_t p[100];

  // extract the first line
  inout.getline(p,100);

  // output the first line to stdout
  wcout << endl << L"Deutch :" << endl;
  wcout << p;

  // extract the seconf line
  inout.getline(p,100);

  // output the second line to stdout
  wcout << endl << L"Francais :" << endl;
  wcout << p;

  // extract the third line
  inout.getline(p,100);

  // output the third line to stdout
  wcout << endl << L"English :" << endl;
  wcout << p;
 
  // output the all content of the
  //wstringstream object to stdout
  wcout << endl << endl << inout.str();
#else
 
 // create a bi-directional stringstream object 
  stringstream inout;

  // output characters
  inout << "Das ist die rede von einem man" << endl;
  inout << "C'est l'histoire d'un home" << endl;
  inout << "This is the story of a man" << endl;

  char p[100];

  // extract the first line
  inout.getline(p,100);

  // output the first line to stdout
  cout << endl << "Deutch :" << endl;
  cout << p;

  // extract the seconf line
  inout.getline(p,100);

  // output the second line to stdout
  cout << endl << "Francais :" << endl;
  cout << p;

  // extract the third line
  inout.getline(p,100);

  // output the third line to stdout
  cout << endl << "English :" << endl;
  cout << p;
 
  // output the all content of the
  //stringstream object to stdout
  cout << endl << endl << inout.str();
#endif

  return 0;
}

