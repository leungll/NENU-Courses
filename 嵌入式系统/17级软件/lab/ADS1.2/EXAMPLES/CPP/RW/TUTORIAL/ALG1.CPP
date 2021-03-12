/**************************************************************************
 *
 * alg1.cpp - Example program for STL generic algorithms that initialize 
 *    sequences.  Section 12.2
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

#include <iostream>

#ifndef _RWSTD_NO_NAMESPACE
using namespace std;
#endif

class iotaGen
{
  public:
    iotaGen (int iv) : current(iv) { }
    int operator () () { return current++; }
  private:
    int current;
};

//
// Illustrate the use of the fill and fill_n functions.
//

void fill_example ()
{
    cout << "Illustrate fill function" << endl;
    //
    // Example 1, fill an array with initial values
    //
    char buffer[100], *bufferp = buffer;
    fill (bufferp,(bufferp + 100),'\0');
    fill_n (bufferp, 10, 'x');
    cout << buffer << endl;
    //
    // Example 2, use fill to initialize a list.
    //
    list<string,allocator<string> > aList;
    fill_n (inserter(aList, aList.begin()), 10, "empty");
    copy(aList.begin(), aList.end(), ostream_iterator<string,char,char_traits<char> >(cout, " "));
    cout << endl;
    //
    // Example 3, use fill to overwrite values in a list.
    //
    fill (aList.begin(), aList.end(), "full");
    copy(aList.begin(), aList.end(), ostream_iterator<string,char,char_traits<char> >(cout, " "));
    cout << endl;
    //
    // Example 4, fill in a portion of a list.
    //
    vector<int,allocator<int> > iVec(10);
    generate (iVec.begin(), iVec.end(), iotaGen(1));
    vector<int,allocator<int> >::iterator seven = find(iVec.begin(), iVec.end(), 7);
#ifndef _RWSTD_FILL_NAME_CLASH
    fill(iVec.begin(), seven, 0);
#else
    std_fill(iVec.begin(), seven, 0);
#endif
    copy(iVec.begin(), iVec.end(), ostream_iterator<int,char,char_traits<char> >(cout));
    cout << endl;
}

//
// Illustrate the use of the copy function.
//

void copy_example ()
{
    cout << "Illustrate copy function " << endl;
    //
    // Example 1, a simple copy.
    //
    char * source  = "reprise";
    char * surpass = "surpass";
    char buffer[120], *bufferp = buffer;
    copy(source, source + strlen(source) + 1, bufferp);
    //
    // Example 2, self copies.
    //
    *copy(bufferp + 2, bufferp+ strlen(buffer), bufferp) = '\0';
    int buflen = strlen(buffer) + 1;
    copy_backward(bufferp, bufferp + buflen, bufferp + buflen + 3);
    copy(surpass, surpass + 3, bufferp);
    //
    // Example 3, copy to output.
    //
    copy(bufferp, bufferp + strlen(buffer), ostream_iterator<char,char,char_traits<char> >(cout));
    cout << endl;
    //
    // Example 4, use copy to convert type.
    //
    list<char,allocator<char> > char_list;
    copy(bufferp, bufferp + strlen(buffer),
         inserter(char_list,char_list.end()));
    char * big = "big ";
    copy(big, big + 4, inserter(char_list, char_list.begin()));
    
    char buffer2[200], *buffer2p = buffer2;
    *copy(char_list.begin(), char_list.end(), buffer2p) = '\0';
    cout << buffer2 << endl;
}


#include <sstream>

string generateLabel ()
{
    //
    // Generate a label string of the form L_ddd.
    //
    static int lastLabel = 0;
    ostringstream ost;
    ost << "L_" << lastLabel++;
    return ost.str();
}

//
// Illustrate the use of the generate and genrate_n functions.
//

void generate_example ()
{
    cout << "Illustrate generate algorithm" << endl;
    //
    // Example 1, generate a list of label numbers.
    //
    list<string,allocator<string> > labelList;
    generate_n (inserter(labelList, labelList.begin()), 4, generateLabel);  
    copy(labelList.begin(),labelList.end(),ostream_iterator<string,char,char_traits<char> >(cout," "));
    cout << endl;
    //
    // Example 2, generate an arithmetic progression.
    //
    vector<int,allocator<int> > iVec(10);
    generate (iVec.begin(), iVec.end(), iotaGen(2));
    generate_n (iVec.begin(), 5, iotaGen(7));
    copy (iVec.begin(), iVec.end(), ostream_iterator<int,char,char_traits<char> >(cout, " "));
    cout << endl;
}

//
// Illustrate the use of the algorithm swap_ranges.
//

void swap_example ()
{
    cout << "Illustrate swap_ranges algorithm" << endl;
    //
    // First make two parallel sequences.
    //
    int data[] = {12, 27, 14, 64}, *datap = data;
    vector<int,allocator<int> > aVec(4);
    generate (aVec.begin(), aVec.end(), iotaGen(1));
    //
    // Illustrate swap and swap_itr.
    //
    swap(data[0], data[2]);
    copy (data, data+4, ostream_iterator<int,char,char_traits<char> >(cout, " "));
    cout << endl;
    vector<int,allocator<int> >::iterator last = aVec.end(); last--;
    iter_swap(aVec.begin(), last);
    copy (aVec.begin(), aVec.end(), ostream_iterator<int,char,char_traits<char> >(cout, " "));
    cout << endl;
    //
    // Now swap the entire sequence.
    //
    swap_ranges (aVec.begin(), aVec.end(), datap);
    copy (data, data+4, ostream_iterator<int,char,char_traits<char> >(cout, " ")), cout << endl;
    copy (aVec.begin(), aVec.end(), ostream_iterator<int,char,char_traits<char> >(cout, " "));
    cout << endl;
}

int main ()
{
    cout << "STL generic algorithms -- initialization algorithms" << endl;

    fill_example();
    copy_example();
    generate_example();
    swap_example();
    
    cout << "End of initialization tests" << endl;

    return 0;
}
