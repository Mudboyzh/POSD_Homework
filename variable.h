#ifndef VARIABLE_H
#define VARIABLE_H

#include <string>
#include <vector>
#include "atom.h"
#include "list.h"
using std::string;

class Variable: public Term{
public:
  Variable(string s):_symbol(s){ std::cout << "Var:["<< _symbol << "]\n";}
  string _symbol;
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

  bool match( Variable & var ) {
    bool ret = _assignable;
    if (_assignable) {
      if ( var._assignable ){ 
        ref.push_back( &var ); 
        var.ref.push_back(this);
        // 互相紀錄對方
        _value = &var;
        // var._value = this;
      }
      else {
        _value = &var;
        _assignable = false;
      }
      return ret;
    }
    else return _value->value() == var.value() ;
  } // match with Variable

  bool match( List &listA ) {
    bool ret = _assignable ;
    if (_assignable) {
      for (int i = 0; i < listA._elements.size(); i++) {
        if ( listA._elements[i]->symbol() == _symbol ) return false ;
      }
      _value = &listA;
      _assignable = false ;
    }
    return ret ;
  } // match with List

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



};

#endif
