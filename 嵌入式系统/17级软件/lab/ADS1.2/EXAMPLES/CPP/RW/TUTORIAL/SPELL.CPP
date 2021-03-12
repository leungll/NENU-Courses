/**************************************************************************
 *
 * spell.cpp -  spell checking program.  Section 8.3
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

#include <string>
#include <set>

#ifdef _RW_STD_IOSTREAM
#include <iostream>
#include <fstream>
#else
#include <iostream.h>
#include <fstream.h>
#endif
    
#ifndef _RWSTD_NO_NAMESPACE
using namespace std;
#endif

void spellCheck (istream & dictionary, istream & text)
{
    typedef set <string, less<string>,allocator<string>  > stringset;
    stringset words, misspellings;
    string word;
    istream_iterator<string,char,char_traits<char>,ptrdiff_t > eof, dstream(dictionary);
    //
    // First read the dictionary.
    //
    copy(dstream,eof,inserter(words,words.begin()));
    //
    // Next read the text.
    //
    while (text >> word)
        if (! words.count(word))
            misspellings.insert(word);
    //
    // Finally, output all misspellings.
    //
    cout << endl;
    cout << "Misspelled words:" << endl;
    copy (misspellings.begin(), misspellings.end(),
        ostream_iterator<string,char,char_traits<char> >(cout, "\n"));
}

int main ()
{
    cout << "Enter text:";
    ifstream words("words");
    spellCheck(words, cin);
    cout << "End of spell check program" << endl;
    return 0;
}
