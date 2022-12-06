#include "sicgl/screen.h"
#include "tests.h"
#include "utils.h"

void setUp(void) {
  // set stuff up here
}

void tearDown(void) {
  // clean stuff up here
}

// not needed when using generate_test_runner.rb
int main(void) {
  UNITY_BEGIN();

  RUN_TEST(test_linear_case1);
  RUN_TEST(test_linear_case2);
  RUN_TEST(test_linear_case3);

  RUN_TEST(test_circular_case1);
  RUN_TEST(test_circular_case2);
  RUN_TEST(test_circular_case3);
  RUN_TEST(test_circular_case4);

  return UNITY_END();
}
