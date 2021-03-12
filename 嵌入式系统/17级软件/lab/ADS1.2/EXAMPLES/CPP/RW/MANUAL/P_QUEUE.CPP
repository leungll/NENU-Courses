/**************************************************************************
 *
 * p_queue.cpp - Example program of a priority queue.
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
 
 #include <queue>
 #include <deque>
 #include <vector>
 #include <string>
 
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
   // Make a priority queue of int  using a vector container.
   //
   priority_queue<int, vector<int,allocator<int> >, less<int> > pq;
   // 
   // Push a couple of values.
   //
   pq.push(1);
   pq.push(2);
   //
   // Pop a couple of values and examine the ends.
   //
   cout << pq.top() << endl;
   pq.pop();
   cout << pq.top() << endl;
   pq.pop();
   //
   // Make a priority queue of strings.
   //
   priority_queue<string,deque<string,allocator<string> >, less<string> > pqs;
   //
   // Push on a few strings then pop them back off.
   //
   int i;
   for (i = 0; i < 10; i++)
   {
     pqs.push(string(i+1,'a'));
     cout << pqs.top() << endl;
   }
   for (i = 0; i < 10; i++)
   {
     cout << pqs.top() << endl;
     pqs.pop();
   }
   //
   // Make a priority queue of strings using greater.
   //
   priority_queue<string,deque<string,allocator<string> >, 
                 greater<string> > pgqs;
   //
   // Push on a few strings then pop them back off.
   //
   for (i = 0; i < 10; i++)
   {
     pgqs.push(string(i+1,'a'));
     cout << pgqs.top() << endl;
   }
   for (i = 0; i < 10; i++)
   {
     cout << pgqs.top() << endl;
     pgqs.pop();
   }

   return 0;
}



