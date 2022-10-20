//
// Created by Pavel Akhtyamov on 2019-03-05.
//

#include "TestAdd.h"

TEST_F(TestAdd, TwoPlusTwo) {
  ASSERT_EQ(4, get_max_substring("b*", "bbbb"));
  ASSERT_EQ(2, get_max_substring("bc.", "babcb"));
  ASSERT_EQ(2, get_max_substring("abc.+", "babcc"));
  ASSERT_EQ(3, get_max_substring("abc.+*", "babcc"));

  ASSERT_EQ(1, get_max_substring("bc*+", "babcb"));
  ASSERT_EQ(2, get_max_substring("ab+c.aba.*.bac.+.+*", "babc"));
  ASSERT_EQ(2, get_max_substring("ab.bc.+aba.*.b.+*", "babc"));
  ASSERT_EQ(4, get_max_substring("acb..bab.c. * .ab.ba. + . + *a.", "abbaa"));

}
