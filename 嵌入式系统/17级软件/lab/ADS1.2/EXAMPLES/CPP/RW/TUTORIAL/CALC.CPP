/**************************************************************************
 *
 * calc.cpp - RPN Calculator -- Illustration of the use of stacks.
 *      Section 10.2.1
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
#include <stack>

#ifdef _RW_STD_IOSTREAM
#include <iostream>
#else
#include <iostream.h>
#endif
    
#ifndef _RWSTD_NO_NAMESPACE
using namespace std;
#endif

//
// Simulate the behavior of a simple integer calculator.
//

class CalculatorEngine
{
  public:
    enum binaryOperator { PLUS, MINUS, TIMES, DIVIDE };
    int  currentMemory ()                { return data.top(); }
    void pushOperand   (int value)       { data.push (value); }
    void doOperator    (binaryOperator);
  protected:
    stack< int, vector<int,allocator<int> > > data;
};

void CalculatorEngine::doOperator (binaryOperator theOp)
{
    int right = data.top();
    data.pop();
    int left = data.top();
    data.pop();
    switch (theOp)
    {
        case PLUS:   data.push(left + right); break;
        case MINUS:  data.push(left - right); break;
        case TIMES:  data.push(left * right); break;
        case DIVIDE: data.push(left / right); break;
    }
}

int main()
{
    cout << "Calculator example program, from Chapter 8" << endl;

    cout << "Enter a legal RPN expression, end with p q (print and quit)" << endl;
    int intval;
    CalculatorEngine calc;
    char c;
    
    while (cin >> c)
        switch (c)
        {
            case '0': case '1': case '2': case '3': case '4':
            case '5': case '6': case '7': case '8': case '9':
                cin.putback(c);
                cin >> intval;
                calc.pushOperand(intval);
                break;
            case '+': 
                calc.doOperator(CalculatorEngine::PLUS); break;
            case '-': calc.doOperator(CalculatorEngine::MINUS); break;
            case '*': calc.doOperator(CalculatorEngine::TIMES); break;
            case '/': calc.doOperator(CalculatorEngine::DIVIDE); break;
            case 'p': cout << calc.currentMemory() << endl; break;
            case 'q': cout << "End calculator program" << endl;
                return 0; // quit program
        }
    return 0;
}
