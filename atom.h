#ifndef ATOM_H
#define ATOM_H

#include <string>
#include <sstream>
using std::string;

template <class T>
class Iterator;
class Term{
public:
  virtual string symbol() const {return _symbol;}
  virtual string value() const {return symbol();}
  virtual bool match(Term & a);
  virtual Iterator<Term *> *createIterator();
  virtual Iterator<Term *> *createDFSIterator();
  virtual Iterator<Term *> *createBFSIterator();
  int arity() const {return 0;}
  Term *args(int index) { return nullptr; }
protected:
  Term ():_symbol(""){}
  Term (string s):_symbol(s) {}
  Term(double db){
    std::ostringstream strs;
    strs << db;
    _symbol = strs.str();
  }
  string _symbol;
};

class Atom : public Term{
public:
  Atom(string s):Term(s) {}
};

#endif
