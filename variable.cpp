#include "atom.h"
#include "number.h"
#include "variable.h"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

Variable::Variable(string s)
{
    _symbol = s;
}

string Variable::symbol() const
{
    return _symbol;
}

string Variable::value() const
{
    if (_value == "")
    {
        return _symbol;
    }
    // if(_value == "s(X)"){
    //     return "s(teddy)";
    // }
    return _value;
}
void Variable::setSymbol(string s)
{
    _symbol = s;
}

void Variable::setValue(string v)
{
    _value = v;
}

bool Variable::match(Term &term)
{
    if (_value == term.value())
        return true;

    bool flag = tag;
    // Variable *var = dynamic_cast<Variable *>(&term);

    if (tag)
    {
        // cout << "###### " << term.value() << endl;
        // cout << "###### " << term.symbol() << endl;
        _value = term.value();
        tag = false;

       
        if (arr[0] != NULL)
        {
            for (int i = 0; i < 5; i++)
            {
                if (arr[i] != NULL)
                {

                    // cout << this->symbol() << "&&&" << i << endl;
                    arr[i]->match(term);
                }
            }
        }
    }

    return flag;
}

// bool Variable::match(Number num)
// {

//     if (_value == num.value())
//     {
//         tag = false;
//         return true;
//     }
//     else if (tag)
//     {
//         _value = num.value();
//         tag = false;
//         return true;
//     }
//     return false;
// }

// bool Variable::match(Atom atom)
// {
//     if (_value == atom.symbol())
//     {
//         tag = false;
//         return true;
//     }

//     if (tag)
//     {
//         _value = atom.symbol();
//         tag = false;
//         return true;
//     }
//     return false;
// }

bool Variable::match(Variable &var)
{
    bool flag = tag;
    if (_value == "")
    {
        _value = var.symbol();
    }

    if (tag)
    {
        if (var.tag)
        {
            arr[index++] = &var;
            var.arr[var.index++] = this;
        }
        else
        {
            _value = var.value();
            tag = false;
        }
    }

    return flag;
}
