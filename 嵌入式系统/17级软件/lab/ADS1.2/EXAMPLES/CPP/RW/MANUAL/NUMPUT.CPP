/**************************************************************************
 *
 * numput.cpp - Example program for the numput facet. 
 *              See Class Reference Section
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

#include <string>
#include <iostream>

int main ()
{
#ifndef _RWSTD_NO_NAMESPACE
  using namespace std;
#endif

  typedef ostreambuf_iterator<char,char_traits<char> > iter_type;
  
  locale loc;
  bool bval = true;
  long lval = 422432L;
  unsigned long ulval = 12328889UL;
  double dval = 10933.8934; 
  long double ldval = 100028933.8934; 

  // Construct a ostreambuf_iterator on cout
  iter_type begin(cout);

  // Get a num_put facet reference
  const num_put<char,iter_type>& np = 
#ifndef _RWSTD_NO_TEMPLATE_ON_RETURN_TYPE
    use_facet<num_put<char,iter_type> >(loc);
#else
    use_facet(loc,(num_put<char,iter_type>*)0);
#endif

  // Put out a bool
  cout << bval << " --> ";
  np.put(begin,cout,' ',bval);

  // Put out a long
  cout << endl << lval << " --> ";
  np.put(begin,cout,' ',lval);

  // Put out an unsigned long
  cout << endl << ulval << " --> ";
  np.put(begin,cout,' ',ulval);

  // Put out a double
  cout << endl << dval << " --> ";
  np.put(begin,cout,' ',dval);

  // Put out a long double
  cout << endl << ldval << " --> ";
  np.put(begin,cout,' ',ldval);

  cout <<  endl;

  return 0;
}



