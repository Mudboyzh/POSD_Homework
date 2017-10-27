#ifndef STRUCT_H
#define STRUCT_H

#include "atom.h"
#include "variable.h"
#include <vector>
#include <string>

using std::string;

class Struct:public Term
{
public:
  Struct(Atom const & name, std::vector<Term *> args):_name(name), _args(args) {
    std::cout << "Struct: " << _name.symbol() << std::endl;
  }

  std::vector< Variable * >ref ;
  
  Term * args(int index) {
    return _args[index];
  } // Term args()

  Atom const & name() {
    return _name;
  } // Atom name()

  string symbol() const{
    string ret =_name.symbol() + "(";
    for(int i = 0; i < _args.size() - 1 ; i++){
      ret += _args[i]-> symbol() + ", ";
    }
    ret += _args[_args.size()-1]-> symbol() + ")";
    return  ret;
  } // string symbol()

  string value() const{
    string ret =_name.symbol() + "(";
    for(int i = 0; i < _args.size() - 1 ; i++) {

      if (_args[i]->className() == "Variable" ) {
        Variable *var = dynamic_cast<Variable *>(_args[i]);
        // term change type to variable  
        if (!var->_assignable) ret += var->value() + ", ";
        else ret += var-> symbol() + ", ";
      } // if variable
      else if (_args[i]->className() == "Struct" ) ret += _args[i]->value() + ", ";
      else ret += _args[i]-> symbol() + ", ";
      
    } // for

    if( _args[_args.size()-1]->className() == "Variable" ) {
      Variable *var = dynamic_cast<Variable *>(_args[_args.size()-1]);
      if ( !var->_assignable ) ret += var->value() + ")";
      else ret += var->symbol() + ")";
    } // if variable
    else if (_args[_args.size()-1]->className() == "Struct") ret += _args[_args.size()-1]->value() + ")";
    else ret += _args[_args.size()-1]-> symbol() + ")";

    return  ret;
  } // string value()

  string className() const{
      return "Struct" ;
  }

  bool match(Term &term) {
    Struct * ps = dynamic_cast<Struct *>(&term);
    if (ps){
      if (!_name.match(ps->_name))
        return false;
      if(_args.size()!= ps->_args.size())
        return false;
      for(int i=0;i<_args.size();i++){
        if(_args[i]->symbol() != ps->_args[i]->symbol())
            return false;
      }
      return true;
    }
    return false;
  } // bool match()

private:
  Atom _name;
  std::vector<Term *> _args;
};

#endif
