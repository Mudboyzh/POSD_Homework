#ifndef VARIABLE_H
#define VARIABLE_H

#include <string>
#include <vector>
#include "atom.h"
using std::string;

class Variable: public Term{
public:
  Variable(string s):_symbol(s){ std::cout << "Var symbol:[" << _symbol << "]\n"; }
  string const _symbol;
  // string _value ;
  Term * _value = NULL;
  bool _assignable = true;
  std::vector< Variable * >ref ;
   


  string value() const { 
    if (_assignable && _value == NULL ) return _symbol;
    else if ( _assignable && _value != NULL) return _value->symbol();
    return _value->value(); 
  }
  string symbol() const { return _symbol; }
  string className() const { return "Variable"; }

  bool match( Term & term ){
    bool ret = _assignable;
    if (_assignable) {
      _value = &term;
      _assignable = false;

      if ( ref.size() != 0 ) {
        int refSize = ref.size();
        for(int i = 0; i < refSize ; i++) {
          ref[i]->match(term);
        }
      }
    } // if assignable = true
    else {
      ret = ( _value->value() == term.value());
    }
    return ret;
  } // match with Term

  bool match( Variable & var ) {
    bool ret = _assignable;
    if (_assignable) {
      if ( var._assignable ){ 
        ref.push_back( &var ); 
        var.ref.push_back(this);
        // 互相紀錄對方
        _value = &var;
        var._value = this;
      }
      else {
        _value = &var;
        _assignable = false;
      }
      return ret;
    }
    else return _value->value() == var.value() ;
  } // match with Variable


};

#endif
