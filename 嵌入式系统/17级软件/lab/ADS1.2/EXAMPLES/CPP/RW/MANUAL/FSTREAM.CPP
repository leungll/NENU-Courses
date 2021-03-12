/***************************************************************************
 *
 * fstream.cpp - fstream example
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
 
 
//
// stdlib/examples/manual/fstream.cpp
//
#include<iostream>
#include<fstream>

int main ( )
{
#ifndef _RWSTD_NO_NAMESPACE
  using namespace std;
#endif 

  // create a bi-directional fstream object 
  fstream inout("test_fstream.out",ios_base::in | ios_base::out | ios_base::trunc);

  // output characters
  inout << "Das ist die rede von einem man" << endl;
  inout << "C'est l'histoire d'un home" << endl;
  inout << "This is the story of a man" << endl;

  char p[100];

  // seek back to the beginning of the file
  inout.seekg(0);

  // extract the first line
  inout.getline(p,100);

  // output the first line to stdout
  cout << endl << "Deutch :" << endl;
  cout << p;

  fstream::pos_type pos = inout.tellg();

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
 
  // move the put sequence before
  // the second line
  inout.seekp(pos);

  // replace the second line
  inout << "This is the story of a man" << endl;  

  // replace the third line
  inout << "C'est l'histoire d'un home";

  // seek to the beginning of the file
  inout.seekg(0);

  // output the all content of the
  // fstream object to stdout
  cout << endl << endl << inout.rdbuf();
  cout << endl;

  return 0;
}




