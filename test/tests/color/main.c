#include "sicgl/color.h"
#include "utils.h"

void setUp(void) {
  // set stuff up here
}

void tearDown(void) {
  // clean stuff up here
}

/**
 * @brief Tests that the expected number of bytes per pixel is returned.
 * This test makes an assumption that the expected number of bytes per pixel is
 * in fact 4. This test is invalid for user-supplied color schemes.
 */
static void test_bytes_per_pixel(void) {
  const size_t expected_bytes_per_pixel = 4;
  TEST_ASSERT_EQUAL_INT(expected_bytes_per_pixel, bytes_per_pixel());
}

/**
 * @brief Tests that color elements are properly assembled and dis-assembled.
 * Assumes a method for packing color channels.
 * This test is invalid for user-supplied color schemes.
 */
static void test_color_channels(void) {
  const color_t red = 0x11;
  const color_t green = 0x22;
  const color_t blue = 0x33;
  const color_t alpha = 0x44;

  const color_t reference =
      (alpha << 24) | (red << 16) | (green << 8) | (blue << 0);

  const color_t constructed = color_from_channels(red, green, blue, alpha);

  TEST_ASSERT_EQUAL(reference, constructed);
  TEST_ASSERT_EQUAL(red, color_channel_red(constructed));
  TEST_ASSERT_EQUAL(green, color_channel_green(constructed));
  TEST_ASSERT_EQUAL(blue, color_channel_blue(constructed));
  TEST_ASSERT_EQUAL(alpha, color_channel_alpha(constructed));
}

/**
 * @brief Tests conversion of color channels to unity doubles.
 * Assumes that 8-bit integer color channels are used.
 * This test is invalid for user-supplied color schemes.
 */
void test_unity_color_channels(void) {
  TEST_ASSERT_FLOAT_WITHIN(0.001f, 0.0f, color_channel_as_unity_double(0));
  TEST_ASSERT_FLOAT_WITHIN(0.001f, 1.0f, color_channel_as_unity_double(255));
}

// not needed when using generate_test_runner.rb
int main(void) {
  UNITY_BEGIN();

  RUN_TEST(test_bytes_per_pixel);
  RUN_TEST(test_color_channels);
  RUN_TEST(test_unity_color_channels);

  return UNITY_END();
}
