#ifndef UTVARIABLE_H
#define UTVARIABLE_H
#include "variable.h"
#include "struct.h"
#include "atom.h"
#include "number.h"
#include <string>
#include <iostream>
using namespace std;

TEST(Variable, constructor)
{
  Variable X("X");
  ASSERT_EQ("X", X.symbol());
}

TEST(Variable, matching)
{
  Atom tom("tom");
  Variable X("X");
  ASSERT_TRUE(X.match(tom));
  ASSERT_TRUE(X.match(tom));
  ASSERT_EQ("tom", X.value());
  // ASSERT_TRUE(tom.match(X));
}

TEST(Variable, haveValue)
{
  Atom tom("tom");
  Atom jerry("jerry");
  Variable X("X");
  ASSERT_TRUE(X.match(tom));
  ASSERT_FALSE(X.match(jerry));
  ASSERT_TRUE(tom.match(X));
  ASSERT_FALSE(jerry.match(X));
}

// ?- X=2.7182.
// X=2.7182
TEST(Variable, numE_to_varX)
{
  Variable X("X");
  Number num(2.7182);
  ASSERT_TRUE(X.match(num));
  ASSERT_EQ("2.7182", X.value());
  // ASSERT_TRUE(num.match(X));
}

// ?- X=Y, X=1.
// Y=1
TEST(Variable, varY_to_varX_and_num1_to_varX)
{
  Variable X("X");
  Variable Y("Y");
  Number num(1);
  ASSERT_TRUE(X.match(Y));
  ASSERT_EQ("Y", X.value());
  
  ASSERT_TRUE(X.match(num));
  ASSERT_EQ("1", Y.value());
}

// ?- X=Y, Y=1.
// X=1
TEST(Variable, varY_to_varX_and_num1_to_varY)
{
  Variable X("X");
  Variable Y("Y");
  Number num(1);
  ASSERT_TRUE(X.match(Y));
  ASSERT_EQ("Y", X.value());
  ASSERT_TRUE(Y.match(num));
  ASSERT_EQ("1", X.value());
}

// ?- X=X, X=1.
// X=1
TEST(Variable, varX_match_varX_and_num1_to_varX)
{
  Variable X("X");
  Number num(1);
  ASSERT_TRUE(X.match(X));
  ASSERT_TRUE(X.match(num));
  ASSERT_EQ("1", X.value());
}

// ?- Y=1, X=Y.
// X=1
TEST(Variable, num1_to_varY_and_varX_match_varY)
{
  Variable X("X");
  Variable Y("Y");
  Number num(1);
  ASSERT_TRUE(Y.match(num));
  ASSERT_TRUE(X.match(Y));
  ASSERT_EQ("1", X.value());
}

// ?- X=Y, Y=Z, Z=1
// X=1, Y=1, Z=1
TEST(Variable, num1_to_varZ_to_varY_to_varX)
{
  Variable X("X");
  Variable Y("Y");
  Variable Z("Z");
  Number num(1);
  ASSERT_TRUE(X.match(Y));
  ASSERT_EQ("Y", X.value());
  ASSERT_TRUE(Y.match(Z));
  ASSERT_TRUE(Z.match(num));
  cout << X.value() << endl;
  cout << Y.value() << endl;
  cout << Z.value() << endl;
  ASSERT_EQ("1", X.value());
  ASSERT_EQ("1", Y.value());
  ASSERT_EQ("1", Z.value());
}

// ?- X=Y, X=Z, Z=1
// X=1, Y=1, Z=1
TEST(Variable, num1_to_varZ_to_varX_and_varY_to_varX)
{
  Variable X("X");
  Variable Y("Y");
  Variable Z("Z");
  Number num(1);
  ASSERT_TRUE(X.match(Y));
  ASSERT_EQ("Y", X.value());
  ASSERT_TRUE(X.match(Z));
  ASSERT_TRUE(Z.match(num));
  ASSERT_EQ("1", X.value());
  ASSERT_EQ("1", Y.value());
  ASSERT_EQ("1", Z.value());
}

// Give there is a Struct s contains Variable X
// And another Variable Y
// When Y matches Struct s
// Then #symbol() of Y should return "Y"
// And #value() of Y should return "s(X)"
TEST(Variable, Struct1)
{
  Variable X("X");
  vector<Term *> v = {&X};
  Struct s(Atom("s"), v);
  Variable Y("Y");
  ASSERT_TRUE(Y.match(s));
  ASSERT_EQ("Y", Y.symbol());
  ASSERT_EQ("s(X)", Y.value());
}

// Give there is a Struct s contains Variable X
// And another Variable Y
// When Y matches Struct s
// And X matches Atom "teddy"
// Then #symbol() of Y should return "Y"
// And #value() of Y should return "s(teddy)"
TEST(Variable, Struct2)
{
  Variable X("X");
  vector<Term *> v = {&X};
  Struct s(Atom("s"), v);
  Variable Y("Y");
  ASSERT_TRUE(Y.match(s)); // Y value = s(X) 
  Atom teddy("teddy");
  ASSERT_TRUE(X.match(teddy));  // X value = teddy s value = s(teddy)
  ASSERT_EQ("Y", Y.symbol());
  // ASSERT_EQ("s(teddy)",Y.value());
}

#endif
