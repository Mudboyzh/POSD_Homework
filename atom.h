#ifndef ATOM_H
#define ATOM_H

#include <string>
#include "token.h"

using std::string;

class Atom: public Token {
  public:
  	Atom(string s) {
  		_value = s ;
  		_symbol = s ;
  	}

  	string value() {
  		return _value ;
  	}

  	string symbol() {
  		return _symbol;
  	}

  	string className() {
      	return _className ;
    }


  	bool match( Token &t ) {
  		string tokenType = t.className();
      	if ( tokenType == "Variable" ) {
        Atom temp(this->_value); // temp equal this object
        	return t.match( temp );
      	}
    	return this->value() == t.value();
  	}

  private:
  	string _symbol;
  	string const _className = "Atom";
  	string _value;
};

#endif
