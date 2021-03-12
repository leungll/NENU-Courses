/**************************************************************************
 *
 * indirect_array.cpp -- Indirect array examples 
 *                       See Class Reference Section
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

#include "valarray.h"  // Contains a valarray stream inserter

int main(void)
{
#ifndef _RWSTD_NO_NAMESPACE
  using namespace std;
#endif

  int ibuf[10] = {0,1,2,3,4,5,6,7,8,9};
  size_t sbuf[6] = {0,2,3,4,7,8};

  // create a valarray of ints
  valarray<int>         vi(ibuf,10);

  // create a valarray of indices for a selector
  valarray<size_t> selector(sbuf,6);

  // print out the valarray<int>
  cout << vi << endl;

  // Get a indirect_array 
  // and assign that indirect to another valarray
  indirect_array<int> select = vi[selector];
  valarray<int> vi3 = select;

  // print out the selective array
  cout << vi3 << endl;
  
  // Double the selected values
  select += vi3;

  // print out vi1 again
  cout << vi << endl;

  return 0;
}

