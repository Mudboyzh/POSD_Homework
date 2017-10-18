#include "atom.h"
#include "number.h"
#include "variable.h"

#include <string>
#include <sstream>
#include <iostream>
using namespace std;

Number::Number(double n)
{
    _number = n;
    text = to_string(_number);
    text2 = to_string(_number).substr(0, text.find("0"));

    if (text2.find_last_of(".") == text2.size() - 1)
    {
        _symbol = to_string(_number).substr(0, text2.find("."));
    }
    else
    {
        _symbol = text2;
    }
}

// string Number::value() const
// {
//     return _value;
// }

string Number::symbol() const
{
    return _symbol;
}

double Number::num()
{
    return _number;
}

bool Number::match(Term &term)
{
    // cout<< "$$$"<<endl;
     if ( term.isVariable == true) {
        //  cout<< "888"<<endl;
      return term.match(*this);
    }

    return symbol() == term.symbol();
}

// bool Number::match(Number number)
// {
//     return _number == number.num();
// }

// bool Number::match(Atom atom)
// {
//     return false;
// }

// bool Number::match(Variable &variable)
// {
//     if (variable.value() == std::to_string(_number))
//     {
//         variable.tag = false;
//         return true;
//     }

//     if (variable.tag)
//     {
//         variable.setValue(std::to_string(_number));
//         variable.tag = false;
//         return true;
//     }
//     return false;
// }