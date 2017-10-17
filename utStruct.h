#include <vector>
#include "atom.h"
#include "struct.h"
#include "variable.h" 
#include "number.h"
TEST(Struct, hobby)
{
  Atom tom("tom");
  Atom chaseMouse("chaseMouse");
  std::vector<Term *> v = {&tom, &chaseMouse};
  Struct hobby(Atom("hobby"), v);
  ASSERT_EQ("hobby", hobby.name().symbol());
  ASSERT_EQ("tom", hobby.args(0)->symbol());
  ASSERT_EQ("chaseMouse", hobby.args(1)->symbol());

}

TEST(Struct,symbol)
{
  Atom tom("tom");
  Atom chaseMouse("chaseMouse");
  std::vector<Term *> v = {&tom, &chaseMouse};
  Struct hobby(Atom("hobby"), v);
  ASSERT_EQ("hobby(tom, chaseMouse)",hobby.symbol());
}

TEST(Struct,match1)
{
  Atom tom("tom");
  Atom chaseMouse("chaseMouse");
  std::vector<Term *> v = {&tom, &chaseMouse};
  Struct hobby(Atom("hobby"), v);
  Struct hobby2(Atom("hobby2"), v);
  EXPECT_FALSE(hobby.match(hobby2));
}
TEST(Struct,match2){
  Atom tom("tom");
  Atom chaseMouse("chaseMouse");
  std::vector<Term *> v = {&tom, &chaseMouse};
  Struct hobby(Atom("hobby"), v);
  std::vector<Term *> v1 = {&tom};
  Struct hobby2(Atom("hobby"), v1);
  EXPECT_FALSE(hobby.match(hobby2));
}
TEST(Struct,match3){
  Atom tom("tom");
  Atom chaseMouse("chaseMouse");
  std::vector<Term *> v = {&tom, &chaseMouse};
  Struct hobby(Atom("hobby"), v);
  std::vector<Term *> v1 = { &chaseMouse,&tom};
  Struct hobby2(Atom("hobby"), v1);
  EXPECT_FALSE(hobby.match(hobby2));
}
TEST(Struct,match4)
{
  Atom tom("tom");
  Atom chaseMouse("chaseMouse");
  std::vector<Term *> v = {&tom, &chaseMouse};
  Struct hobby(Atom("hobby"), v);
  Struct hobby2(Atom("hobby"), v);
  EXPECT_TRUE(hobby.match(hobby2));
}
TEST(Struct,match5)
{
  Atom tom("tom");
  Atom chaseMouse("chaseMouse");
  std::vector<Term *> v = {&tom, &chaseMouse};
  Struct hobby(Atom("hobby"), v);
  EXPECT_FALSE(hobby.match(tom));
}


// When Struct s contains a Variable X
// Then #symbol() should return "s(X)"
// and #value() should also return "s(X)"
TEST(Struct, var)
{
  Variable x("X");
  std::vector<Term *> v = {&x};
  Struct s(Atom("s"), v);
  // std::cout << "Symbol(): "<< s.symbol() << std::endl;
  // std::cout << "Value(): "<< s.symbol() << std::endl;
  ASSERT_EQ("s(X)", s.symbol());
  ASSERT_EQ("s(X)", s.value());
}

// Given there is Struct s contains a Variable X
// When Variable X matches an Atom "tom"
// Then #symbol() should return "s(X)"
// and #value() should also return "s(tom)"
TEST(Struct, var_match_atom)
{
  Variable x("X");
  Atom tom("tom");
  x.match(tom);
  std::vector<Term *> v = {&x};
  ASSERT_EQ("tom", x.value());
  Struct s(Atom("s"),v);
  ASSERT_EQ("s(X)", s.symbol());
  ASSERT_EQ("s(tom)", s.value());

}

// Given there are Struct s1 and Struct s2
// When Struct s1 contains Struct s2
// And Struct s2 contains a Variable X
// Then #symbol() of s1 should return "s1(s2(X))"
// and #value() of s1 should also return "s1(s2(X))"
TEST(Struct, nested_struct1)
{
  Variable x("X");
  std::vector<Term *> v2 = {&x};
  Struct s2(Atom("s2"), v2) ;
  std::vector<Term *> v1 = {&s2};
  Struct s1(Atom("s1"), v1);
  ASSERT_EQ("s1(s2(X))", s1.symbol());
  ASSERT_EQ("s1(s2(X))", s1.value());

}

// Given there are Struct s1 contains Struct s2
// And Struct s2 contains Variable X
// When Variable X matches an Atom "tom"
// Then #symbol() of s1 should return "s1(s2(X))"
// and #value() of s1 should return "s1(s2(tom))"
TEST(Struct, nested_struct2)
{
  Variable x("X");
  Atom tom("tom");
  x.match(tom);
  std::vector<Term *> v2 = {&x};
  Struct s2(Atom("s2"), v2) ;
  std::vector<Term *> v1 = {&s2};
  Struct s1(Atom("s1"), v1);
  ASSERT_EQ("s1(s2(X))", s1.symbol());
  ASSERT_EQ("s1(s2(tom))", s1.value());
}

// Given there are Struct s1 contains Struct s2
// And Struct s2 contains Variable X
// When Variable X matches an Number pi: 3.14
// Then #symbol() of s1 should return "s1(s2(X))"
// and #value() of s1 should return "s1(s2(3.14))"
TEST(Struct, nested_struct3)
{
  Variable x("X");
  Number pi(3.14);
  x.match(pi);
  std::vector<Term *> v2 = {&x};
  Struct s2(Atom("s2"), v2) ;
  std::vector<Term *> v1 = {&s2};
  Struct s1(Atom("s1"), v1);
  ASSERT_EQ("s1(s2(X))", s1.symbol());
  ASSERT_EQ("s1(s2(3.14))", s1.value());
}

// Given there are Struct s1 contains Struct s2 and Variable X
// And Struct s2 contains Variable Y
// When Variable X matches Variable Y
// And Variable X matches Atom "kent_beck"
// Then #symbol() of s1 should return "s1(s2(Y), X)"
// and #value() of s1 should return "s1(s2(kent_beck), kent_beck)"
TEST(Struct, nested_struct_and_multiVariable)
{
   Variable x("X");
   Variable y("Y");
   Atom kent_beck("kent_beck");
   std::vector<Term *> v2 = {&y};
   x.match(y);
   y.match(kent_beck);
   Struct s2(Atom("s2"), v2) ;
   std::vector<Term *> v1 = {&s2,&x};
   Struct s1(Atom("s1"), v1);
   ASSERT_EQ("s1(s2(Y), X)", s1.symbol());
   ASSERT_EQ("s1(s2(kent_beck), kent_beck)", s1.value());
}
