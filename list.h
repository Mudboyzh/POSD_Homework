#ifndef LIST_H
#define LIST_H

#include "atom.h"

#include <vector>
using std::vector;

class List : public Term {
public:
  List () {

  }
  List (vector<Term *> const & elements):_elements(elements){}

  static bool elementsSort( const Term * first, const Term * second ) {
  	return first->value() < second->value();
  }

  Term * head() const {
    if ( _elements.size() == 0 )  throw "Accessing head in an empty list";
    return _elements[0] ;
  }

  List * tail() const {
    List * new_List = new List();
    if ( _elements.size() == 0 ) throw "Accessing tail in an empty list";

    new_List->_elements.assign(_elements.begin()+1,_elements.end());
    return new_List ;
  }

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
      return term.match(*this);
    }

    return  value() == term.value();
  }

  bool match(List & listA) {
    std::cout << "List Match List\n" ;
    if ( &listA == this ) {
      std::cout << "List Case 1\n";
      return true;
    }
    else {
      if ( _elements.size() != listA._elements.size() ) {
        std::cout << "List Case 2\n";
        return false;
      }
      else {
        std::cout << "List Case 3\n";
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