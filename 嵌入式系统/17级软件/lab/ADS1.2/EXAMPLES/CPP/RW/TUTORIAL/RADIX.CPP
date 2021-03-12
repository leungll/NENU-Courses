/**************************************************************************
 *
 * radix.cpp - radix sort program.  Section 7.3
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

#include <deque>
#include <list>
#include <vector>
#include <algorithm>
#include <numeric>

#ifdef _RW_STD_IOSTREAM
#include <iostream>
#else
#include <iostream.h>
#endif
    
#ifndef _RWSTD_NO_NAMESPACE
using namespace std;
#endif

class copyIntoBuckets
{
  public:
    copyIntoBuckets (int d, vector< deque<unsigned int,
          allocator<int> >, allocator<int>  > & b, bool & f) 
      : divisor(d), buckets(b), flag(f) {}
    int divisor;
    vector< deque<unsigned int,allocator<int> >, allocator<int>  > & buckets;
    bool & flag;
    void operator () (unsigned int v)
    {
        int index = (v / divisor) % 10;
        //
        // Flag is set to true if any bucket other than zeroth is used.
        //
        if (index) flag = true; 
        buckets[index].push_back(v);
    }
};

#ifndef HPPA_WA
list<unsigned int,allocator<int> >::iterator listCopy (list<unsigned int,allocator<int> >::iterator c,
                                       deque<unsigned int,allocator<int> > & lst)
#else
list<unsigned int,allocator<int> >::iterator listCopy (list<unsigned int,allocator<int> >::iterator c,
                                       deque<unsigned int,allocator<int> > lst)
#endif
{
    return copy(lst.begin(), lst.end(), c);
}

void radixSort (list<unsigned int,allocator<int> > & values)
{
    bool flag   = true;
    int divisor = 1;
    
    while (flag)
    {
        vector< deque<unsigned int,allocator<int> >, allocator<int>  > buckets(10);
        flag = false;
        for_each(values.begin(), values.end(), 
            copyIntoBuckets(divisor, buckets, flag));
        accumulate(buckets.begin(), buckets.end(), values.begin(), listCopy);
        divisor *= 10;
        copy(values.begin(), values.end(), ostream_iterator<int,char,char_traits<char> >(cout, " "));
        cout << endl;
    }
}

int main ()
{
    cout << "Radix sort program"  << endl;

    int data[] = { 624, 852, 426, 987, 269, 146, 415, 301, 730, 78, 593 };
    list<unsigned int,allocator<int> > values(11);
    copy(data, data + 11, values.begin());
    radixSort(values);
    copy(values.begin(), values.end(), ostream_iterator<int,char,char_traits<char> >(cout, " "));
    cout << endl;

    cout << "End radix sort program" << endl;

    return 0;   
}





