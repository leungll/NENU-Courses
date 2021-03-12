/***************************************************************************
 *
 * stringbuf.cpp - basic_stringbuf example.  See Class Reference Section.
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
#include<string>

int main ( )
{
#ifndef _RWSTD_NO_NAMESPACE
  using namespace std;
#endif 

  // create a read/write string-stream object on tiny char
  // and attach it to an ostringstream object
  ostringstream out_1(ios_base::in | ios_base::out);

  // tie the istream object to the ostringstream object
  istream in_1(out_1.rdbuf());   

  // output to out_1
  out_1 << "Here is the first ouput";

  // create a string object on tiny char 
  string  string_ex("l'heure est grave !");

  // open a read only string-stream object on tiny char
  // and initialize it
  istringstream in_2(string_ex);

  // output in_1 to the standard output
  cout << in_1.rdbuf() << endl;

  // reposition in_1 at the beginning
  in_1.seekg(0);

  // output in_2 to the standard output
  cout << in_2.rdbuf() << endl;

  // reposition in_2 at the beginning
  in_2.seekg(0);

  stringbuf::pos_type pos;

  // get the current put position
  // equivalent to
  // out_1.tellp(); 
  pos = out_1.rdbuf()->pubseekoff(0,ios_base::cur,
                                  ios_base::out);

  // append the content of stringbuffer
  // pointed at by in_2 to the one 
  // pointed at by out_1
  out_1 << ' ' << in_2.rdbuf();

  // output in_1 to the standard output
  cout << in_1.rdbuf() << endl;

  // position the get sequence
  // equivalent to
  // in_1.seekg(pos);
  in_1.rdbuf()->pubseekpos(pos, ios_base::in);

  // output "l'heure est grave !"
  cout << in_1.rdbuf() << endl << endl;  

  return 0;
}
 




