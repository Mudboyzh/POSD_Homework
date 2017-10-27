#ifndef UTLIST_H
#define UTLIST_H

#include <string>
#include <vector>
using std::string;

#include "list.h"
#include "struct.h"
#include "atom.h"
#include "number.h"
#include "variable.h"

// When create a new list without any item
// Then #symbol() of the list should return "[]"
TEST (List, constructor) {
  List listA;
  ASSERT_EQ("[]", listA.symbol() );
}

// Given there are two perfect Numbers: 8128, 496
// When create a new list with the perfect Number
// Then #symbol() of the list should return "[496, 8128]"
TEST(List, Numbers) {
  Number num1(8128), num2(496);
  vector<Term *> args = {&num2, &num1};
  List listA(args);
  ASSERT_EQ("[496, 8128]", listA.symbol());
}

// Given there are two atoms: "terence_tao", "alan_mathison_turing"
// When create a new list with the Atoms
// Then #symbol() of the list should return "[terence_tao, alan_mathison_turing]"
TEST(List, Atoms) {
  Atom t("terence_tao"), a("alan_mathison_turing");
  vector<Term *> args = {&t, &a};
  List listA(args);
  ASSERT_EQ("[terence_tao, alan_mathison_turing]", listA.symbol());
}

// Given there are two variables: X, Y
// When create a new list with the variables
// Then #symbol() of the list should return "[X, Y]"
TEST(List, Vars) {
  Variable x("X"), y("Y");
  vector<Term *> args = {&x, &y};
  List listA(args);
  ASSERT_EQ("[X, Y]", listA.symbol());
}

// ?- tom = [496, X, terence_tao].
// false.
TEST(List, matchToAtomShouldFail) {
  Atom tom("tom"), ter("terence_tao");
  Number num496(496);
  Variable x("X");
  std::vector<Term *> args = {&num496, &x, &ter};
  List listA(args);
  ASSERT_FALSE(tom.match(listA));
}

// ?- 8128 = [496, X, terence_tao].
// false.
TEST(List, matchToNumberShouldFail) {
  Atom ter("terence_tao");
  Number num8128(8128), num496(496);
  Variable x("X");
  ASSERT_EQ("X", x.value());
  std::vector<Term *> args = {&num496, &x, &ter};
  List listA(args);
  ASSERT_EQ("[496, X, terence_tao]", listA.value());
  ASSERT_FALSE(num8128.match(listA));
}

// ?- s(X) = [496, X, terence_tao].
// false.
TEST(List, matchToStructShouldFail) {
  Variable x("X");
  std::vector<Term *> v2 = {&x};
  Struct s(Atom("s"), v2) ;
  ASSERT_EQ("s(X)", s.value());

  Atom ter("terence_tao");
  Number num496(496);
  std::vector<Term *> args = {&num496, &x, &ter};
  List listA(args);

  ASSERT_FALSE(s.match(listA));
}

// ?- Y = [496, X, terence_tao].
// Y = [496, X, terence_tao].
TEST(List, matchToVarShouldSucceed) {
  Atom ter("terence_tao");
  Number num496(496);
  Variable x("X"), y("Y");
  std::vector<Term *> args = {&num496, &x, &ter};
  List listA(args);

  ASSERT_TRUE( y.match(listA));
  ASSERT_EQ("[496, X, terence_tao]", y.value());

}

// ?- X = [496, X, terence_tao].
// false.
TEST(List, matchToVarOccuredInListShouldFail) {
  Variable x("X");
  Atom ter("terence_tao");
  Number num496(496);
  std::vector<Term *> args = {&num496, &x, &ter};
  List listA(args);
  ASSERT_FALSE( x.match(listA));
}

// ?- [496, X, terence_tao] = [496, X, terence_tao].
// true.
TEST(List, matchToSameListShouldSucceed) {
  Variable x("X");
  ASSERT_EQ("X", x.symbol());
  ASSERT_EQ("X", x.value());

  Atom ter("terence_tao");
  ASSERT_EQ("terence_tao", ter.symbol());
  ASSERT_EQ("terence_tao", ter.value());

  Number num496(496);
  ASSERT_EQ("496", num496.symbol());
  ASSERT_EQ("496", num496.value());

  std::vector<Term *> args = {&num496, &x, &ter};
  List listA(args);
  ASSERT_EQ("[496, X, terence_tao]", listA.value());
  x.match(num496);
  ASSERT_EQ("[496, X, terence_tao]", listA.symbol());
  ASSERT_EQ("[496, 496, terence_tao]", listA.value());
  ASSERT_TRUE(listA.match(listA));

  // List listC;
  // ASSERT_TRUE(listC.match(listC));
}

