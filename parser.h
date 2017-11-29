#ifndef PARSER_H
#define PARSER_H
#include <string>
#include <stack>
using std::stack;
using std::string;

#include "atom.h"
#include "variable.h"
#include "global.h"
#include "scanner.h"
#include "struct.h"
#include "list.h"
#include "node.h"
#include "utParser.h"

class Parser
{
public:
  Parser(Scanner scanner) : _scanner(scanner), _terms() {}

  void matchings()
  {
    while (_scanner.currentChar() != '.')
    {
      Term *term = createTerm();
      if (term != nullptr)
      {
        _terms.push_back(term);
        Node *n = new Node(TERM, term, nullptr, nullptr);
        op_term.push(n);
      }
      switch(_scanner.currentChar())
      {
        case '=': {
                    Node *n = new Node(EQUALITY);
                    op_op.push(n);
                    break;
                  }
        case ',': {
                    Node *n ;
                    while(op_op.size() > 0 && op_op.top()->payload != COMMA && op_op.top()->payload != SEMICOLON ) {
                      n = makeTree();
                      op_term.push(n);
                    }
                    n = new Node(COMMA);
                    op_op.push(n);
                    break;
                  }
        case ';': {
                    Node *n;
                    while(op_op.size() > 0 && op_op.top()->payload != SEMICOLON ) {
                      n = makeTree();
                      op_term.push(n);
                    }
                    _allTermsTable.push_back(_tempTermsTable);
                    _tempTermsTable.clear();
                    n = new Node(SEMICOLON);
                    op_op.push(n);
                    break;
                  }       
        default:  break;
      }
    }

    Node *temp;
    while (op_op.size() > 0)
    {
      temp = makeTree();
      op_term.push(temp);
      tree = temp;
    }
  }

  Node *expressionTree()
  {
    return tree;
  }

  
  Node *makeTree()
  {
    Node *n = op_op.top();
    op_op.pop();
    n->right = op_term.top();
    op_term.pop();
    n->left = op_term.top();
    op_term.pop();
    return n;
  }

  Term * checkIfTermExist( string symbol ) 
  {
    for( int i = 0; i < _tempTermsTable.size(); i++ ) 
    {
         if( symbol == _tempTermsTable[i]->symbol() ) return _tempTermsTable[i]; 
    }
    return nullptr;
  }

  Term *createTerm()
  {
    int token = _scanner.nextToken();
    _currentToken = token;
    if (token == VAR)
    {
      Term * temp = checkIfTermExist(symtable[_scanner.tokenValue()].first) ;
      if ( temp != nullptr ) return temp;
      else  {
        temp = new Variable(symtable[_scanner.tokenValue()].first);
        _tempTermsTable.push_back(temp);
        return temp;
      }
    }
    else if (token == NUMBER)
    {
      return new Number(_scanner.tokenValue());
    }
    else if (token == ATOM || token == ATOMSC)
    {
      Atom *atom = new Atom(symtable[_scanner.tokenValue()].first);
      if (_scanner.currentChar() == '(')
      {
        return structure();
      }
      else
        return atom;
    }
    else if (token == '[')
    {
      return list();
    }

    return nullptr;
  }

  Term *structure()
  {
    Atom structName = Atom(symtable[_scanner.tokenValue()].first);
    int startIndexOfStructArgs = _terms.size();
    _scanner.nextToken();
    createTerms();
    if (_currentToken == ')')
    {
      vector<Term *> args(_terms.begin() + startIndexOfStructArgs, _terms.end());
      _terms.erase(_terms.begin() + startIndexOfStructArgs, _terms.end());
      return new Struct(structName, args);
    }
    else
    {
      throw string("unexpected token");
    }
  }

  Term *list()
  {
    int startIndexOfListArgs = _terms.size();
    createTerms();
    if (_currentToken == ']')
    {
      vector<Term *> args(_terms.begin() + startIndexOfListArgs, _terms.end());
      _terms.erase(_terms.begin() + startIndexOfListArgs, _terms.end());
      return new List(args);
    }
    else
    {
      throw string("unexpected token");
    }
  }

  vector<Term *> &getTerms()
  {
    return _terms;
  }

private:
  FRIEND_TEST(ParserTest, createArgs);
  FRIEND_TEST(ParserTest, ListOfTermsEmpty);
  FRIEND_TEST(ParserTest, listofTermsTwoNumber);
  FRIEND_TEST(ParserTest, createTerm_nestedStruct3);

  void createTerms()
  {
    Term *term = createTerm();
    if (term != nullptr)
    {
      if ( checkIfTermExist(term->symbol()) == nullptr ) _terms.push_back(term);
      else _terms.push_back(checkIfTermExist(term->symbol()));
      while ((_currentToken = _scanner.nextToken()) == ',')
      {
          term = createTerm(); 
          if ( checkIfTermExist(term->symbol()) == nullptr ) _terms.push_back(term);
          else _terms.push_back(checkIfTermExist(term->symbol()));
      }
    }
  }

  vector<Term *> _terms;
  vector<Term *> _tempTermsTable;
  vector< vector<Term *> > _allTermsTable;
  int scope = 0;
  Scanner _scanner;
  int _currentToken;
  Node *tree;
  stack<Node *> op_term;
  stack<Node *> op_op;
};
#endif
