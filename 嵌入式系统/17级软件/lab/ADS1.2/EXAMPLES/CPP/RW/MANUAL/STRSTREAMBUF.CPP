/***************************************************************************
 *
 * strstreambuf.cpp - strstreambuf example.  See Class Reference Section.
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
#include<strstream>
#include<iomanip>

int main ( )
{
#ifndef _RWSTD_NO_NAMESPACE
  using namespace std;
#endif 

  // create a read/write strstreambuf object
  // and attach it to an ostrstream object
  ostrstream out;

  // tie the istream object to the ostrstream object
  istream in(out.rdbuf());   

  // output to out_1
  out << "anticonstitutionellement is a big word !!!";

  // create a NTBS 
  char *p ="Le rat des villes et le rat des champs";

  // output the NTBS
  out << p << endl;   

  // resize the buffer
  if ( out.rdbuf()->pubsetbuf(0,5000) )
   cout << endl << "Success in allocating the buffer" << endl;

  // output the all buffer to stdout
  cout << in.rdbuf( );

  // output the decimal conversion of 100 in hex
  // with right padding and a width field of 200
  out << dec << setfill('!') << setw(200) << 0x100 << endl;  
  
  // output the content of the input sequence to stdout
  cout << in.rdbuf( ) << endl;

  // number of elements in the output sequence
  cout << out.rdbuf()->pcount() << endl;

  // resize the buffer to a minimum size
  if ( out.rdbuf()->pubsetbuf(0,out.rdbuf()->pcount()+1) )
   cout << endl << "Success in resizing the buffer" << endl;

  // output the content of the all array object
  cout << out.rdbuf()->str() << endl;

  return 0;
 }



