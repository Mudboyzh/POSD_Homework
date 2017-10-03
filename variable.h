#ifndef VARIABLE_H
#define VARIABLE_H

#include <string>
#include "token.h"
using std::string;


class Variable: public Token {
 public:
 	Variable( string s ) {
 		_symbol = s ;
 	}

 	string value() {
 		return _value;
 	}

 	string symbol() {
 		return _symbol;
 	}

 	string className() {
      return _className ;
    }

 	bool match( Token & t ) {
 		// bool ret = isAssignable ;
 		if ( isAssignable ) {
 			_value = t.value();
 			isAssignable = false ;
 			return true ;
 		}
 		else {
 			return this->_value == t.value();
 		}
 	}
 private:
 	string _symbol;
 	string _value;
 	string const _className = "Variable";
 	bool isAssignable = true ;
};

#endif
