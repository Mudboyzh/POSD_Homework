#ifndef VARIABLE_H
#define VARIABLE_H

#include <string>
#include <vector>
#include "atom.h"
using std::string;

class Variable: public Term{
public:
  Variable(string s):_symbol(s){}
  string const _symbol;
  string _value ;
  bool _assignable = true;
  std::vector< Variable * >ref ;
   


  string value() const { 
    if (_assignable && _value.empty() ) return _symbol;
    return _value; 
  }
  string symbol() const { return _symbol; }
  string className() const { return "Variable"; }

  bool match( Term & term ){
    bool ret = _assignable;
    if (_assignable) {
      _value = term.value() ;
      _assignable = false;
      // if (term.className() == "Struct") {
      //   term.ref.push_back(this);
      // }
      if ( ref.size() != 0 ) {
        int refSize = ref.size();
        for(int i = 0; i < refSize ; i++) {
          ref[i]->match(term);
        }
      }
    } // if assignable = true
    else {
      ret = ( _value == term.value());
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
        _value = var.value();
        var._value = value();
      }
      else {
        _value = var.value();
        _assignable = false;
      }
    }
    return ret;
  } // match with Variable


};

#endif
