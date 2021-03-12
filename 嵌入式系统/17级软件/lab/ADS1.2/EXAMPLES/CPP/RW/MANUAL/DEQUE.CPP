/**************************************************************************
 *
 * deque.cpp - Example program for deque class. See Class Reference Section
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

#include <deque>
#include <string>

#ifdef _RW_STD_IOSTREAM
#include <iostream>
#else
#include <iostream.h>
#endif     

#ifndef _RWSTD_NO_NAMESPACE
  using namespace std;
#endif


deque<string,allocator<string> > deck_of_cards; 
deque<string,allocator<string> > current_hand;

void initialize_cards(deque<string,allocator<string> >& cards)
{
   cards.push_front("aceofspades");
   cards.push_front("kingofspades");
   cards.push_front("queenofspades");
   cards.push_front("jackofspades");
   cards.push_front("tenofspades");
   //
   // etc.
   //
}

template <class It, class It2> 
void print_current_hand(It start, It2 end) 
{
   while (start < end) 
     cout << *start++ << endl;
}


template <class It, class It2>
void deal_cards(It, It2 end)
{
   for (int i=0;i<5;i++)
   {
     current_hand.insert(current_hand.begin(),*end);
     deck_of_cards.erase(end++);
   }
}

void play_poker()
{
   initialize_cards(deck_of_cards);
   deal_cards(current_hand.begin(),deck_of_cards.begin()); 
}

int main () 
{
   play_poker();
   print_current_hand(current_hand.begin(),current_hand.end());
   return 0;
}



