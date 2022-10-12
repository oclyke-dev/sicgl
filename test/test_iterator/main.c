#include <stdio.h>

#include "sicgl.h"
#include "unity.h"

// fwd declarations
void test_iterator_bare_range(void);
void test_iterator_range(void);

void setUp(void) {
  // set stuff up here
}

void tearDown(void) {
  // clean stuff up here
}

// not needed when using generate_test_runner.rb
int main(void) {
  UNITY_BEGIN();
  RUN_TEST(test_iterator_bare_range);
  RUN_TEST(test_iterator_range);
  return UNITY_END();
}
