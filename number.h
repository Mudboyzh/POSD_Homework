#ifndef NUMBER_H_INCLUDED
#define NUMBER_H_INCLUDED

#include <string>
#include "term.h"
using std::string;

class Atom;
class Variable;
class Number : public Term
{
public:
  Number(double n);

  // string value() const;
  string symbol() const;
  double num();

  bool match(Term &term);
  // bool match(Number number);
  // bool match(Atom atom);
  // bool match(Variable &variable);

private:
  // string _value;
  string text;
  string text2;
  string _symbol;
  bool isVariable = true;
  double _number;
};

#endif