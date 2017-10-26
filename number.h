#ifndef NUMBER_H
#define NUMBER_H

#include <string>
#include <sstream>
#include "atom.h"
using std::string;

class Number: public Term {
  public:
    Number(double num):_value(num) {
      std::cout << "Number before process :[" << num<< "]\n";
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
      std::cout << "Number after process:[" << _symbol<< "]\n";
    }

    string symbol() const{
      return _symbol;
    }

    string className() const{
      return "Number" ;
    }

    bool match( Term &term ) {
      if ( term.className() == "Variable" ) {
        return term.match(*this);
      }

      return  value() == term.value();
    } 
  private:
    string _symbol;
    double _value;
};

#endif
