#ifndef LIST_H
#define LIST_H

#include "term.h"

#include <vector>
using std::vector;

class List : public Term {
public:
  List () {

  }
  List (vector<Term *> const & elements):_elements(elements){
  	// std::sort(_elements.begin(), _elements.end(), elementsSort);
  }

  static bool elementsSort( const Term * first, const Term * second ) {
  	return first->value() < second->value();
  }

  Term * head() const;
  List * tail() const;

  string symbol() const {
  	string ret = "[" ;
  	for( int i = 0; i < _elements.size(); i++ ) {
  		ret += _elements[i]->symbol();
  		if ( i != _elements.size()-1 ) ret += ", ";
  	}
  	ret += "]";
  	return ret ;
  }

  string value() const {
  	string ret = "[" ;
  	std::cout << "\nyeee1\n";
  	for( int i = 0; i < _elements.size(); i++ ) {
  		std::cout << "element's value: " << _elements[i]->value() << std::endl;
  		ret += _elements[i]->value();
  		if ( i != _elements.size()-1 ) ret += ", ";
  	}
  	std::cout << "\nyeee2\n";
  	ret += "]";
  	return ret ;
  }
  bool match(Term & term){}
  string className() const { return "List" ;};



private:
  vector<Term *> _elements;

};

#endif