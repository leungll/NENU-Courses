/**************************************************************************
 *
 * numget.cpp - Example program for the numget facet. 
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
#include <sstream>

int main ()
{
#ifndef _RWSTD_NO_NAMESPACE
  using namespace std;
#endif

  typedef istreambuf_iterator<char,char_traits<char> > iter_type;
  
  locale loc;
  ios_base::iostate state;
  bool bval = false;
  long lval = 0L;
  long double ldval = 0.0;
  iter_type end;

  // Get a num_get facet
  const num_get<char,iter_type>& tg = 
#ifndef _RWSTD_NO_TEMPLATE_ON_RETURN_TYPE
    use_facet<num_get<char,iter_type> >(loc);
#else
    use_facet(loc,(num_get<char,iter_type>*)0);
#endif
#ifndef _RWSTD_NO_BOOL
  {
    // Build an istringstream from the buffer and construct
    // beginning and ending iterators on it.
    istringstream ins("true");
    iter_type begin(ins);

    // Get the time
    tg.get(begin,end,ins,state,bval);
  }
#endif
  cout << bval << endl;
  {
    // Get the date
    istringstream ins("2422235");
    iter_type begin(ins);
    tg.get(begin,end,ins,state,lval);
  }
  cout << lval << endl;
  {
    // Get the weekday
    istringstream ins("32324342.98908");
    iter_type begin(ins);
    tg.get(begin,end,ins,state,ldval);
  }
  cout << ldval << endl;

  return 0;
}

