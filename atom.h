#ifndef ATOM_H
#define ATOM_H

#include <string>
#include "term.h"
using std::string;

class Number;
class Variable;
class Atom : public Term
{
public:
  Atom(string s);

  string symbol() const;
  // string value() const;
  
  bool match(Term &term);
  // bool match(Number number);
  // bool match(Variable &variable);

private:
  string _symbol;
  string _value;
  bool isVariable = false;
};

#endif
