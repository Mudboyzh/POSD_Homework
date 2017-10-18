#ifndef VARIABLE_H
#define VARIABLE_H

#include "term.h"
#include <string>
#include <vector>
using std::string;

class Number;
class Atom;
class Variable : public Term
{
public:
  Variable(string s);

  string value() const;
  string symbol() const;
  void setSymbol(string);
  void setValue(string);

  bool match(Term &term);
  // bool match(Number num);
  // bool match(Atom atom);
  bool match(Variable &var);
  bool tag = true;
  Variable *arr[5] = {};
  int index = 0;

private:
  string _symbol;
  string _value;
  bool isVariable = true;
};

#endif
