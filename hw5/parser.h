#ifndef PARSER_H
#define PARSER_H
#include <string>
using std::string;

#include "atom.h"
#include "variable.h"
#include "global.h"
#include "scanner.h"
#include "struct.h"
#include "list.h"

class Parser{
public:
  Parser(Scanner scanner) : _scanner(scanner){}
  
  Term* createTerm(){
    int token = _scanner.nextToken();
    if(token == VAR){
      return new Variable(symtable[_scanner.tokenValue()].first);
    }else if(token == NUMBER){
      return new Number(_scanner.tokenValue());
    }else if(token == ATOM){
        Atom* atom = new Atom(symtable[_scanner.tokenValue()].first);
        if(_scanner.currentChar() == '(' ) {
          _currentToken = _scanner.nextToken() ; // get '('
          printf("pos:%d\n",_scanner.position() );
          if(_scanner.currentChar() == ')') {
            return new Struct(*atom);
            // if (terms.size() > 0) return new Struct(*atom, terms);
            // else return new Struct(*atom);
          }
          else { 
            vector<Term*> terms = getArgs();
            return new Struct(*atom, terms);
          }
        }
        else
          return atom;
    } 
    else if ( token == '[') {
      _scanner.skipLeadingWhiteSpace();
      if(_scanner.currentChar() != ']') {
        vector<Term*> args = getArgs();
        // _scanner.skipLeadingWhiteSpace();
        
        if( _currentToken == ']') {
          return new List(args);
        }
        else throw std::string("unexpected token");
      }
      else {
        // current token is ']',  means "[]"
        _scanner.nextToken();
        vector<Term*> args = {};
        return new List(args);
      }
    }
    else if ( token == ATOMSC) {
       Atom* atom = new Atom(symtable[_scanner.tokenValue()].first);
       if(_scanner.currentChar() == '(' ) {
         _scanner.nextToken() ;
         vector<Term*> terms = getArgs();
         if(_currentToken == ')')
           return new Struct(*atom, terms);
         else throw std::string("unexpected token");
       }
       else throw std::string("unexpected token");
    }
    return nullptr;
  }

  vector<Term*> getArgs()
  {
    Term* term = createTerm();
    vector<Term*> args;
    if(term)
      args.push_back(term);
    while((_currentToken = _scanner.nextToken()) == ',') {
      args.push_back(createTerm());
    }
    return args;
  }



private:
  Scanner _scanner;
  int _currentToken;
};
#endif
