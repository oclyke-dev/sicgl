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
  RUN_TEST(test_interface_line);
  RUN_TEST(test_interface_line_case1);
  RUN_TEST(test_interface_line_case2);
  RUN_TEST(test_interface_rectangle);
  RUN_TEST(test_interface_circle_bresenham);
  RUN_TEST(test_interface_circle_ellipse);
  RUN_TEST(test_interface_ellipse);

  RUN_TEST(test_specific_global_line);
  RUN_TEST(test_specific_global_rectangle);
  RUN_TEST(test_specific_global_circle_bresenham);
  RUN_TEST(test_specific_global_circle_ellipse);
  RUN_TEST(test_specific_global_ellipse);

  RUN_TEST(test_specific_screen_line);
  RUN_TEST(test_specific_screen_rectangle);
  RUN_TEST(test_specific_screen_circle_bresenham);
  RUN_TEST(test_specific_screen_circle_ellipse);
  RUN_TEST(test_specific_screen_ellipse);

  return UNITY_END();
}
