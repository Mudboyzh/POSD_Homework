#ifndef UTTERM_H
#define UTTERM_H

#include "number.h"
#include "atom.h"
#include "variable.h"
#include <string>
#include <iostream>
using namespace std;
//test Number.value()
TEST(Number, ctor)
{
    Number num(1314);
    ASSERT_EQ("1314", num.value());
}

//test Number.symbol()
TEST(Number, symbol)
{
    Number num(520);
    ASSERT_EQ("520", num.symbol());
}

//?- 25=25.
//true.
TEST(Number, matchSuccess)
{
    Number num1(25);
    Number num2(25);
    ASSERT_TRUE(num1.match(num2));
}

//?- 25=0.
//false.
TEST(Number, matchFailureDiffValue)
{
    Number num1(25);
    Number num2(0);
    ASSERT_FALSE(num1.match(num2));
}
//?- 25=tom.
//false.
TEST(Number, matchFailureDiffConstant)
{
    Number num(25);
    Atom atom("tom");
    ASSERT_FALSE(num.match(atom));
}

//?- 25=X.
//true.
TEST(Number, matchSuccessToVar)
{
    Number num(25);
    Variable var("X");
    ASSERT_TRUE(num.match(var));
}

//?- tom=25.
//false.
TEST(Atom, matchFailureDiffConstant)
{
    Atom atom("tom");
    Number num(25);
    ASSERT_FALSE(atom.match(num));
}

// ?- tom = X.
// X = tom.
TEST(Atom, matchSuccessToVar)
{
    Atom atom("tom");
    Variable var("X");
    ASSERT_TRUE(atom.match(var));
}

// ?- X=tom, tom=X.
// X = tom.
TEST(Atom, matchSuccessToVarInstantedToDiffConstant)
{
    Variable var("X");
    Atom atom("tom");
    ASSERT_TRUE(var.match(atom));
    ASSERT_TRUE(atom.match(var));
}

// ?- X=jerry, tom=X.
// false.
TEST(Atom, matchFailureToVarInstantedToDiffConstant)
{
    Variable var("X");
    Atom atom("jerry");
    Atom atom1("tom");
    ASSERT_TRUE(var.match(atom));
    ASSERT_FALSE(atom1.match(var));
}

// ?- X = 5.
// X = 5.
TEST(Var, matchSuccessToNumber)
{
    Variable var("X");
    Number num(5);
    ASSERT_TRUE(var.match(num));
}

// ?- X=25, X= 100.
// false.
TEST(Var, matchFailureToTwoDiffNumbers)
{
    Variable var("X");
    Number num(25);
    Number num1(100);
    ASSERT_TRUE(var.match(num));
    ASSERT_FALSE(var.match(num1));
}

// ?- X=tom, X= 25.
// false.
TEST(Var, matchSuccessToAtomThenFailureToNumber)
{
    Variable var("X");
    Atom atom("tom");
    Number num(25);
    ASSERT_TRUE(var.match(atom));
    ASSERT_FALSE(var.match(num));
}

//?- tom=X, 25=X.
//false.
TEST(Var, matchSuccessToAtomThenFailureToNumber2)
{
    Atom atom("tom");
    Variable var("X");
    Number num(25);
    ASSERT_TRUE(atom.match(var));
    ASSERT_FALSE(num.match(var));
}

//?- X=tom, X=tom.
//true.
TEST(Var, reAssignTheSameAtom)
{
    Variable var("X");
    Atom atom("tom");
    ASSERT_TRUE(var.match(atom));
    ASSERT_TRUE(var.match(atom));
}

#endif
