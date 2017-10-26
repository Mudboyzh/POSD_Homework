#ifndef ATOM_H
#define ATOM_H

#include <string>

using std::string;


class Term{

public:
  virtual string symbol() const= 0;

  virtual string value() const{
    return symbol();
  };

  virtual string className() const = 0 ;

  virtual bool match(Term & term) {
    return symbol() == term.symbol();
  }


};

class Atom : public Term{
public:
  string _symbol;
  
  Atom (string s):_symbol(s) {std::cout << "Var:["<< _symbol << "]\n";}

  string symbol() const{
    return _symbol;
  }
  string className() const{
    return "Atom";
  }

  bool match(Term & term) {
    if ( term.className() == "Variable") {
      return term.match(*this);
    }
    else return symbol() == term.symbol();
  }
};


#endif
