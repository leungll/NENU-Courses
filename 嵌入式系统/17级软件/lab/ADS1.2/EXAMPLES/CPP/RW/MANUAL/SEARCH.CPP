/**************************************************************************
 *
 * search.cpp - Example program of search algorithm.
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

#include <algorithm>
#include <list>
 
#ifdef _RW_STD_IOSTREAM
#include <iostream>
#else
#include <iostream.h>
#endif     

int main ()
{
#ifndef _RWSTD_NO_NAMESPACE
  using namespace std;
#endif

  //
  // Initialize a list sequence and subsequence with characters.
  //
  char seq[40]    = "Here's a string with a substring in it";
  char subseq[10] = "substring";
  list<char,allocator<char> > sequence(seq, seq+38);
  list<char,allocator<char> > subseqnc(subseq, subseq+9);
  //
  // Print out the original sequence.
  //
  cout << endl << "The subsequence, " << subseq << ", was found at the ";
  cout << endl << "location identified by a '*'" << endl << "     ";
  //
  // Create an iterator to identify the location of 
  // subsequence within sequence.
  //
  list<char,allocator<char> >::iterator place;
  //
  // Do search.
  //
  place = search(sequence.begin(), sequence.end(),
                 subseqnc.begin(), subseqnc.end());
  //
  // Identify result by marking first character with a '*'.
  //
  *place = '*';
  //
  // Output sequence to display result.
  //
  for (list<char,allocator<char> >::iterator i = sequence.begin(); i != sequence.end(); i++)
    cout << *i;
  cout << endl;

  return 0;
}
