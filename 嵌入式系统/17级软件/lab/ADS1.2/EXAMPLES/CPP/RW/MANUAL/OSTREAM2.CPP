/***************************************************************************
 *
 * ostream2.cpp - ostream example
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
#include<sstream>

int main ( )
{
#ifndef _RWSTD_NO_NAMESPACE
   using namespace std;
#endif 
   
   float f= 3.14159;

#ifndef _RWSTD_NO_WIDE_CHAR
   wchar_t* s= L"Kenavo !";

   // create a read/write stringbuf object on wide char
   // and attach it to an wistringstream object
   wistringstream in( ios_base::in | ios_base::out );
      
   // tie the wostream object to the wistringstream object
   wostream out(in.rdbuf());

   out << L"test beginning !" << endl;

   // output f in scientific format
   out << scientific << f <<endl; 

   // store the current put-pointer position  
   wostream::pos_type pos = out.tellp();

   // output s 
   out << s << endl;   

   // output the all buffer to standard output
   wcout << in.rdbuf() << endl;

   // position the get-pointer
   in.seekg(pos);

   // output s
   wcout << in.rdbuf() << endl;         
#else

   char* s= "Kenavo !";

   // create a read/write stringbuf object on char
   // and attach it to an istringstream object
   istringstream in( ios_base::in | ios_base::out );
      
   // tie the wostream object to the istringstream object
   ostream out(in.rdbuf());

   out << "test beginning !" << endl;

   // output f in scientific format
   out << scientific << f <<endl; 

   // store the current put-pointer position  
   ostream::pos_type pos = out.tellp();

   // output s 
   out << s << endl;   

   // output the all buffer to standard output
   cout << in.rdbuf() << endl;

   // position the get-pointer
   in.seekg(pos);

   // output s
   cout << in.rdbuf() << endl; 
#endif

   return 0;
}
 


