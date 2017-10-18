#include "atom.h"
#include "number.h"
#include "variable.h"
#include <iostream>
#include <string>
using namespace std;

Atom::Atom(string s)
{
    _symbol = s;
}

string Atom::symbol() const
{
    return _symbol;
}

// string Atom::value() const
// {
//     return symbol() ;
// }

bool Atom::match(Term &term)
{
    

    if (term.isVariable == true)
    {
        // Variable *ps = dynamic_cast<Variable *>(&term);
        Atom atom(_symbol);
        return term.match(atom);

        // return term.match(*this);
    }
    return symbol() == term.symbol();
}
// bool Atom::match(Number number)
// {
//     return false;
// }

// bool Atom::match(Variable &variable)
// {
//     if(_symbol  == variable.value()){
//         variable.tag = false;
//         return true;
//     }

//     if (variable.tag)
//     {
//         variable.setValue(_symbol );
//         variable.tag = false;
//         return true;
//     }
//     return false;
// }
