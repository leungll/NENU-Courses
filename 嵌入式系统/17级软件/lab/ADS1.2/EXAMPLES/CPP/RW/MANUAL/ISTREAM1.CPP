/***************************************************************************
 *
 * istream1.cpp - istream example
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
 
#include<iostream>
#include<istream>
#include<fstream>

int main ( )
{
#ifndef _RWSTD_NO_NAMESPACE
  using namespace std;
#endif 
 
  float f= 3.14159;
  int   i= 3;
  char  s[200];

  // open a file for read and write operations 
  ofstream out("example", ios_base::in | ios_base::out
               | ios_base::trunc);

  // tie the istream object to the ofstream filebuf 
  istream  in (out.rdbuf());

  // output to the file
  out << "He lifted his head and pondered." << endl;
  out << f << endl;
  out << i << endl;
  
  // seek to the beginning of the file
  in.seekg(0);
  
  f = i = 0;

  // read from the file using formatted functions
  in.getline(s, 200);
  in >> f >> i;

  // seek to the beginning of the file
  in.seekg(0,ios_base::beg);

  // output the all file to the standard output
  cout << in.rdbuf();

  // seek to the beginning of the file
  in.seekg(0);
 
  // read the first line in the file
  // "He lifted his head and pondered."
  in.getline(s,100);

  cout << s << endl;

  // read the second line in the file
  // 3.14159
  in.getline(s,100);

  cout << s << endl;

  // seek to the beginning of the file
  in.seekg(0);

  // read the first line in the file
  // "He lifted his head and pondered."
  in.get(s,100);

  // remove the newline character
  in.ignore();

  cout << s << endl;

  // read the second line in the file
  // 3.14159
  in.get(s,100);

  cout << s << endl;

  // remove the newline character
  in.ignore();

  // store the current file position   
  istream::pos_type position = in.tellg();
 
  out << endl << "replace the int" << endl;

  // move back to the previous saved position
  in.seekg(position);   

  // output the remain of the file
  // "replace the int"
  // this is equivalent of
  // cout << in.rdbuf();
  while( !ifstream::traits_type::eq_int_type( in.peek(),
                                              ifstream::traits_type::eof()) )
   cout << ifstream::traits_type::to_char_type(in.get()); 
 
  cout << "\n\n\n" << flush;

  return 0;
}




