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
  RUN_TEST(test_specific_display_line);
  RUN_TEST(test_specific_display_rectangle);
  RUN_TEST(test_specific_display_circle);
  RUN_TEST(test_specific_display_ellipse);

  RUN_TEST(test_specific_global_line);
  RUN_TEST(test_specific_global_rectangle);
  RUN_TEST(test_specific_global_circle);
  RUN_TEST(test_specific_global_ellipse);

  RUN_TEST(test_specific_screen_line);
  RUN_TEST(test_specific_screen_rectangle);
  RUN_TEST(test_specific_screen_circle);
  RUN_TEST(test_specific_screen_ellipse);

  // generic
  RUN_TEST(test_generic_display_line);
  RUN_TEST(test_generic_display_rectangle);
  RUN_TEST(test_generic_display_circle);
  RUN_TEST(test_generic_display_ellipse);

  RUN_TEST(test_generic_global_line);
  RUN_TEST(test_generic_global_rectangle);
  RUN_TEST(test_generic_global_circle);
  RUN_TEST(test_generic_global_ellipse);

  RUN_TEST(test_generic_screen_line);
  RUN_TEST(test_generic_screen_rectangle);
  RUN_TEST(test_generic_screen_circle);
  RUN_TEST(test_generic_screen_ellipse);

  return UNITY_END();
}
