#ifndef NODE_H
#define NODE_H

enum Operators
{
  SEMICOLON,
  COMMA,
  EQUALITY,
  TERM
};

class Node
{
public:
  Node(Operators op) : payload(op), term(0), left(0), right(0) {}
  Node(Operators op, Term *t, Node *l, Node *r) : payload(op), term(t), left(l), right(r) {}

  bool evaluate()
  {
    if (payload == EQUALITY)
    {
      return left->term->match(*(right->term));
    }
    else if (payload == COMMA ||payload == SEMICOLON)
    {
      return left->evaluate() && right->evaluate();
    }
    return false;
  }
  Operators payload;
  Term *term;
  Node *left;
  Node *right;
};

#endif