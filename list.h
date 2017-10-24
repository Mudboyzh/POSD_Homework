#ifndef LIST_H
#define LIST_H

#include "atom.h"

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
  	for( int i = 0; i < _elements.size(); i++ ) {
  		ret += _elements[i]->value();
  		if ( i != _elements.size()-1 ) ret += ", ";
  	}
  	ret += "]";
  	return ret ;
  }
  bool match(Term & term) {
    if ( term.className() == "Variable" ) {
      List temp(_elements);
      return term.match(temp);
    }

    return  value() == term.value();
  }

  bool match(List & listA) {
    if ( &listA == this ) return true;
    else {
      if ( _elements.size() != listA._elements.size() ) return false;
      else {
        for ( int i = 0; i < _elements.size() ; i++ ) {
          if ( !( _elements[i]->match( *listA._elements[i])) ) return false ; 
        } // for
      } // else

      return true ;
    } // else
  }

  string className() const { return "List" ;}

  int getElementSize() {
    return _elements.size();
  }

  vector<Term *> _elements;
};

#endif