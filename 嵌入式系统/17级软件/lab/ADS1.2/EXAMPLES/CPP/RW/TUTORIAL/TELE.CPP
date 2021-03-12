/**************************************************************************
 *
 * tele.cpp - telephone directory sample program, from section 9.3.1
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

# include <map>
# include <algorithm>
# include <vector>

#ifdef _RW_STD_IOSTREAM
#include <iostream>
#else
#include <iostream.h>
#endif
   
# include <string>

#ifndef _RWSTD_NO_NAMESPACE
using namespace std;
#endif

typedef map<string, long, less<string>,allocator<string>  > friendMap;
typedef map<long, string, less<long>,allocator<long>  >   sortedMap;

//
// Utility functions used in telephone directory.
//

typedef friendMap::value_type entry_type;
typedef sortedMap::value_type sorted_entry_type;

#ifndef HPPA_WA
void printEntry (const entry_type & entry)
#else
void printEntry (const entry_type entry)
#endif
{
    cout << entry.first << ":" << entry.second << endl;
}

#ifndef HPPA_WA
void printSortedEntry (const sorted_entry_type & entry)
#else
void printSortedEntry (const sorted_entry_type entry)
#endif 
{
    cout << entry.first << ":" << entry.second << endl;
}

int prefix (const entry_type& entry) { return entry.second / 10000; }

bool prefixCompare (const entry_type & a, const entry_type & b)
{
    return prefix(a) < prefix(b);
}
    
class checkPrefix
{
  public:
    checkPrefix (int p) : testPrefix(p) { }
    int testPrefix;
    bool operator () (const entry_type& entry)
    {
        return prefix(entry)==testPrefix;
    }
};
            
class telephoneDirectory
{
  public:
    void addEntry (string name, long number) { database[name] = number; }
        
    void remove (string name) { database.erase(name); }
    
    void update (string name, long number)
    {
        remove(name);addEntry(name,number);
    }
        
    void displayDatabase()
    {
        for_each(database.begin(), database.end(), printEntry);
    }
    
    void displayPrefix(int);
    
    void displayByPrefix(); 
    
private:
    friendMap database;
};

void telephoneDirectory::displayPrefix (int prefix)
{
    cout << "Listing for prefix " << prefix << endl;
    map<string, long, less<string>,allocator<string>  >::iterator where;
    where = find_if(database.begin(), database.end(), checkPrefix(prefix));
    while (where != database.end())
    {
        printEntry(*where);
        where = find_if(++where, database.end(), checkPrefix(prefix));
    }
    cout << "end of prefix listing" << endl;
}

void telephoneDirectory::displayByPrefix ()
{
    cout << "Display by prefix" << endl;

    sortedMap sortedData;
    for (friendMap::iterator i = database.begin(); i != database.end(); i++)
        sortedData.insert(sortedMap::value_type((*i).second, (*i).first));
    for_each(sortedData.begin(), sortedData.end(), printSortedEntry);

    cout << "end display by prefix" << endl;
}

int main ()
{
    cout << "Telephone Directory sample program" << endl;

    telephoneDirectory friends;
    friends.addEntry("Samantha", 6342343);
    friends.addEntry("Brenda", 5436546);
    friends.addEntry("Fred", 7435423);
    friends.addEntry("Allen", 6348723);
    friends.displayDatabase();
    friends.displayPrefix(634);
    friends.displayByPrefix();
    
    cout << "End of telephone directory sample program" << endl;

    return 0;
}
