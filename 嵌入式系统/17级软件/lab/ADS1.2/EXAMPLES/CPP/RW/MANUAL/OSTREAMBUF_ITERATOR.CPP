/***************************************************************************
 *
 * ostreambuf_iterator.cpp - ostreambuf_iterator example
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

  // create a filebuf object
  filebuf buf;

  // open the file iter_out and link it to the filebuf object
  buf.open("iter_out", ios_base::in | ios_base::out | ios_base::trunc );

  // create an ostreambuf_iterator and link it to 
  // the filebuf object
  ostreambuf_iterator<char,char_traits<char> > out_iter(&buf);

  // output into the file using the ostreambuf_iterator
  for(char i=64; i<127; i++ )
   out_iter = i;

  // seek to the beginning of the file
  buf.pubseekpos(0);
  
  // create an istreambuf_iterator and link it to 
  // the filebuf object
  istreambuf_iterator<char,char_traits<char> > in_iter(&buf);

  // construct an end of stream iterator
  istreambuf_iterator<char,char_traits<char> > end_of_stream_iterator;

  cout << endl;

  // output the content of the file
  while( !in_iter.equal(end_of_stream_iterator) )

  // use both operator++ and operator*
  cout << *in_iter++;

  cout << endl;

  return 0;
}

 


