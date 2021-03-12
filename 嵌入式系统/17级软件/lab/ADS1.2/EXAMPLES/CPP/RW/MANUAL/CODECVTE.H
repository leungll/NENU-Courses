/**************************************************************************
 *
 * codecvte.h - Example of user defined codecvt facet. 
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
 
#include <locale>
#include <strstream>
#include <functional>
#include <algorithm>

#ifndef _RWSTD_NO_NAMESPACE
using std::codecvt;
using std::min;
#ifdef _RWSTD_NO_MBSTATE_T
using std::mbstate_t;
#endif
#endif

#define RWSTD_TABLE_SIZE 59
// 
// This facet performs a conversion from  Latin Alphabet No. 1 
// (ISO 8859-1) to U.S.  ASCII code page 437.  Some conversions are one
// way (from ISO to ASCII, but not back again) because this ASCII 
// code page has no equivilent to the ISO character.
//
class ex_codecvt : public codecvt<char,char,mbstate_t>
{
private:
    static char table_[RWSTD_TABLE_SIZE][3]; 
                           
protected:
  virtual result do_in(mbstate_t&,
      const char* from, const char* from_end, const char*& from_next,
      char* to, char* to_limit, char*& to_next) const
  {  
    bool match;
    int i = min(to_limit-to,from_end-from);
    from_next = from;
    to_next = to;
    for (int j =0; j < i; j++)
    {
      match = false;
      for (int k = 0; k < RWSTD_TABLE_SIZE; k++)
      {  
        if (*from_next >= table_[k][0] && 
            *from_next <= table_[k][1])
        {
          *to_next = table_[k][2];
          match = true;
          break;
        }
      }
      if (!match)
        *to_next = *from_next;
      from_next++;
      to_next++;
    }
    return ok;
  }

  virtual result do_out(mbstate_t&,
    const char* from, const char* from_end, const char*& from_next,
    char* to, char* to_limit, char*& to_next) const
  {
    bool match;
    int i = min(to_limit-to,from_end-from);
    from_next = from;
    to_next = to;
    for (int j =0; j < i; j++)
    {
      match = false;
      for (int k = 0; k < RWSTD_TABLE_SIZE; k++)
      {  
        if (*from_next == table_[k][2] && 
            table_[k][0] == table_[k][1])
        {
          *to_next = table_[k][1];
          match = true;
          break;
        }
      }
      if (!match)
        *to_next = *from_next;
      from_next++;
      to_next++;
    }
    return ok;
  }

  virtual bool do_always_noconv() const _RWSTD_THROW_SPEC_NULL
  { return false; }

  virtual int do_encoding() const _RWSTD_THROW_SPEC_NULL
  { return 1; }

  virtual int do_length (const mbstate_t&, const char* from,
                         const char* end, size_t max) const
  { return min((size_t)(end - from),max); }

  virtual int do_max_length() const _RWSTD_THROW_SPEC_NULL
  { return INT_MAX; }

};
 
char ex_codecvt::table_[RWSTD_TABLE_SIZE][3] =
                             { 0xa2, 0xa2, 0x9b,
                               0xa3, 0xa3, 0x9c,
                               0xa5, 0xa5, 0x9d,
                               0xa7, 0xa7, 0x15,
                               0xa8, 0xa8, 0x22,
                               0xaa, 0xaa, 0xa6,
                               0xab, 0xab, 0xae,
                               0xb5, 0xb5, 0xe6,
                               0xb6, 0xb6, 0x14,
                               0xb7, 0xb7, 0xfa,
                               0xba, 0xba, 0xa7,
                               0xbb, 0xbb, 0xaf,
                               0xbc, 0xbc, 0xac,
                               0xbd, 0xbd, 0xab,
                               0xbf, 0xbf, 0xa8,
                               0xc0, 0xc3, 0x41,
                               0xc4, 0xc4, 0x8e,
                               0xc5, 0xc5, 0x41,
                               0xc6, 0xc6, 0x92,
                               0xc7, 0xc7, 0x80,
                               0xc8, 0xc8, 0x45,
                               0xc9, 0xc9, 0x90,
                               0xca, 0xcb, 0x45,
                               0xcc, 0xcf, 0x49,
                               0xd1, 0xd1, 0xa5,
                               0xd2, 0xd5, 0x4f,
                               0xd6, 0xd6, 0x99,
                               0xd8, 0xd8, 0xed,
                               0xd9, 0xdb, 0x55,
                               0xdc, 0xdc, 0x9a,
                               0xdd, 0xdd, 0x59,
                               0xdf, 0xdf, 0xe1,
                               0xe0, 0xe0, 0x85,
                               0xe1, 0xe1, 0xa0,
                               0xe2, 0xe2, 0x83,
                               0xe3, 0xe3, 0x61,
                               0xe4, 0xe4, 0x84,
                               0xe5, 0xe5, 0x86,
                               0xe6, 0xe6, 0x91,
                               0xe7, 0xe7, 0x87,
                               0xe8, 0xe8, 0x8a,
                               0xe9, 0xe9, 0x82,
                               0xea, 0xea, 0x88,
                               0xeb, 0xeb, 0x89,
                               0xec, 0xec, 0x8d,
                               0xed, 0xed, 0xa1,
                               0xee, 0xee, 0x8c,
                               0xef, 0xef, 0x8b,
                               0xf1, 0xf1, 0xa4,
                               0xf2, 0xf2, 0x95,
                               0xf3, 0xf3, 0xa2,
                               0xf4, 0xf4, 0x93,
                               0xf5, 0xf5, 0x6f,
                               0xf6, 0xf6, 0x94,
                               0xf9, 0xf9, 0x97,
                               0xfa, 0xfa, 0xa3,
                               0xfb, 0xfb, 0x96,
                               0xfc, 0xfc, 0x81,
                               0xff, 0xff, 0x98 };

































