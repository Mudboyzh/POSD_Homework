#ifndef PARSER_H
#define PARSER_H
#include <string>
using std::string;

#include <gtest/gtest.h>
#include "atom.h"
#include "variable.h"
#include "global.h"
#include "scanner.h"
#include "struct.h"
#include "list.h"
#include "exp.h"
#include <stack>
#include <vector>

using std::stack;

class Parser{
public:
  Parser(Scanner scanner) : _scanner(scanner), _terms() {}

  Term* createTerm(){
    int token = _scanner.nextToken();
    _currentToken = token;
    if(token == VAR){
      for (int i = 0; i < _variableTable.size(); i++) {
        if ( symtable[_scanner.tokenValue()].first == _variableTable[i]->symbol())
          return _variableTable[i];
      }
      
      Variable *var = new Variable(symtable[_scanner.tokenValue()].first);
      _variableTable.push_back(var);
      return var;
    }else if(token == NUMBER){
      return new Number(_scanner.tokenValue());
    }else if(token == ATOM || token == ATOMSC){
      Atom* atom = new Atom(symtable[_scanner.tokenValue()].first);
      if(_scanner.currentChar() == '(' ) {
        return structure();
      }
      else
        return atom;
    }
    else if(token == '['){
      return list();
    }

    return nullptr;
  }



  Term * structure() {
    Atom structName = Atom(symtable[_scanner.tokenValue()].first);
    int startIndexOfStructArgs = _terms.size();
    _scanner.nextToken();
    createTerms();
    if(_currentToken == ')')
    {
      vector<Term *> args(_terms.begin() + startIndexOfStructArgs, _terms.end());
      _terms.erase(_terms.begin() + startIndexOfStructArgs, _terms.end());
      return new Struct(structName, args);
    } else {
      throw string("Unbalanced operator");
    }
  }

  Term * list() {
    int startIndexOfListArgs = _terms.size();
    createTerms();
    if(_currentToken == ']')
    {
      vector<Term *> args(_terms.begin() + startIndexOfListArgs, _terms.end());
      _terms.erase(_terms.begin() + startIndexOfListArgs, _terms.end());
      if(args.size()==0){
        return new Atom("[]");
      }
      return new List(args);
    } else {
      throw string("Unbalanced operator");
    }
  }

  vector<Term *> & getTerms() {
    return _terms;
  }


  void buildExpression(){
    // createTerm();
    disjunctionMatch();
    restDisjunctionMatch();
    Term * temp = createTerm();

    if ( temp != nullptr || _currentToken != '.') {
      throw string("Missing token '.'");
    }
  }

  void restDisjunctionMatch() {
    // std::cout << "!!!current: " << _scanner.currentChar() << "\n" ;
    if (_scanner.currentChar() == ';') {
      _variableTable.clear();
      createTerm();
      _scanner.peekNextToken();
      if (_scanner.tokenValue() == NONE )
        throw string ( "Unexpected ';' before '.'");
      // createTerm();
      disjunctionMatch();
      Exp *right = _expStack.top();
      _expStack.pop();
      Exp *left = _expStack.top();
      _expStack.pop();
      _expStack.push(new DisjExp(left, right));
      restDisjunctionMatch();
    }
  }

  void disjunctionMatch() {
    conjunctionMatch();
    restConjunctionMatch();
  }

  void restConjunctionMatch() {
    if (_scanner.currentChar() == ',') {
      createTerm();
      _scanner.peekNextToken();
      if (_scanner.tokenValue() == NONE )
        throw string ( "Unexpected ',' before '.'");
      conjunctionMatch();
      Exp *right = _expStack.top();
      _expStack.pop();
      Exp *left = _expStack.top();
      _expStack.pop();
      _expStack.push(new ConjExp(left, right));
      restConjunctionMatch();
    }
  }

  void conjunctionMatch() {
    Term * left = createTerm();
    if (createTerm() == nullptr && _currentToken == '=') {
      Term * right = createTerm();
      
      _expStack.push(new MatchExp(left, right));
    }
    else if ( _currentToken == '.' )  
      throw string( left->symbol() + " does never get assignment");
    else if ( _currentToken == ';' || _currentToken == ',' )
      throw string( "Unexpected '" + string(1, _currentToken) + "' before '" +  _scanner.currentChar()+"'");
    // std::cout << "!~~!curr:" << _currentToken << "\n";
  }

  Exp* getExpressionTree(){
    return _expStack.top();
  }

  string result() {
    return getExpressionTree()->getResult() + ".";
  }

private:
  FRIEND_TEST(ParserTest, createArgs);
  FRIEND_TEST(ParserTest,ListOfTermsEmpty);
  FRIEND_TEST(ParserTest,listofTermsTwoNumber);
  FRIEND_TEST(ParserTest, createTerm_nestedStruct3);
  FRIEND_TEST(ParserTest, createTerms);

  void createTerms() {
    Term* term = createTerm();
    if(term!=nullptr)
    {
      _terms.push_back(term);
      while((_currentToken = _scanner.nextToken()) == ',') {
        _terms.push_back(createTerm());
      }
    }
  }

  vector<Term *> _terms;
  Scanner _scanner;
  int _currentToken;
  stack<Exp*> _expStack;
  vector<Variable *> _variableTable;
};
#endif
