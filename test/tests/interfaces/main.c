#include "sicgl/screen.h"
#include "utils.h"

#include "tests.h"

void setUp(void) {
  // set stuff up here
}

void tearDown(void) {
  // clean stuff up here
}

// not needed when using generate_test_runner.rb
int main(void) {
  UNITY_BEGIN();

	// specific display tests
  RUN_TEST(test_specific_display_pixel);
  RUN_TEST(test_specific_display_hline);
  RUN_TEST(test_specific_display_vline);
	RUN_TEST(test_specific_display_region);

  return UNITY_END();
}
