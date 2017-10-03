#ifndef UTTERM_H
#define UTTERM_H

#include "number.h"
#include "atom.h"
#include "variable.h"

//test Number.value()
TEST (Number,ctor) {
	Number num_10(10);
	ASSERT_EQ("10", num_10.value());
}

//test Number.symbol()
TEST (Number, symbol) {
	Number num_10(10) ;
	ASSERT_EQ("10", num_10.symbol());
}

//?- 25=25.
//true.
TEST (Number, matchSuccess) {
	Number num_25(25);
	ASSERT_TRUE(num_25.match(num_25));
}

//?- 25=0.
//false.
TEST (Number, matchFailureDiffValue) {
	Number num_25(25);
	Number num_0(0);
	ASSERT_FALSE(num_25.match(num_0));
}

//?- 25=tom.
//false.
TEST (Number, matchFailureDiffConstant) {
	Number num_25(25);
	Atom tom("tom");
	ASSERT_FALSE(num_25.match(tom));
}

//?- 25=X.
//true.
TEST (Number, matchSuccessToVar) {
  Number num_25(25);
  Variable x("X");
  ASSERT_TRUE(num_25.match(x));
}

//?- tom=25.
//false.
TEST (Atom, matchFailureDiffConstant) {
	Atom tom("tom");
	Number num_25(25);
	ASSERT_FALSE(tom.match(num_25));
}

// ?- tom = X.
// X = tom.
TEST (Atom, matchSuccessToVar) {
	Atom tom("tom");
	Variable x("X");
	ASSERT_TRUE( tom.match(x) );
	ASSERT_EQ(tom.value(), x.value());
}

// ?- X=tom, tom=X.
// X = tom.
TEST (Atom, matchSuccessToVarInstantedToDiffConstant) {
	Variable x("X");
	Atom tom("tom");
	ASSERT_TRUE( x.match(tom) );
	ASSERT_TRUE( tom.match(x) );
	ASSERT_EQ(tom.value(), x.value());
}

// ?- X=jerry, tom=X.
// false.
TEST (Atom, matchFailureToVarInstantedToDiffConstant) {
	Variable x("X");
	Atom jerry("jerry");
	Atom tom("tom");
	ASSERT_TRUE( x.match(jerry));
	ASSERT_FALSE( tom.match(jerry));
}

// ?- X = 5.
// X = 5.
TEST (Var, matchSuccessToNumber) {
 	Variable x("X");
 	Number num_5(5);
 	ASSERT_TRUE(x.match(num_5));
 	ASSERT_EQ( x.value() , num_5.value() );
}

// ?- X=25, X= 100.
// false.
TEST (Var, matchFailureToTwoDiffNumbers) {
	Variable x("X");
	Number num_25(25);
	Number num_100(100);
	ASSERT_TRUE( x.match(num_25) );
	ASSERT_FALSE( x.match(num_100) );
	ASSERT_EQ( x.value(), num_25.value() );
}	

// ?- X=tom, X= 25.
// false.
TEST (Var, matchSuccessToAtomThenFailureToNumber) {
	Variable x("X");
	Atom tom("tom");
	Number num_25(25);
	ASSERT_TRUE(x.match(tom));
	ASSERT_FALSE(x.match(num_25));
	ASSERT_EQ(x.value(), tom.value() );
}

//?- tom=X, 25=X.
//false.
TEST (Var, matchSuccessToAtomThenFailureToNumber2) {
	Atom tom("tom");
	Variable x("X");
	Number num_25(25);
	ASSERT_TRUE(tom.match(x));
	ASSERT_FALSE(num_25.match(x));
	ASSERT_EQ(tom.value(), x.value());

}
//?- X=tom, X=tom.
//true.
TEST(Var, reAssignTheSameAtom){
	Variable x("X");
	Atom tom("tom");
	ASSERT_TRUE(x.match(tom));
	ASSERT_TRUE(x.match(tom));
	
}
#endif