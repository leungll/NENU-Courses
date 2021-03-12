/**************************************************************************
 *
 * alg7.cpp - Illustrate the use of the sort related generic algorithms.
 *    Section 13
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
#include <deque>
#include <list>
#include <algorithm>
#include <functional>

#ifdef _RW_STD_IOSTREAM
#include <iostream>
#else
#include <iostream.h>
#endif

#ifndef _RWSTD_NO_NAMESPACE
using namespace std;
#endif
    
int randomInteger (unsigned int n) { return rand() % n; }
    
int randomValue () { return randomInteger(100); }

ostream_iterator<int,char,char_traits<char> > intOut(cout, " ");
        
void sortExample ()
{
    cout << "Sort algorithms"  << endl;
    //
    // Fill both a vector and a deque with random integers.
    //
    vector<int,allocator<int> > aVec(15);
    deque<int,allocator<int> >  aDec(15);
    generate (aVec.begin(), aVec.end(), randomValue);
    generate (aDec.begin(), aDec.end(), randomValue);
    //
    // Sort the vector ascending.
    //
    sort (aVec.begin(), aVec.end());
    copy (aVec.begin(), aVec.end(), intOut);
    cout << endl;
    //
    // Sort the deque descending.
    //
    sort (aDec.begin(), aDec.end(), greater<int>() );
    copy (aDec.begin(), aDec.end(), intOut);
    cout << endl;
    //
    // Sort the vector descending?
    //
    sort (aVec.rbegin(), aVec.rend());
    copy (aVec.begin(), aVec.end(), intOut);
    cout << endl;
}

void partial_sort_example ()
{
    cout << "Partial sort examples" << endl;
    //
    // Make a vector of 15 random integers.
    //
    vector<int,allocator<int> > aVec(15);
    generate (aVec.begin(), aVec.end(), randomValue);
    copy (aVec.begin(), aVec.end(), intOut);
    cout << endl;
    //
    // Partial sort the first seven positions.
    //
    partial_sort (aVec.begin(), aVec.begin() + 7, aVec.end());
    copy (aVec.begin(), aVec.end(), intOut);
    cout << endl;
    //
    // Make a list of random integers.
    //
    list<int,allocator<int> > aList((list<int,allocator<int> >::size_type)15, 0);
    generate (aList.begin(), aList.end(), randomValue);
    copy (aList.begin(), aList.end(), intOut);
    cout << endl;
    //
    // Sort only the first seven elements.
    //
    vector<int,allocator<int> > start(7);
    partial_sort_copy (aList.begin(), aList.end(),
                       start.begin(), start.end(), greater<int>());
    copy (start.begin(), start.end(), intOut);
    cout << endl;   
}

//
// Illustrate the use of the nth_largest function.
//

void nth_element_example () 
{
    cout << "Nth largest example" << endl;
    //
    // Make a vector of random integers.
    //
    vector<int,allocator<int> > aVec(10);
    generate (aVec.begin(), aVec.end(), randomValue);
    //
    // Now find the 5th largest.
    //
    vector<int,allocator<int> >::iterator nth = aVec.begin() + 4;
    nth_element(aVec.begin(), nth, aVec.end());
    cout << "fifth largest is " << *nth << " in" << endl;
    copy (aVec.begin(), aVec.end(), intOut);
    cout << endl;
}

//
// Illustrate the use of the binary search functions.
//

void binary_search_example ()
{
    cout << "Binary search example" << endl;
    //
    // Make an ordered vector of 15 random integers.
    //
    vector<int,allocator<int> > aVec(15);
    generate (aVec.begin(), aVec.end(), randomValue);
    sort (aVec.begin(), aVec.end());
    copy (aVec.begin(), aVec.end(), intOut),   cout << endl;
    //
    // See if it contains an eleven.
    //
    if (binary_search(aVec.begin(), aVec.end(), 11))
        cout << "contains an 11" << endl;
    else
        cout << "does not contain an 11"  << endl;
    //
    // Insert an 11 and a 14.
    //
    vector<int,allocator<int> >::iterator where;
    where = lower_bound (aVec.begin(), aVec.end(), 11);
    aVec.insert (where, 11);
    where = upper_bound (aVec.begin(), aVec.end(), 14);
    aVec.insert (where, 14);
    copy (aVec.begin(), aVec.end(), intOut),   cout << endl;
}

//
// Illustrate the use of the merge function.
//

void merge_example ()
{
    cout << "Merge algorithm examples" << endl;
    //
    // Make a list and vector of 10 random integers.
    //
    vector<int,allocator<int> > aVec(10);
    list<int,allocator<int> > aList((list<int,allocator<int> >::size_type)10, 0);
    generate (aVec.begin(), aVec.end(), randomValue);
    sort (aVec.begin(), aVec.end());
    generate_n (aList.begin(), 10, randomValue);
    aList.sort();
    //
    // Merge into a vector.
    //
    vector<int,allocator<int> > vResult (aVec.size() + aList.size());
    merge (aVec.begin(), aVec.end(), aList.begin(), aList.end(), 
           vResult.begin());
    //
    // Merge into a list.
    //
    list<int,allocator<int> > lResult;
    merge (aVec.begin(), aVec.end(), aList.begin(), aList.end(), 
           inserter(lResult, lResult.begin()));
    //
    // Merge into the output.
    //
    merge (aVec.begin(), aVec.end(), aList.begin(), aList.end(), 
           ostream_iterator<int,char,char_traits<char> >(cout, " "));
    cout << endl;
}

class iotaGen
{
  public:
    iotaGen (int c = 0) : current(c) { }
    int operator () () { return current++; }
  private:
    int current;
};

//
// Illustrate the use of the generic set functions.
//

void set_example ()

{
    cout << "Set operations:" << endl;
    //
    // Make a couple of ordered lists.
    //
    list <int,allocator<int> > listOne, listTwo;
    generate_n (inserter(listOne, listOne.begin()), 5, iotaGen(1));
    generate_n (inserter(listTwo, listTwo.begin()), 5, iotaGen(3));
    //
    // union - 1 2 3 4 5 6 7
    //
    set_union (listOne.begin(), listOne.end(),
               listTwo.begin(), listTwo.end(), intOut);
    cout << endl;
    //
    // merge - 1 2 3 3 4 4 5 5 6 7
    //
    merge (listOne.begin(), listOne.end(),
           listTwo.begin(), listTwo.end(), intOut);
    cout << endl;
    //
    // intersection 3 4 5
    //
    set_intersection (listOne.begin(), listOne.end(),
                      listTwo.begin(), listTwo.end(), intOut);
    cout << endl;
    //
    // difference 1 2
    //
    set_difference (listOne.begin(), listOne.end(),
                    listTwo.begin(), listTwo.end(), intOut);
    cout << endl;
    //
    // symmetric difference 1 2 6 7
    //
    set_symmetric_difference (listOne.begin(), listOne.end(), 
                              listTwo.begin(), listTwo.end(), intOut);
    cout << endl;
        
    if (includes(listOne.begin(), listOne.end(),
            listTwo.begin(), listTwo.end()))
                cout << "set is subset" << endl;
    else
        cout << "set is not subset" << endl;
}

//
// Illustrate the use of the heap functions.
//

void heap_example ()
{
    ostream_iterator<int,char,char_traits<char> > intOut(cout, " ");
    //
    // Make a heap of 15 random integers.
    //
    vector<int,allocator<int> > aVec(15);
    generate (aVec.begin(), aVec.end(), randomValue);
    make_heap (aVec.begin(), aVec.end());
    copy (aVec.begin(), aVec.end(), intOut);
    cout << endl;
    cout << "Largest value " << aVec.front() << endl;
    //
    // Remove largest and reheap.
    //
    pop_heap(aVec.begin(), aVec.end());
    aVec.pop_back();
    copy (aVec.begin(), aVec.end(), intOut);
    cout << endl;
    //
    // Add a 97 to the heap.
    //
    aVec.push_back(97);
    push_heap (aVec.begin(), aVec.end());
    copy (aVec.begin(), aVec.end(), intOut);
    cout << endl;
    //
    // Finally, make into sorted collection.
    //
    sort_heap (aVec.begin(), aVec.end());
    copy (aVec.begin(), aVec.end(), intOut);
    cout << endl;
}

int main ()
{
    cout << "Sorting generic algorithms examples" << endl;

    sortExample();
    partial_sort_example();
    nth_element_example();
    binary_search_example();
    merge_example();
    set_example();
    heap_example();
    
    cout << "End sorting examples" << endl;

    return 0;
}
