/***************************************************************************
 *
 * filebuf.cpp - basic_filebuf example
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
 
#include<iostream>
#include<fstream>

int main ( )
{
#ifndef _RWSTD_NO_NAMESPACE
  using namespace std;
#endif 


  // create a read/write file-stream object on tiny char
  // and attach it to the file "filebuf.out"
  ofstream out("filebuf.dat",ios_base::in |
               ios_base::out | ios_base::trunc );

  // tie the istream object to the ofstream object
  istream in(out.rdbuf());   

  // output to out
  out << "Il errait comme un ame en peine";
  
  // seek to the beginning of the file
  in.seekg(0);

  // output in to the standard output
  cout << in.rdbuf() << endl;

  // close the file "filebuf.out"
  out.close();

  // open the existing file "filebuf.out"
  // and truncate it
  out.open("filebuf.dat",ios_base::in |
           ios_base::out | ios_base::trunc);

  // set the buffer size
  out.rdbuf()->pubsetbuf(0,4096);
 
  // open the source code file
  ifstream ins("filebuf.cpp");

  //output it to filebuf.out
  out << ins.rdbuf();
  
  // seek to the beginning of the file
  out.seekp(0);

  // output the all file
  cout << out.rdbuf();  
  
  return 0;
}



