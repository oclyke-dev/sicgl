#include "sicgl/display.h"
#include "utils.h"

void setUp(void) {
  // set stuff up here
}

void tearDown(void) {
  // clean stuff up here
}

void test_stand_in(void) {
  TEST_IGNORE_MESSAGE("there are currently no tests for display_t");
}

// not needed when using generate_test_runner.rb
int main(void) {
  UNITY_BEGIN();
  RUN_TEST(test_stand_in);
  return UNITY_END();
}
