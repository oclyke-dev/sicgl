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

  // generic full display
  RUN_TEST(test_generic_full_pixel);
  RUN_TEST(test_generic_full_hline);
  RUN_TEST(test_generic_full_vline);
  RUN_TEST(test_generic_full_region);

  // generic naive display
  RUN_TEST(test_generic_naive_pixel);
  RUN_TEST(test_generic_naive_hline);
  RUN_TEST(test_generic_naive_vline);
  RUN_TEST(test_generic_naive_region);

  return UNITY_END();
}
