#include "gd.h"
#include "globals.h"
#include "sicgl/screen.h"
#include "tests/alpha.h"
#include "tests/alpha_simple.h"
#include "tests/bitwise.h"
#include "tests/channelwise.h"
#include "tests/direct.h"
#include "utils.h"

// size of canvases for these tests
uext_t width = 255;
uext_t height = 255;

screen_t* screen = NULL;
interface_t* backdrop_interface = NULL;
interface_t* source_interface = NULL;

interface_t* gradient_backdrop_interface = NULL;
interface_t* gradient_source_interface = NULL;

color_t clear = gdTrueColorAlpha(0, 0, 0, gdAlphaTransparent);
color_t canary = gdTrueColorAlpha(255, 255, 0, gdAlphaOpaque);
color_t cyan = gdTrueColorAlpha(0, 255, 255, gdAlphaOpaque);

void setUp(void) {
  // create screen and interfaces to persist the original layers
  screen = new_screen_extent(width, height, 0, 0);
  backdrop_interface = new_libgd_interface(screen, NULL, 0);
  source_interface = new_libgd_interface(screen, NULL, 0);
  gradient_backdrop_interface = new_libgd_interface(screen, NULL, 0);
  gradient_source_interface = new_libgd_interface(screen, NULL, 0);
  TEST_ASSERT_NOT_NULL_MESSAGE(screen, "could not create screen");
  TEST_ASSERT_NOT_NULL_MESSAGE(
      backdrop_interface, "could not create backdrop interface");
  TEST_ASSERT_NOT_NULL_MESSAGE(
      source_interface, "could not create source interface");
  TEST_ASSERT_NOT_NULL_MESSAGE(
      gradient_backdrop_interface, "could not create gradient backdrop interface");
  TEST_ASSERT_NOT_NULL_MESSAGE(
      gradient_source_interface, "could not create gradient source interface");

  // draw rectangles
  sicgl_interface_rectangle_filled(
      backdrop_interface, clear, 0, 0, width - 1, height - 1);
  sicgl_interface_rectangle_filled(
      backdrop_interface, canary, 25, 25, 175, 175);

  sicgl_interface_rectangle_filled(
      source_interface, clear, 0, 0, width - 1, height - 1);
  sicgl_interface_rectangle_filled(source_interface, cyan, 75, 75, 225, 225);

  // draw gradients
  for (ext_t idx = 0; idx < width; idx++) {
    const int alpha = (idx << 23);
    for (ext_t idy = 0; idy < height; idy++) {
        sicgl_interface_line(gradient_backdrop_interface, (alpha & 0xff000000) | 0x00ff0000, 0, idx, width - 1, idx);
        sicgl_interface_line(gradient_source_interface, (alpha & 0xff000000) | 0x000000ff, idx, 0, idx, height - 1);
    }    
  }

  // save the reference pictures
  png_t* backdrop_png = new_png_from_libgd_interface(backdrop_interface);
  png_t* source_png = new_png_from_libgd_interface(source_interface);
  png_t* gradient_backdrop_png = new_png_from_libgd_interface(gradient_backdrop_interface);
  png_t* gradient_source_png = new_png_from_libgd_interface(gradient_source_interface);

  TEST_ASSERT_NOT_NULL_MESSAGE(backdrop_png, "could not create backdrop png");
  TEST_ASSERT_NOT_NULL_MESSAGE(source_png, "could not create source png");

  TEST_ASSERT_EQUAL_INT(
      0, png_to_file(backdrop_png, TEST_OUTPUT_DIR "/_backdrop.png"));
  TEST_ASSERT_EQUAL_INT(
      0, png_to_file(source_png, TEST_OUTPUT_DIR "/_source.png"));
  TEST_ASSERT_EQUAL_INT(
      0, png_to_file(gradient_backdrop_png, TEST_OUTPUT_DIR "/_gradient_backdrop.png"));
  TEST_ASSERT_EQUAL_INT(
      0, png_to_file(gradient_source_png, TEST_OUTPUT_DIR "/_gradient_source.png"));
}

void tearDown(void) {
  // clean stuff up here
  release_screen(screen);
  release_libgd_interface(backdrop_interface);
  release_libgd_interface(source_interface);
}

// not needed when using generate_test_runner.rb
int main(void) {
  UNITY_BEGIN();

  // direct
  RUN_TEST(test_direct_set);
  RUN_TEST(test_direct_clear);
  RUN_TEST(test_direct_none);

  // bitwise
  RUN_TEST(test_bitwise_and);
  RUN_TEST(test_bitwise_or);
  RUN_TEST(test_bitwise_xor);
  RUN_TEST(test_bitwise_nand);
  RUN_TEST(test_bitwise_nor);
  RUN_TEST(test_bitwise_xnor);

  // channelwise
  RUN_TEST(test_channelwise_min);
  RUN_TEST(test_channelwise_max);

  RUN_TEST(test_channelwise_sum);
  RUN_TEST(test_channelwise_diff);
  RUN_TEST(test_channelwise_diff_reverse);
  RUN_TEST(test_channelwise_multiply);
  RUN_TEST(test_channelwise_divide);
  RUN_TEST(test_channelwise_divide_reverse);

  RUN_TEST(test_channelwise_sum_clamped);
  RUN_TEST(test_channelwise_diff_clamped);
  RUN_TEST(test_channelwise_diff_reverse_clamped);
  RUN_TEST(test_channelwise_multiply_clamped);
  RUN_TEST(test_channelwise_divide_clamped);
  RUN_TEST(test_channelwise_divide_reverse_clamped);

  // alpha simple
  RUN_TEST(test_alpha_simple);

  // alpha porter-duff
  RUN_TEST(test_alpha_clear);
  RUN_TEST(test_alpha_copy);
  RUN_TEST(test_alpha_destination);
  RUN_TEST(test_alpha_source_over);
  RUN_TEST(test_alpha_destination_over);
  RUN_TEST(test_alpha_source_in);
  RUN_TEST(test_alpha_destination_in);
  RUN_TEST(test_alpha_source_out);
  RUN_TEST(test_alpha_destination_out);
  RUN_TEST(test_alpha_source_atop);
  RUN_TEST(test_alpha_destination_atop);
  RUN_TEST(test_alpha_xor);
  RUN_TEST(test_alpha_lighter);

  return UNITY_END();
}