// ?- [496, X, terence_tao] = [496, Y, terence_tao].
// true.
TEST(List, matchToSameListWithDiffVarNameShouldSucceed) {
  Variable x("X"), y("Y");
  Atom ter("terence_tao");
  Number num496(496);
  std::vector<Term *> argsA = {&num496, &x, &ter};
  std::vector<Term *> argsB = {&num496, &y, &ter};
  List listA(argsA);
  List listB(argsB);
  ASSERT_TRUE(listA.match(listB));
  ASSERT_EQ("Y", x.value());
}

// ?- [496, X, terence_tao] = [496, 8128, terence_tao].
// X = 8128.
TEST(List, matchToVarToAtominListShouldSucceed) {
  Variable x("X");
  Atom ter("terence_tao");
  Number num496(496), num8128(8128);
  std::vector<Term *> argsA = {&num496, &x, &ter};
  std::vector<Term *> argsB = {&num496, &num8128, &ter};
  List listA(argsA);
  List listB(argsB);
  ASSERT_TRUE(listA.match(listB));
  ASSERT_EQ("8128", x.value());

}

// ?- Y = [496, X, terence_tao], X = alan_mathison_turing.
// Y = [496, alan_mathison_turing, terence_tao],
// X = alan_mathison_turing.
TEST(List, matchVarinListToAtomShouldSucceed) {
  Variable x("X"), y("Y");
  Atom ter("terence_tao"), alan("alan_mathison_turing");
  Number num496(496);
  std::vector<Term *> args = {&num496, &x, &ter};
  List listA(args);
  ASSERT_TRUE(y.match(listA));
  ASSERT_TRUE(x.match(alan));
  ASSERT_EQ("[496, alan_mathison_turing, terence_tao]", y.value());
  ASSERT_EQ("alan_mathison_turing", x.value());
}

// Example: 
// ?- [first, second, third] = [H|T].
// H = first, T = [second, third].
TEST(List, headAndTailMatching1) {
  Atom f("first"), s("second"), t("third");
  vector<Term *> args = {&f, &s, &t};
  List l(args);

  EXPECT_EQ(string("first"), l.head()->symbol());
  EXPECT_EQ(string("[second, third]"), l.tail()->value());
}

// Example:
// ?- [first, second, third] = [first, H|T].
// H = second, T = [third].
TEST(List, headAndTailMatching2) {
  Atom f("first"), s("second"), t("third");
  vector<Term *> args = {&f, &s, &t};
  List l(args);

  EXPECT_EQ(string("second"), l.tail()->head()->value());
  EXPECT_EQ(string("[third]"), l.tail()->tail()->value());
}

// ?- [[first], second, third] = [H|T].
// H = [first], T = [second, third].
TEST(List, headAndTailMatching3) {
  Atom f("first"), s("second"), t("third");
  vector<Term *> v = {&f};
  List listA(v);
  vector<Term *> args = { &listA, &s, &t};
  List listB(args);

  ASSERT_EQ(string("[first]"), listB.head()->value());
  ASSERT_EQ(string("[second, third]"), listB.tail()->value());

}

// ?- [first, second, third] = [first, second, H|T].
// H = third, T = [].
TEST(List, headAndTailMatching4) {
  Atom f("first"), s("second"), t("third");
  vector<Term *> args = {&f, &s, &t};
  List l(args);

  EXPECT_EQ(string("third"), l.tail()->tail()->head()->value());
  EXPECT_EQ(string("[]"), l.tail()->tail()->tail()->value());
}
 
// Given there is a empty list
// When client still want to get the head of list
// Then it should throw a string: "Accessing head in an empty list" as an exception.
TEST (List, emptyExecptionOfHead) {
  List listEmpty;
  try {
    listEmpty.head()->value();
  }
  catch (const char* errorMsg){
    ASSERT_EQ("Accessing head in an empty list", errorMsg);
  }
}

// Given there is a empty list
// When client still want to get the head of list
// Then it should throw a string: "Accessing tail in an empty list" as an exception.
TEST (List, emptyExecptionOfTail) {
  List listEmpty;
  try {
    listEmpty.tail()->value();
  }
  catch (const char* errorMsg){
    ASSERT_EQ("Accessing tail in an empty list", errorMsg);
  }
}




#endif