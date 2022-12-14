#include "TestAdd.h"
#include "CYK.h"


TEST_F(TestAdd, TwoPlusTwo) {
vector<string> rules;
string w;
w = "aa";
rules = {"S AA",
	    "A AAA",
	    "A a",
	    "A '"};
EXPECT_TRUE( CYK(w, rules));

w = "aa";
rules = {"S AAAAAAA",
           "A AAA",
           "A a",
           "A '"};
EXPECT_FALSE(CYK(w, rules));

w = "cbbbbbc";
rules = {"S ABbA",
        "B BB",
        "B b",
        "A C",
        "C c"};
EXPECT_TRUE( CYK(w, rules));

w = "cbbbbc";
rules = {"S ABbA",
        "B BB",
        "B b",
        "A C",
        "C c"};
EXPECT_TRUE( CYK(w, rules));

w = "ccbbbbc";
rules = {"S ABbA",
       "B BB",
       "B b",
       "A C",
       "C c"};
EXPECT_FALSE( CYK(w, rules));

w = "cbacbbbc";
rules = {"S ABbA", //S - c'ba S - cbbbc
       "S SS",
       "B bb",
       "B `",
       "C c",
       "A C",
       "A a"};
EXPECT_TRUE( CYK(w, rules));

w = "'";
rules = {"S A",
         "S SS",
         "B bb",
         "B `",
         "S B``",
         "A `",
         "A a"};
EXPECT_TRUE( CYK(w, rules));

w = "abbb";
rules = {"S A",
          "S SS",
          "B bb",
          "B `",
          "S B``",
          "A `",
          "A a"};
EXPECT_FALSE( CYK(w, rules));

w = "bbbbb";
rules = {"S A",
      "S SS",
      "B bb",
      "B `",
      "S B``",
      "A `",
      "A a"};
EXPECT_FALSE(CYK(w, rules));

w = "bbbb";
rules = {"S A",
      "S SS",
      "B bb",
      "B `",
      "S B``",
      "A `",
      "A B"};
EXPECT_TRUE( CYK(w, rules));

w = "bbb";
rules = {"S A",
      "S SS",
      "B bb",
      "B `",
      "S B``",
      "A `",
      "A B"};
EXPECT_FALSE(CYK(w, rules));

w = "bbabb";
rules = {"S `",
      "S SS",
      "B bb",
      "B `",
      "S B``",
      "A `",
      "B A",
      "A a"};
EXPECT_TRUE( CYK(w, rules));

}
