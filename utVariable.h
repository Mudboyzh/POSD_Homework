#ifndef UTVARIABLE_H
#define UTVARIABLE_H
#include "variable.h"
#include "number.h"
#include "struct.h"
#include "atom.h"
TEST(Variable, constructor){
  Variable X("X");
  ASSERT_EQ("X", X._symbol);
}

TEST(Variable , matching){
  Atom tom("tom");
  Atom jerry("jerry");
  Variable X("X");
  ASSERT_TRUE(X.match(tom));
  ASSERT_TRUE(X.match(tom));
  ASSERT_EQ( "tom", X.value());
}
TEST (Variable , haveValue){
  Atom tom ("tom");
  Atom jerry ("jerry");
  Variable X("X");
  ASSERT_TRUE(X.match(tom));
  ASSERT_FALSE(X.match(jerry));
}

// ?- X=2.7182.
// X=2.7182
TEST(Variable , numE_to_varX){
  Number num(2.7182);
  Variable x("X");
  ASSERT_TRUE(x.match(num));
  ASSERT_EQ("2.7182", x.value());
  ASSERT_EQ("2.7182", num.symbol());
  ASSERT_EQ("2.7182", num.value());
  ASSERT_TRUE(x.match(num));
  ASSERT_TRUE(num.match(x));
  ASSERT_TRUE(x.match(x));
  ASSERT_TRUE(num.match(num));
}

// ?- X=Y, X=1
// Y=1
TEST (Variable, varY_to_varX_and_num1_to_varX) {
  Number num1(1);
  Variable x("X");
  Variable y("Y");
  x.match(y);
  x.match(num1);
  ASSERT_EQ("1", y.value());
}
  
// ?- X=Y, Y=1.
// X=1
TEST (Variable, varY_to_varX_and_num1_to_varY) {
  Number num1(1);
  Variable x("X");
  Variable y("Y");
  x.match(y);
  ASSERT_EQ("Y",x.value());
  y.match(num1);
  ASSERT_EQ("1", x.value());
}

// ?- X=X, X=1.
// X=1
TEST (Variable, varX_match_varX_and_num1_to_varX) {
  Number num1(1);
  Variable x("X");
  x.match(x);
  x.match(num1);
  ASSERT_EQ("1", x.value());
}

// ?- Y=1, X=Y.
// X=1
TEST (Variable, num1_to_varY_and_varX_match_varY) {
  Number num1(1);
  Variable x("X");
  Variable y("Y");
  y.match(num1);
  x.match(y);
  ASSERT_EQ("1", x.value());
}

// ?- X=Y, Y=Z, Z=1
// X=1, Y=1, Z=1
TEST (Variable, num1_to_varZ_to_varY_to_varX) {
  Number num1(1);
  Variable x("X");
  Variable y("Y");
  Variable z("Z");
  x.match(y);
  y.match(z);
  z.match(num1);
  EXPECT_EQ("1", x.value());
  EXPECT_EQ("1", y.value());
  EXPECT_EQ("1", z.value());
}

// ?- X=Y, X=Z, Z=1
// X=1, Y=1, Z=1
TEST (Variable, num1_to_varZ_to_varX_and_varY_to_varX) {
  Number num1(1);
  Variable x("X");
  Variable y("Y");
  Variable z("Z");
  x.match(y);
  x.match(z);
  z.match(num1);
  EXPECT_EQ("1", x.value());
  EXPECT_EQ("1", y.value());
  EXPECT_EQ("1", z.value());
}

// Give there is a Struct s contains Variable X
// And another Variable Y
// When Y matches Struct s
// Then #symbol() of Y should return "Y"
// And #value() of Y should return "s(X)"
TEST (Variable, Struct1) {
  Variable x("X");
  Variable y("Y");
  std::vector<Term *> v = {&x};
  Struct s(Atom("s"), v);
  y.match(s);
  ASSERT_EQ("Y", y.symbol());
  ASSERT_EQ("s(X)", y.value());
}

// Give there is a Struct s contains Variable X
// And another Variable Y
// When Y matches Struct s
// And X matches Atom "teddy"
// Then #symbol() of Y should return "Y"
// And #value() of Y should return "s(teddy)"
TEST (Variable, Struct2) {
  Variable x("X");
  Variable y("Y");
  Atom teddy("teddy");
  std::vector<Term *> v = {&x};
  Struct s(Atom("s"), v);
  y.match(s);
  x.match(teddy);
  // y.match(s);
  ASSERT_EQ("teddy",x.value());
  ASSERT_EQ("Y", y.symbol());
  ASSERT_EQ("s(teddy)", y.value());
}


#endif
