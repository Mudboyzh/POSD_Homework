#ifndef NUMBER_H
#define NUMBER_H

#include <string>
#include "token.h"
using std::string;

class Number: public Token {
  public:
    Number(int num) {
      _symbol = std::to_string(num);
      _value = num;
    }

    string value() {
      return std::to_string( _value);
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
        Number temp(this->_value); // temp equal this object
        return t.match( temp );
      }

      return  this->value() == t.value();
    } 
  private:
    string const _className = "Number" ;
    string _symbol;
    int _value;

};

#endif
