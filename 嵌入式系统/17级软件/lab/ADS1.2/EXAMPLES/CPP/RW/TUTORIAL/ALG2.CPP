/**************************************************************************
 *
 * alg2.cpp - test program for STL generic algorithm that search for 
 *    elements that satisfy a condition.  Section 12.3
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
#include <ctype.h>
#include <string>
#include <string.h>

#ifdef _RW_STD_IOSTREAM
#include <iostream>
#else
#include <iostream.h>
#endif

#ifndef _RWSTD_NO_NAMESPACE
using namespace std;
#endif

int randomInteger (int m) {   return rand() % m; }

bool isLeapYear (unsigned int year)
{
    if (year % 1000 == 0)
        return true;
    if (year % 100 == 0)
        return false;
    if (year % 4 == 0)
        return true;
    return false;
}


void split (const string & text, const string & separators,
            list<string,allocator<string> > & words)
{
    int n     = text.length();
    int start = text.find_first_not_of(separators);

    while ((start >= 0) && (start < n))
    {
        int stop = text.find_first_of(separators, start);
        if ((stop < 0) || (stop > n)) stop = n;
        words.push_back (text.substr(start, stop-start));
        start = text.find_first_not_of(separators, stop+1);
    }
}

//
// Illustrate use of the find function.
//

void find_test ()
{
    cout << "Test of algorithm find" << endl;

    int vintageYears[] = { 1967, 1972, 1974, 1980, 1995 };

    vector<int,allocator<int> >::iterator start = vintageYears;
    vector<int,allocator<int> >::iterator stop  = vintageYears + 5;
    
    vector<int,allocator<int> >::iterator where = find_if(start, stop, isLeapYear);
    
    if (where != stop)
        cout << "first vintage leap year is " << *where << endl;
    else
        cout << "no vintage leap years" << endl;
        
    where = find(start, stop, 1995);
    
    if (where != stop)
        cout << "1995 is position " << where - start << " in sequence" << endl;
    else
        cout << "1995 does not occur in sequence" << endl;
}

void find_adjacent_test ()
{
    cout << "Test of algorithm find adjacent" << endl;

    char * text = "The bookkeeper carefully opened the door";
    
    vector<char,allocator<char> >::iterator start = text;
    vector<char,allocator<char> >::iterator stop = text + strlen(text);
    
    vector<char,allocator<char> >::iterator where = start;
    
    cout << "In the text " << text << endl;

    while ((where = adjacent_find(where, stop)) != stop)
    {
        cout << "double " << *where << " in position " << where-start << endl;
        ++where;
    }
}

//
// Illustrate the use of the search function.
//

void search_test ()
{
    cout << "Test of algorithm search" << endl;

    char * base = "aspirations";
    char * text = "ration";
    
    char * where = search(base, base+strlen(base), text, text+strlen(text));
    
    if (*where != '\0')
        cout << "substring begins in position " << where - base << endl;
    else
        cout << "substring does not occur in text" << endl;
}

//
// Illustrate use of max_element and min_element algorithms.
//

void max_min_example ()
{
    cout << "Test of max and min algorithms " << endl;
    //
    // Make a vector of random numbers between 0 and 99.
    //
    vector<int,allocator<int> > numbers(25);
    for (int i = 0; i < 25; i++)
        numbers[i] = randomInteger(100);
    //
    // Print the maximum.
    //
    vector<int,allocator<int> >::iterator max = max_element(numbers.begin(), numbers.end());
    cout << "largest value was " << *max << endl;
    //
    // Example using strings.
    //
    string text = "it was the best of times, it was the worst of times.";
    list<string,allocator<string> >words;
    split(text, " .,!:;", words);
    cout << "The smallest word is "
        << * min_element(words.begin(), words.end())
        << " and the largest word is "
        << * max_element(words.begin(), words.end())
        << endl;
}

//
// Illustrate the use of the mismatch function.
//

void mismatch_test (char * a, char * b) 
{
    pair<char *, char *> differPositions(0, 0);
    char * aDiffPos;
    char * bDiffPos;

    if (strlen(a) < strlen(b))
    {
        differPositions = mismatch(a, a + strlen(a), b);
        aDiffPos = differPositions.first;
        bDiffPos = differPositions.second;
    }
    else
    {
        differPositions = mismatch(b, b + strlen(b), a);
        aDiffPos = differPositions.second;
        bDiffPos = differPositions.first;
    }
        
    cout << "string " << a;

    if (*aDiffPos == *bDiffPos)
        cout << " is equal to ";
    else if (*aDiffPos < *bDiffPos)
        cout << " is less than ";
    else
        cout << " is greater than ";

    cout << b << endl;
}

int main ()
{
    cout << "STL generic algorithms -- Searching Algorithms" << endl;

    find_test();
    find_adjacent_test();
    search_test();
    max_min_example();
    mismatch_test("goody", "goody");
    mismatch_test("good", "goody");
    mismatch_test("goody", "good");
    mismatch_test("good", "fred");
    mismatch_test("fred", "good");
    
    cout << "End of search algorithms test program" << endl;

    return 0;
}










