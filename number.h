#ifndef NUMBER_H
#define NUMBER_H

#include <string>
#include "atom.h"
using std::string;

class Number: public Term {
  public:
    Number(double num):_value(num) {
      _symbol = std::to_string(num) ;
      if ( _symbol.find(".") != string::npos ) {
        for(int i = _symbol.length()-1; i > 0; i-- ) {
          // remove tail zero or dot. example: 2.0, 2.12000
          if (_symbol[i] == '0' ) _symbol.pop_back();
          else {
            if ( _symbol[i] == '.') _symbol.pop_back();
            break;
          }
        } // for
      }
      std::cout << "Number: [" << _symbol << "] \n" ;
    }

    string symbol() const{
      return _symbol;
    }

    string className() const{
      return "Number" ;
    }

    bool match( Term &term ) {
      if ( term.className() == "Variable" ) {
        Number temp(_value);
        return term.match(temp);
      }

      return  value() == term.value();
    } 
  private:
    string _symbol;
    double _value;
};

#endif
