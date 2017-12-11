#ifndef UTITERATOR_H
#define UTITERATOR_H

#include "struct.h"
#include "variable.h"
#include "atom.h"
#include "number.h"
#include "list.h"
#include "iterator.h"
#include <iostream>
using namespace std;
//s(1, t(x, 2), Y)
TEST(iterator, first)
{
  Number one(1);
  Variable X("X");
  Variable Y("Y");
  Number two(2);
  Struct t(Atom("t"), {&X, &two});
  Struct s(Atom("s"), {&one, &t, &Y});
  // StructIterator it(&s);
  Iterator<Term *> *itStruct = s.createIterator();
  // Iterator& itStruct = it;
  // ASSERT_EQ(it.first()->symbol());
  itStruct->first();
  ASSERT_EQ("1", itStruct->currentItem()->symbol());
  ASSERT_FALSE(itStruct->isDone());
  itStruct->next();
  ASSERT_EQ("t(X, 2)", itStruct->currentItem()->symbol());
  ASSERT_FALSE(itStruct->isDone());
  itStruct->next();
  ASSERT_EQ("Y", itStruct->currentItem()->symbol());
  itStruct->next();
  ASSERT_TRUE(itStruct->isDone());
}

TEST(iterator, nested_iterator)
{
  // Number one(1);
  // Variable X("X");
  // Variable Y("Y");
  // Number two(2);
  // Struct t(Atom("t"), { &X, &two });
  // Struct s(Atom("s"), { &one, &t, &Y });
  // StructIterator it(&s);
  // it.first();
  // it.next();
  // Struct *s2 = dynamic_cast<Struct *>(it.currentItem());

  // StructIterator it2(s2);
  // it2.first();
  // ASSERT_EQ("X", it2.currentItem()->symbol());
  // ASSERT_FALSE(it2.isDone());
  // it2.next();
  // ASSERT_EQ("2", it2.currentItem()->symbol());
  // ASSERT_FALSE(it2.isDone());
  // it2.next();
  // ASSERT_TRUE(it2.isDone());
}

TEST(iterator, firstList)
{
  Number one(1);
  Variable X("X");
  Variable Y("Y");
  Number two(2);
  Struct t(Atom("t"), {&X, &two});
  List l({&one, &t, &Y});
  ListIterator<Term *> it(&l);
  Iterator<Term *> *itList = &it;
  itList->first();
  ASSERT_EQ("1", itList->currentItem()->symbol());
  ASSERT_FALSE(itList->isDone());
  itList->next();
  ASSERT_EQ("t(X, 2)", itList->currentItem()->symbol());
  ASSERT_FALSE(itList->isDone());
  itList->next();
  ASSERT_EQ("Y", itList->currentItem()->symbol());
  itList->next();
  ASSERT_TRUE(itList->isDone());
}

TEST(iterator, NullIterator)
{
  Number one(1);
  NullIterator<Term *> nullIterator(&one);
  nullIterator.first();
  ASSERT_TRUE(nullIterator.isDone());
  Iterator<Term *> *it = one.createIterator();
  it->first();
  ASSERT_TRUE(it->isDone());
}

TEST(iterator, StructBFSIterator)
{
//          s(t2(t(x, 2), 1), t(x, 2), Y)
//             /            |      \
//    t2(t(x, 2), 1)    t(x, 2)        Y
//        /       \     /   \ 
//    t(x, 2)       1   x       2
//     /    \
//     x      2

  Number one(1);
  Variable X("X");
  Variable Y("Y");
  Number two(2);
  Struct t(Atom("t"), {&X, &two});    // t(x, 2)
  Struct t2(Atom("t2"), {&t, &one});  // t2(t(x, 2), 1)
  Struct s(Atom("s"), {&t2, &t, &Y}); // s(t2(t(x, 2), 1), t(x, 2), Y)
  Iterator<Term *> *it = s.createBFSIterator();
  it->first();
  ASSERT_EQ("t2(t(X, 2), 1)", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("t(X, 2)", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("Y", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("t(X, 2)", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("1", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("X", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("2", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("X", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("2", it->currentItem()->symbol());
  it->next();
  ASSERT_TRUE(it->isDone());
}

TEST(iterator, ListBFSIterator)
{
//     [[1, X], [[1, X], 2], Y]
//     /            |         \
//   [1, X]    [[1, X], 2]      Y
//   /   \         /     \     
//  1    X     [1, X]     2
//               /  \
//             1   X
  Number one(1);
  Variable X("X");
  Variable Y("Y");
  Number two(2);
  vector<Term *> Var = {&one, &X}; 
  List list(Var); // [1, X]
  vector<Term *> Var1 = {&list, &two}; 
  List list1(Var1); // [[1, X], 2]
  vector<Term *> Var2 = {&list, &list1, &Y};
  List list2(Var2); // [[1, X], [[1, X], 2], Y]

  Iterator<Term *> *it = list2.createBFSIterator();
  it->first();
  ASSERT_EQ("[1, X]", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("[[1, X], 2]", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("Y", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("1", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("X", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("[1, X]", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("2", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("1", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("X", it->currentItem()->symbol());
  it->next();
  ASSERT_TRUE(it->isDone());
}

TEST(iterator, StructDFSIterator)
{
//          s(t2(t(x, 2), 1), t(x, 2), Y)
//             /            |      \
//    t2(t(x, 2), 1)    t(x, 2)        Y
//        /       \     /   \ 
//    t(x, 2)       1   x       2
//     /    \
//     x      2

  Number one(1);
  Variable X("X");
  Variable Y("Y");
  Number two(2);
  Struct t(Atom("t"), {&X, &two});    // t(x, 2)
  Struct t2(Atom("t2"), {&t, &one});  // t2(t(x, 2), 1)
  Struct s(Atom("s"), {&t2, &t, &Y}); // s(t2(t(x, 2), 1), t(x, 2), Y)
  Iterator<Term *> *it = s.createDFSIterator();
  it->first();
  ASSERT_EQ("t2(t(X, 2), 1)", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("t(X, 2)", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("X", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("2", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("1", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("t(X, 2)", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("X", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("2", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("Y", it->currentItem()->symbol());
  it->next();
  ASSERT_TRUE(it->isDone());
}

TEST(iterator, ListDFSIterator)
{
//     [[1, X], [[1, X], 2], Y]
//     /            |         \
//   [1, X]    [[1, X], 2]      Y
//   /   \         /     \     
//  1    X     [1, X]     2
//               /  \
//             1   X
  Number one(1);
  Variable X("X");
  Variable Y("Y");
  Number two(2);
  vector<Term *> Var = {&one, &X}; 
  List list(Var); // [1, X]
  vector<Term *> Var1 = {&list, &two}; 
  List list1(Var1); // [[1, X], 2]
  vector<Term *> Var2 = {&list, &list1, &Y};
  List list2(Var2); // [[1, X], [[1, X], 2], Y]

  Iterator<Term *> *it = list2.createDFSIterator();
  it->first();
  ASSERT_EQ("[1, X]", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("1", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("X", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("[[1, X], 2]", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("[1, X]", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("1", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("X", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("2", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("Y", it->currentItem()->symbol());
  it->next();
  ASSERT_TRUE(it->isDone());
}

#endif
