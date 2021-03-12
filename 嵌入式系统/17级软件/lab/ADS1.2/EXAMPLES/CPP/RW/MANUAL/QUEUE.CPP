/**************************************************************************
 *
 * queue.cpp - Example program of queues. See Class Reference Section
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

#include <queue>
#include <string>
#include <deque>
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
  // Make a queue using a deque container.
  //
  queue<int, list<int,allocator<int> > > q;
  //
  // Push a couple of values on then pop them off.
  //
  q.push(1);
  q.push(2);
  cout << q.front() << endl;
  q.pop();
  cout << q.front() << endl;
  q.pop();
  //
  // Make a queue of strings using a deque container.
  //
  queue<string,deque<string,allocator<string> > > qs;
  //
  // Push on a few strings then pop them back off.
  //
  int i;
  for (i = 0; i < 10; i++)
  {
    qs.push(string(i+1,'a'));
    cout << qs.front() << endl;
  }
  for (i = 0; i < 10; i++)
  {
    cout << qs.front() << endl;
    qs.pop();
  }

  return 0;
}
