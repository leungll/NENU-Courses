/**************************************************************************
 *
 * stocks.cpp - Example program of money_punct,num_put,time_put facets.
 *            
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

#include "stocks.h"

locale::id   StockXchange::id;

#if defined(WIN32) || defined(_WIN32)
#define US_LOCALE             "us"
#define UK_LOCALE             "uk"
#define GERMAN_LOCALE         "deu"
#define FRENCH_LOCALE         "fra"
#define JAPANESE_LOCALE       "jpn"
#else
#define US_LOCALE             "en_US"
#define UK_LOCALE             "en_UK"
#define GERMAN_LOCALE         "de"
#define FRENCH_LOCALE         "fr"
#define JAPANESE_LOCALE       "jp"
#endif /* WIN32 */

void  StockXchange::localTime(ostream& os) const
{
   struct tm timeb;
   memcpy(&timeb,tmb,sizeof(struct tm));
   char pat[] = "%b %d %X %p";
   const time_put<char,iter_type>& tp = 
#ifndef _RWSTD_NO_TEMPLATE_ON_RETURN_TYPE
   use_facet<time_put<char,iter_type> >(os.getloc());
#else
   use_facet(os.getloc(),(time_put<char,iter_type>*)0);
#endif
   iter_type begin(os);
   os<<"\t [";
   tp.put(begin,os,' ',&timeb,pat,pat+11);
   os<<"]"<<'\n';    
}

void  StockXchange::add(const string& name, double initPrice)
{
   companyDatabase.push_front(new Company(name,initPrice));     
}

bool  StockXchange::put(ostream& os) const
{ 
   locale loc = os.getloc();
   localTime(os); //display the local time

   const moneypunct<char,false>& mpunct =
#ifndef _RWSTD_NO_TEMPLATE_ON_RETURN_TYPE
         use_facet<moneypunct<char,false> >(loc);
#else
         use_facet(loc,(moneypunct<char,false>*)0);
#endif
 
   const num_put<char,iter_type>& np = 
#ifndef _RWSTD_NO_TEMPLATE_ON_RETURN_TYPE
         use_facet<num_put<char,iter_type> >(loc);
#else
         use_facet(loc,(num_put<char,iter_type>*)0);
#endif

   os<<'\n';
   os<<"Company"<<"\t\t\t"<<"Initial Price"<<"\t"<<"Current Price"<<"\t"<<"Volume"<<endl;
   os<<"-------"<<"\t\t\t"<<"------------"<<"\t"<<"----------"<<"\t"<<"______"<<endl;  
   os<<'\n';
   
   iter_type itbegin(os);//ostream-buf iterator  
   database::const_iterator begin = companyDatabase.begin();
   database::const_iterator end   = companyDatabase.end();

   while(begin<end)
      {
        Company *info = *begin++;
        info->updateStock();
        os<<info->companyName<<"\t\t";
        os<<mpunct.curr_symbol();
        np.put(itbegin,os,' ',info->offerPrice);
        os<<"\t\t";
        os<<mpunct.curr_symbol();
        np.put(itbegin,os,' ',info->stockPrice);
        os<<"\t\t";
        np.put(itbegin,os,' ',info->randomChange(info->stockPrice+10000));
        os<<'\n'; 
      }
   return 1;

}
ostream & operator<<(ostream& os, const StockXchange&)
{
    locale loc = os.getloc();
    const StockXchange& se_facet =
#ifndef _RWSTD_NO_TEMPLATE_ON_RETURN_TYPE
         use_facet<StockXchange >(loc);
#else
         use_facet(loc,(StockXchange*)0);
#endif
         se_facet.put(os);
    return os;
}


int main()
{
#ifndef _RWSTD_NO_NAMESPACE
    using namespace std;
#endif
#if defined(_MSC_VER)
    //to workaround a bug in msvc 5.0
    cin.rdbuf();
#endif
    typedef pair<StockXchange*, locale> sl_pair;
    typedef deque<sl_pair*, allocator<sl_pair*> > Xchange;
    Xchange sXchange;
    
    ostream       os(cout.rdbuf());

    //Add some hypothetical companies that went public.
    //("Company name" , "initial stock price")
   
    NewYorkStockXchange *nse = new NewYorkStockXchange;
    nse->add("Hyper Software",20.50);
    nse->add("Florida Fish",15.10);
    nse->add("Inka Inc",9.50);
    nse->add("Emory Chemicals",11.00);
 
    TokyoStockXchange* tse = new TokyoStockXchange;
    tse->add("Akiro Electronics",12.30);

    LondonStockXchange* lse   = new LondonStockXchange;   
    lse->add("Royal Beef",7.25);
    lse->add("Island Banks",34.00);

    FrankFurtStockXchange* fse   = new FrankFurtStockXchange;   
    fse->add("B\166rsen-Software",9.75);
    fse->add("M\174nchner R\174ck",19.75);
    
    ParisStockXchange* pse   = new ParisStockXchange;   
    pse->add("Wines Inc.",11.50);
    pse->add("Eiffel Co.",11.50);

    const char *p=setlocale(LC_ALL,UK_LOCALE);
    if (!p) cerr<<'\n'<<"Not a valid locale: UK_LOCALE"<<endl;
     else{
          os.imbue(locale(locale(UK_LOCALE),lse));
          sXchange.push_front(new sl_pair(pse,os.getloc()));
          os<<*lse;
         }

    p = setlocale(LC_ALL,US_LOCALE);
    if (!p) cerr<<'\n'<<"Not a valid locale: US_LOCALE"<<endl;
     else{
          os.imbue(locale(locale(US_LOCALE),nse));
          sXchange.push_front(new sl_pair(nse,os.getloc()));
          os<<*nse;
         }

    p = setlocale(LC_ALL,GERMAN_LOCALE);
    if (!p) cerr<<'\n'<<"Not a valid locale: GERMAN_LOCALE"<<endl;
     else{
          os.imbue(locale(locale(GERMAN_LOCALE),fse));
          sXchange.push_front(new sl_pair(fse,os.getloc()));
          os<<*fse;
         }

    p = setlocale(LC_ALL,FRENCH_LOCALE);
    if (!p) cerr<<'\n'<<"Not a valid locale: FRENCH_LOCALE"<<endl;
     else{
          os.imbue(locale(locale(FRENCH_LOCALE),pse));
          sXchange.push_front(new sl_pair(pse,os.getloc()));
          os<<*pse;
         }

    p = setlocale(LC_ALL,JAPANESE_LOCALE);
    if (!p) cerr<<'\n'<<"Not a valid locale: JAPANESE_LOCALE"<<endl;
     else{
          os.imbue(locale(locale(JAPANESE_LOCALE),tse));
          sXchange.push_front(new sl_pair(tse,os.getloc()));
          os<<*tse;
         }

    char q = 0;    
    for(;;) 
     {
       cout<<'\n'<<"Want to see another quote [enter 'q' to quit] ?"; 
       cin>>q;
       if(q!='q')
       {
         Xchange::const_iterator it_begin = sXchange.begin();
         Xchange::const_iterator it_end   = sXchange.end();
         while(it_begin<it_end)
         {
           os.imbue((*it_begin)->second);
           os<<(*(*it_begin)->first);
           it_begin++;
         }
       } else break;
     }   
    return 0;
}






