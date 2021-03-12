/**************************************************************************
 *
 * timeget.cpp - Example program for the time_get facet. 
 *               See Class Reference Section
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

#include <locale>
#include <sstream>
#include <time.h>

#ifndef _RWSTD_NO_NAMESPACE
  using namespace std;
#endif

// Print out a tm struct
ostream& operator<< (ostream& os, const struct tm& t)
{
  os << "Daylight Savings = " << t.tm_isdst << endl;
  os << "Day of year      = " << t.tm_yday << endl;
  os << "Day of week      = " << t.tm_wday << endl;
  os << "Year             = " << t.tm_year << endl;
  os << "Month            = " << t.tm_mon << endl;
  os << "Day of month     = " << t.tm_mday << endl;
  os << "Hour             = " << t.tm_hour << endl;
  os << "Minute           = " << t.tm_min << endl;
  os << "Second           = " << t.tm_sec << endl;
  return os;
}

int main ()
{
  typedef istreambuf_iterator<char,char_traits<char> > iter_type;
  
  locale loc("");
  setlocale(LC_ALL, "");
  time_t tm = time(NULL);
  struct tm* tmb = localtime(&tm);
  struct tm timeb;
  struct tm timeb2;
  memcpy(&timeb,tmb,sizeof(struct tm));
  memcpy(&timeb2,tmb,sizeof(struct tm));
  timeb2.tm_mday=6;
  timeb2.tm_mon=11;
  timeb2.tm_year=96;
  ios_base::iostate state;
  iter_type end;

  // Get a time_get facet
  const time_get<char,iter_type>& tg = 
#ifndef _RWSTD_NO_TEMPLATE_ON_RETURN_TYPE
    use_facet<time_get<char,iter_type> >(loc);
#else
    use_facet(loc,(time_get<char,iter_type>*)0);
#endif

  cout << "Date order = " << tg.date_order() << endl;

  cout << timeb << endl;
  {
    // Build an istringstream from the buffer and construct
    // beginning and ending iterators on it.
    istringstream ins("12:46:32");
    iter_type begin(ins);

    // Get the time
    tg.get_time(begin,end,ins,state,&timeb);
  }
  cout << timeb << endl;
  {
    // Get the date
    char newDate[20];
    strftime(newDate, sizeof(newDate), "%x", &timeb2);
    istringstream ins(newDate);
    iter_type begin(ins);
    tg.get_date(begin,end,ins,state,&timeb);
    cout << "New Date = " << newDate << endl << timeb2 << endl;
  }
  cout << timeb << endl;
  {
    // Get the weekday
    istringstream ins("Tuesday");
    iter_type begin(ins);
    tg.get_weekday(begin,end,ins,state,&timeb);
  }
  cout << timeb << endl;
  return 0;
}

