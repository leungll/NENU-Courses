/***************************************************************************
 *
 * istringstream.cpp - basic_istringstream example
 *                     See Class Reference Section
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
#include<iomanip>

int main ( )
{
#ifndef _RWSTD_NO_NAMESPACE
  using namespace std;
#endif 

  long   l= 20;

#ifndef _RWSTD_NO_WIDE_CHAR
  wchar_t *ntbs=L"Il avait l'air heureux";
  wchar_t c;
  wchar_t buf[50];

  // create a read/write string-stream object on wide char
  // and attach it to an wistringstream object
  wistringstream in(ios_base::in | ios_base::out);

  // tie the ostream object to the wistringstream object
  wostream out(in.rdbuf());   

  // output ntbs in out
  out << ntbs;

  // output each word on a separate line
  while ( in.get(c) )
   {
     if ( wistringstream::traits_type::eq(c,L' ') ) 
      wcout << endl;
     else
      wcout << c;
   }
  wcout << endl << endl;

  // clear the state flags, fail bit set by last in.get(c)
  in.clear();

  // move back the input sequence to the beginning
  in.seekg(0); 

  // does the same thing as the previous code
  // output each word on a separate line
  while ( in >> buf )
   wcout << buf << endl; 
    
  wcout << endl << endl;
#endif

  // create a tiny string object
  string test_string("Il dormait pour l'eternite");

  // create a read/write string-stream object on char
  // and attach it to an istringstream object
  istringstream in_bis(ios_base:: in | ios_base::out |
                       ios_base::app );

  // create an ostream object
  ostream out_bis(in_bis.rdbuf());  

  // initialize the string-buffer with test_string
  in_bis.str(test_string);

  out_bis << endl;

  // output the base info before each integer
  out_bis << showbase;

  ostream::pos_type pos= out_bis.tellp();

  // output l in hex with a field with of 20 
  out_bis << hex << setw(20) << l << endl;

  // output l in oct with a field with of 20
  out_bis << oct << setw(20) << l << endl;

  // output l in dec with a field with of 20
  out_bis << dec << setw(20) << l << endl;

  // output the all buffer
  cout << in_bis.rdbuf();

  // seek the input sequence to pos  
  in_bis.seekg(pos);

  int a,b,d;

  in_bis.unsetf(ios_base::basefield);

  // read the previous outputted integer
  in_bis >> a >> b >> d;

  // output 3 times 20
  cout << a << endl << b << endl << d << endl;

  return 0;
 }



