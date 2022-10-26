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

  // specific display
  RUN_TEST(test_specific_display_pixel);
  RUN_TEST(test_specific_display_hline);
  RUN_TEST(test_specific_display_vline);
  RUN_TEST(test_specific_display_region);

  // specific screen
  RUN_TEST(test_specific_screen_pixel);
  RUN_TEST(test_specific_screen_hline);
  RUN_TEST(test_specific_screen_vline);
  RUN_TEST(test_specific_screen_region);

  // generic full display
  RUN_TEST(test_generic_full_display_pixel);
  RUN_TEST(test_generic_full_display_hline);
  RUN_TEST(test_generic_full_display_vline);
  RUN_TEST(test_generic_full_display_region);

  // generic full screen
  RUN_TEST(test_generic_full_screen_pixel);
  RUN_TEST(test_generic_full_screen_hline);
  RUN_TEST(test_generic_full_screen_vline);
  RUN_TEST(test_generic_full_screen_region);

  // generic naive display
  RUN_TEST(test_generic_naive_display_pixel);
  RUN_TEST(test_generic_naive_display_hline);
  RUN_TEST(test_generic_naive_display_vline);
  RUN_TEST(test_generic_naive_display_region);

  // generic naive screen
  RUN_TEST(test_generic_naive_screen_pixel);
  RUN_TEST(test_generic_naive_screen_hline);
  RUN_TEST(test_generic_naive_screen_vline);
  RUN_TEST(test_generic_naive_screen_region);

  return UNITY_END();
}
