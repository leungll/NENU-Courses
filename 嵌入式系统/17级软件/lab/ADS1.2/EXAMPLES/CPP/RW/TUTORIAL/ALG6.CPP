/**************************************************************************
 *
 * alg6.cpp - STL generic algorithms that produce new sequences
 *    section 12.7
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
#include <list>
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

int square (int n) { return n * n; }

class iotaGen
{
  public:
    iotaGen (int iv) : current(iv) { }
    int operator () () { return current++; }
  private:
    int current;
};

//
// Illustrate the use of the transform algorithm.
//

void transform_example ()

{
    //
    // Generate a list of values from 1 to 6.
    //
    list<int,allocator<int> > aList;
    generate_n (inserter(aList, aList.begin()), 6, iotaGen(1));
    cout << "Original list: ";
    copy(aList.begin(), aList.end(), ostream_iterator<int,char,char_traits<char> >(cout, " "));
    cout << endl;
    //
    // Transform elements by squaring, copy into vector.
    //
    vector<int,allocator<int> > aVec(6);
    transform (aList.begin(), aList.end(), aVec.begin(), square);
    cout << "After squaring: ";
    copy(aVec.begin(), aVec.end(), ostream_iterator<int,char,char_traits<char> >(cout, " "));
    cout << endl;
    //
    // Transform vector again, in place, yielding 4th powers.
    //
    transform (aVec.begin(), aVec.end(), aVec.begin(), square);
    cout << "After squaring again: ";
    copy(aVec.begin(), aVec.end(), ostream_iterator<int,char,char_traits<char> >(cout, " "));
    cout << endl;
    //
    // Transform in parallel, yielding cubes.
    //
    vector<int,allocator<int> > cubes(6);
    transform (aVec.begin(), aVec.end(), aList.begin(), cubes.begin(),
               divides<int>());
    cout << "After division: ";
    copy(cubes.begin(), cubes.end(), ostream_iterator<int,char,char_traits<char> >(cout, " "));
    cout << endl;
}

//
// Illustrate the use of the partial sum algorithm.
//

void partial_sum_example ()
{
    //
    // Generate values 1 to 5.
    //
    vector<int,allocator<int> > aVec(5);
    generate (aVec.begin(), aVec.end(), iotaGen(1));
    //
    // Output partial sums.
    //
    cout << "Partial sums examples" << endl;
    cout << "Partial sums : ";
    partial_sum (aVec.begin(), aVec.end(), ostream_iterator<int,char,char_traits<char> >(cout, " "));
    cout << endl;
    //    
    // Output partial products.
    //
    cout << "Partial products: ";
    partial_sum (aVec.begin(), aVec.end(), 
                 ostream_iterator<int,char,char_traits<char> >(cout, " "),
                 multiplies<int>() );

    cout << endl;
}

//
// Illustrate the use of the adjacent difference algorithm.
//

void adjacent_difference_example ()
{
    //
    // Generate values 1 to 5.
    //
    vector<int,allocator<int> > aVec(5);
    generate (aVec.begin(), aVec.end(), iotaGen(1));
    //
    // Output partial sums.
    //
    cout << "Adjacent Differences examples" << endl;
    cout << "Adjacent Differences : ";
    adjacent_difference (aVec.begin(), aVec.end(),
                         ostream_iterator<int,char,char_traits<char> >(cout, " "));
    cout << endl;
    //
    // Output partial products.
    //
    cout << "Adjacent sums: ";
    adjacent_difference (aVec.begin(), aVec.end(),
                         ostream_iterator<int,char,char_traits<char> >(cout, " "), plus<int>());
    cout << endl;
}


int main ()
 {
    cout << "STL generic algorithms -- that transform sequences"  << endl;
    
    transform_example();
    partial_sum_example();
    adjacent_difference_example ();
    
    cout << "End generic transform algorithms example" << endl;

    return 0;
}







