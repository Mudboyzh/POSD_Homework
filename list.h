#ifndef LIST_H
#define LIST_H

#include "atom.h"

#include <vector>
#include <typeinfo>
using std::vector;

class List : public Term {
public:
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
  bool match(List & listA) {
    if ( &listA == this) return true;
    else {
      if (_elements.size() != listA._elements.size()) return false;
      else {
        for(int i = 0; i < _elements.size(); i++) {
          if( !_elements[i]->match(*listA._elements[i])) return false ;
        } // for
      } // else
    } // else
    return true ;
  }

public:
  List (): _elements() {}
  List (vector<Term *> const & elements):_elements(elements){}
  Term * head() const{
    if ( _elements.size() == 0 )  throw "Accessing head in an empty list";
    return _elements[0] ;
  }
  List * tail() const {
    if ( _elements.size() == 0 ) throw "Accessing tail in an empty list";
    vector<Term *> v;
    v.assign(_elements.begin()+1,_elements.end());
    return new List(v) ;
  }

private:
  vector<Term *> _elements;

};

#endif