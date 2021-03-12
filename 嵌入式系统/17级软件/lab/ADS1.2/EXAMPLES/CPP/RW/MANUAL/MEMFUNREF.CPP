/**************************************************************************
 *
 * memfunref.cpp - Example program for mem_fun and other member function
 *                 reference wrappers.  See Class Reference Section
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
#include <functional>

#ifdef _RW_STD_IOSTREAM
#include <iostream>
#else
#include <iostream.h>
#endif     

#ifndef _RWSTD_NO_NAMESPACE
using namespace std;
#endif        
          
template <class T> class subList  
{
public:
  //
  //
  int sort() 
  {
    l.sort();
    return 1;
  }
  subList(int * begin, int* end):l(begin,end){}
  int display()
  {
    copy(l.begin(),l.end(),ostream_iterator<int,char,char_traits<char> >(cout," "));
    cout<<endl;
    return 1;
  }
private:
  list<T, allocator<T> > l;
};


int main()
{
  int a1[] = {2,1,5,6,4};
  int a2[] = {11,4,67,3,14};
  subList<int> s1(a1,a1+5);
  subList<int> s2(a2,a2+5);
    
  // Build a list of subLists
    
  list<subList<int>, allocator<subList<int> > > l;
  l.insert(l.begin(),s1);
  l.insert(l.begin(),s2);

  // Sort each subList in the list
  for_each(l.begin(),l.end(),mem_fun_ref(&subList<int>::sort));
    
  // Display the contents of list
  for_each(l.begin(),l.end(),mem_fun_ref(&subList<int>::display));

  return 0;
}


