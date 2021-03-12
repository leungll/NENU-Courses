/**************************************************************************
 *
 * sieve.cpp -  sieve program.  Section 5.3
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

#include <vector>

#ifdef _RW_STD_IOSTREAM
#include <iostream>
#else
#include <iostream.h>
#endif
    
int main()
{
#ifndef _RWSTD_NO_NAMESPACE
    using namespace std;
#endif

    cout << "Prime Sieve program, a test of vectors" << endl;
    //
    // Create a sieve of bits, initially on.
    //
    const int sievesize = 100;
    vector<int,allocator<int> > sieve((size_t)sievesize, 1);
    //
    // Now search for 1 bt positions.
    //
    for (int i = 2; i * i < sievesize; i++)
        if (sieve[i])
            for (int j = i + i; j < sievesize; j += i)
                sieve[j] = 0;
    //
    // Now output all the values that are set.
    //
    for (int j = 2; j < sievesize; j++)
        if (sieve[j]) 
            cout << j << " ";
    cout << endl;
    
    cout << "End of Prime Sieve program" << endl;

    return 0;
}
