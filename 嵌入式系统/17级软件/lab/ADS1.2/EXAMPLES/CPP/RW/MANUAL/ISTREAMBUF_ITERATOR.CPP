/***************************************************************************
 *
 * istreambuf_iterator.cpp - istreambuf_iterator example
 *                           See Class Reference Section
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
#include<fstream>

int main ( )
{
#ifndef _RWSTD_NO_NAMESPACE
  using namespace std;
#endif 

  // open the file is_iter.out for reading and writing
  ofstream out("is_iter.out", ios_base::out | ios_base::in | ios_base::trunc);

  // output the example sentence into the file
  out << "Ceci est un simple example pour demontrer le" << endl;
  out << "fonctionement de istreambuf_iterator";

  // seek to the beginning of the file
  out.seekp(0);

  // construct an istreambuf_iterator pointing to
  // the ofstream object underlying streambuffer
  istreambuf_iterator<char,char_traits<char> > iter(out.rdbuf());

  // construct an end of stream iterator
  istreambuf_iterator<char,char_traits<char> > end_of_stream_iterator;

  cout << endl;

  // output the content of the file
  while( !iter.equal(end_of_stream_iterator) )

  // use both operator++ and operator*
  cout << *iter++;

  cout << endl; 

  return 0;
}

 


