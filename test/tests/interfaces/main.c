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

  // specific
  RUN_TEST(test_specific_pixel);
  RUN_TEST(test_specific_hline);
  RUN_TEST(test_specific_vline);
  RUN_TEST(test_specific_region);

  return UNITY_END();
}
