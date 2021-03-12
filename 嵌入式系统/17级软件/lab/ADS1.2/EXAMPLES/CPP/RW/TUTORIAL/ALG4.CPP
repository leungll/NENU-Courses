/**************************************************************************
 *
 * alg4.cpp - Example programs for STL generic algorithms removal 
 *    algorithms. Section 12.5
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

#include <list>
#include <set>
#include <algorithm>

#ifdef _RW_STD_IOSTREAM
#include <iostream>
#else
#include <iostream.h>
#endif

#ifndef _RWSTD_NO_NAMESPACE
using namespace std;
#endif
    
bool isEven (int n) { return 0 == (n % 2); }

//
// Illustrate the use of the remove algorithm.
//

void remove_example ()
{
    cout << "Remove Algorithm examples" << endl;
    //
    // Create a list of numbers.
    //
    int data[] = { 1, 2, 4, 3, 1, 4, 2 };
    list<int,allocator<int> > aList;
    copy (data, data+7, inserter(aList, aList.begin()));
    cout << "Original list: ";
    copy (aList.begin(), aList.end(), ostream_iterator<int,char,char_traits<char> >(cout, " "));
    cout << endl;
    //
    // Remove 2's, copy into a new list.
    //
    list<int,allocator<int> > newList;
    remove_copy (aList.begin(), aList.end(), back_inserter(newList), 2);
    cout << "After removing 2's: ";
    copy (newList.begin(), newList.end(), ostream_iterator<int,char,char_traits<char> >(cout, " "));
    cout << endl;
    //
    // Remove 2's in place.
    //
    list<int,allocator<int> >::iterator where;
    where = remove(aList.begin(), aList.end(), 2);
    cout << "List after removal, before erase: ";
    copy (aList.begin(), aList.end(), ostream_iterator<int,char,char_traits<char> >(cout, " "));
    cout << endl;
    aList.erase(where, aList.end());
    cout << "List after erase: ";
    copy (aList.begin(), aList.end(), ostream_iterator<int,char,char_traits<char> >(cout, " "));
    cout << endl;
    //
    // Remove all even values.
    //
    where = remove_if (aList.begin(), aList.end(), isEven);
    aList.erase(where, aList.end());
    cout << "List after removing even values: ";
    copy (aList.begin(), aList.end(), ostream_iterator<int,char,char_traits<char> >(cout, " "));
    cout << endl;
}

//
// Illustrate use of the unqiue algorithm.
//
void unique_example ()
{
    //
    // First make a list of values.
    //
    int data[] = { 1, 3, 3, 2, 2, 4 };
    list<int,allocator<int> > aList;
    copy(data, data+6, inserter(aList, aList.begin()));
    cout << "Origianal List: ";
    copy(aList.begin(), aList.end(), ostream_iterator<int,char,char_traits<char> >(cout, " "));
    cout << endl;
    //
    // Copy unique elements into a set.
    //
    set<int, less<int>,allocator<int>  > aSet;
//    unique_copy(aList.begin(), aList.end(), inserter(aSet, aSet.begin()));
    cout << "Set after unique_copy: ";
    copy(aSet.begin(), aSet.end(), ostream_iterator<int,char,char_traits<char> >(cout, " "));
    cout << endl;
    //
    // Copy unique elements in place.
    //
    list<int,allocator<int> >::iterator where;
    where = unique(aList.begin(), aList.end());
    cout << "List after calling unique: ";
    copy(aList.begin(), aList.end(), ostream_iterator<int,char,char_traits<char> >(cout, " "));
    cout << endl;
    //
    // Remove trailing values.
    //
    aList.erase(where, aList.end());
    cout << "List after erase: ";
    copy(aList.begin(), aList.end(), ostream_iterator<int,char,char_traits<char> >(cout, " "));
    cout << endl;
}

int main ()
{
    cout << "STL generic algorithms -- Removal Algorithms" << endl;

    remove_example();
    unique_example();
    
    cout << "End of removal algorithms sample program" << endl;

    return 0;
}
