/***************************************************************************
 *
 * ostream1.cpp - ostream example
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
#include<iomanip>

int main ( )
{
#ifndef _RWSTD_NO_NAMESPACE
   using namespace std;
#endif 
   
   float f= 3.14159123;
   int   i= 22;
   char* s= "Why, one can hear the grass growing!";

   // create a read/write stringbuf object on tiny char
   // and attach it to an istringstream object
   istringstream in( ios_base::in | ios_base::out );
      
   // tie the ostream object to the istringstream object
   ostream out(in.rdbuf());

   out << "test beginning !" << endl;

   // output i in hexadecimal
   out << hex << i <<endl; 

   // set the field width to 10
   // set the padding character to '@'
   // and output i in octal
   out << setw(10) << oct << setfill('@') << i << endl;

   // set the precision to 2 digits after the separator
   // output f
   out << setprecision(3) << f << endl;

   // output the 17 first characters of s
   out.write(s,17);

   // output a newline character
   out.put('\n');

   // output s 
   out << s << endl;   

   // output the all buffer to standard output
   cout << in.rdbuf();     

   return 0;
}



