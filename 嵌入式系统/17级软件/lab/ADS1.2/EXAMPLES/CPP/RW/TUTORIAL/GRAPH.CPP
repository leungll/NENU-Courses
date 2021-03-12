/**************************************************************************
 *
 * graph.cpp - Graph program.  Section 9.3.2
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

#include <map>
#include <vector>
#include <queue>

#ifdef _RW_STD_IOSTREAM
#include <iostream>
#else
#include <iostream.h>
#endif
    
#include <string>
#ifndef _RWSTD_NO_NAMESPACE
using namespace std;
using namespace std::rel_ops;
#endif

typedef map<string, int, less<string>,allocator<string>  >          stringVector;
typedef map<string, stringVector, less<string>,allocator<string>  > graph;

struct DistancePair
{
    unsigned first;
    string   second;
    DistancePair() : first(0) {}
    DistancePair(unsigned f, const string& s) : first(f), second(s) {}
};

bool operator< (const DistancePair& lhs, const DistancePair& rhs)
{
    return lhs.first < rhs.first;
}

bool operator> (const DistancePair& lhs, const DistancePair& rhs)
{
    return lhs.first > rhs.first;
}

string pendleton("Pendleton");
string pensacola("Pensacola");
string peoria("Peoria");
string phoenix("Phoenix");
string pierre("Pierre");
string pittsburgh("Pittsburgh");
string princeton("Princeton");
string pueblo("Pueblo");

graph cityMap;

void shortestDistance (graph& cityMap, string& start, stringVector& distances)
{
    //
    // Process a priority queue of distances to nodes.
    //
    priority_queue<DistancePair, vector<DistancePair,allocator<DistancePair> >,
        greater<DistancePair> > que;
    que.push(DistancePair(0, start));
    
    while (! que.empty())
    {
        //
        // Pull nearest city from queue.
        //
        int distance = que.top().first;
        string city = que.top().second;
        que.pop();
        //
        // If we haven't seen it already, process it.
        //
        if (0 == distances.count(city))
        {
            //
            // Then add it to shortest distance map.
            //
            distances[city] = distance;
            //
            // And put values into queue.
            //
            const stringVector& cities = cityMap[city];
            stringVector::const_iterator start = cities.begin();
            stringVector::const_iterator stop  = cities.end();
            for (; start != stop; ++start) 
                que.push(DistancePair(distance + (*start).second,
                                      (*start).first));
        }
    }
}

int main ()
{
    cout << "Graph example program, from Chapter 7" << endl;

    cityMap[pendleton][phoenix]    = 4;
    cityMap[pendleton][pueblo]     = 8;
    cityMap[pensacola][phoenix]    = 5;
    cityMap[peoria][pittsburgh]    = 5;
    cityMap[peoria][pueblo]        = 3;
    cityMap[phoenix][peoria]       = 4;
    cityMap[phoenix][pittsburgh]   = 10;
    cityMap[phoenix][pueblo]       = 3;
    cityMap[pierre][pendleton]     = 2;
    cityMap[pittsburgh][pensacola] = 4;
    cityMap[princeton][pittsburgh] = 2;
    cityMap[pueblo][pierre]        = 3;
    
    stringVector distances;
    
    shortestDistance(cityMap, pierre, distances);
    stringVector::iterator where;
    for (where = distances.begin(); where != distances.end(); ++where)
        cout << "Distance to: " << (*where).first << ":"
             <<  (*where).second << endl;
        
    cout << "End of graph example program" << endl;

    return 0;
}
