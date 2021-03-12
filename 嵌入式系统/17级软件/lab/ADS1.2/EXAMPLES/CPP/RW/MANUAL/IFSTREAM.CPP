/***************************************************************************
 *
 * ifstream.cpp - basic_ifstream example
 *                See Class Reference Section
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
// stdlib/examples/manual/ifstream.cpp
//
#include<iostream>
#include<fstream>
#include<iomanip>

int main ( )
{
#ifndef _RWSTD_NO_NAMESPACE
  using namespace std;
#endif 

  long   l= 20;
  const char   *ntbs="Le minot passait la piece a frotter";
  char   c;
  char   buf[50];

#ifndef _RWSTD_NO_EXCEPTIONS
  try {
#endif

    // create a read/write file-stream object on char
    // and attach it to an ifstream object
    ifstream in("ifstream.results.out",ios_base::in | ios_base::out |
		ios_base::trunc);

    if ( !in.is_open() ) 
#ifndef _RWSTD_NO_EXCEPTIONS
      throw(ios_base::failure("Open error"));
#else
    abort();
#endif

    // tie the ostream object to the ifstream object
    ostream out(in.rdbuf());   

    // output ntbs in out
    out << ntbs << endl;

    // seek to the beginning of the file
    in.seekg(0);

    // output each word on a separate line
    while ( in.get(c) )
    {
      if ( ifstream::traits_type::eq(c,' ') ) 
        cout << endl;
      else
        cout << c;
    }
    cout << endl << endl;

	// clear the state flags, fail bit set by last call to in.get(c)
	in.clear();

    // move back to the beginning of the file
    in.seekg(0); 

    // does the same thing as the previous code
    // output each word on a separate line
    while ( in >> buf )
      cout << buf << endl; 
    
    cout << endl << endl;

	// clear the flags, last in >> buf set fail bit because of nl at end of string
	in.clear(); 

    // output the base info before each integer
    out << showbase;

    ostream::pos_type pos= out.tellp();

    // output l in hex with a field with of 20 
    out << hex << setw(20) << l << endl;

    // output l in oct with a field with of 20
    out << oct << setw(20) << l << endl;

    // output l in dec with a field with of 20
    out << dec << setw(20) << l << endl;

    // move back to the beginning of the file
    in.seekg(0);

    // output the all file
    cout << in.rdbuf();

	// clear the flags 
	in.clear(); 

    // seek the input sequence to pos  
    in.seekg(pos);
  
    int a,b,d;

    in.unsetf(ios_base::basefield);

    // read the previous outputted integer
    in >> a >> b >> d;

    // output 3 times 20
    cout << a << endl << b << endl << d << endl;

#ifndef _RWSTD_NO_EXCEPTIONS
  }
  catch( ios_base::failure var )
  {
    cout << var.what();
  }
#endif   
 
  return 0;
}




