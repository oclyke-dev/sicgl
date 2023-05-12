#include "gd.h"
#include "globals.h"
#include "sicgl/screen.h"
#include "tests/alpha.h"
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

png_t* solid_backdrop_png = NULL;
png_t* solid_source_png = NULL;
png_t* gradient_backdrop_png = NULL;
png_t* gradient_source_png = NULL;

/**
 * @brief Create a source images object
 *
 * These images are used to feed the compositor tests.
 *
 * These images are no longer used, to prevent changes
 * in sicgl code from invalidating existing test references.
 */
void create_source_images(void) {
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
      gradient_backdrop_interface,
      "could not create gradient backdrop interface");
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
      sicgl_interface_line(
          gradient_backdrop_interface, (alpha & 0xff000000) | 0x00ff0000, 0,
          idx, width - 1, idx);
      sicgl_interface_line(
          gradient_source_interface, (alpha & 0xff000000) | 0x000000ff, idx, 0,
          idx, height - 1);
    }
  }

  // save the reference pictures
  solid_backdrop_png = new_png_from_libgd_interface(backdrop_interface);
  solid_source_png = new_png_from_libgd_interface(source_interface);
  gradient_backdrop_png =
      new_png_from_libgd_interface(gradient_backdrop_interface);
  gradient_source_png = new_png_from_libgd_interface(gradient_source_interface);

  TEST_ASSERT_NOT_NULL_MESSAGE(
      solid_backdrop_png, "could not create solid backdrop png");
  TEST_ASSERT_NOT_NULL_MESSAGE(
      solid_source_png, "could not create solid source png");
  TEST_ASSERT_NOT_NULL_MESSAGE(
      gradient_backdrop_png, "could not create gradient backdrop png");
  TEST_ASSERT_NOT_NULL_MESSAGE(
      gradient_source_png, "could not create gradient source png");

  TEST_ASSERT_EQUAL_INT_MESSAGE(
      0,
      png_to_file(solid_backdrop_png, TEST_OUTPUT_DIR "/_solid_backdrop.png"),
      "failed to store solid backdrop png");
  TEST_ASSERT_EQUAL_INT_MESSAGE(
      0, png_to_file(solid_source_png, TEST_OUTPUT_DIR "/_solid_source.png"),
      "failed to store solid source png");
  TEST_ASSERT_EQUAL_INT_MESSAGE(
      0,
      png_to_file(
          gradient_backdrop_png, TEST_OUTPUT_DIR "/_gradient_backdrop.png"),
      "failed to store gradient backdrop png");
  TEST_ASSERT_EQUAL_INT_MESSAGE(
      0,
      png_to_file(gradient_source_png, TEST_OUTPUT_DIR "/_gradient_source.png"),
      "failed to store gradient source png");
}

void setUp(void) {
  // create the source images
  // (todo: use the reference images directly to create the interfaces
  // which are used in the test compositions)
  create_source_images();

  // ensure that the reference pictures have not changed
  // (this could happen, for instance, if the sicgl code used to draw the
  // reference pictures has changed)
  png_t* reference_solid_backdrop_png = NULL;
  png_t* reference_solid_source_png = NULL;
  png_t* reference_gradient_backdrop_png = NULL;
  png_t* reference_gradient_source_png = NULL;

  TEST_ASSERT_EQUAL_INT_MESSAGE(
      0,
      png_from_file(
          TEST_SOURCE_DIR "/reference/_solid_backdrop.png",
          &reference_solid_backdrop_png),
      "could not load reference solid backdrop image");
  TEST_ASSERT_EQUAL_INT_MESSAGE(
      0,
      png_from_file(
          TEST_SOURCE_DIR "/reference/_solid_source.png",
          &reference_solid_source_png),
      "could not load reference solid source image");
  TEST_ASSERT_EQUAL_INT_MESSAGE(
      0,
      png_from_file(
          TEST_SOURCE_DIR "/reference/_gradient_backdrop.png",
          &reference_gradient_backdrop_png),
      "could not load reference gradient backdrop image");
  TEST_ASSERT_EQUAL_INT_MESSAGE(
      0,
      png_from_file(
          TEST_SOURCE_DIR "/reference/_gradient_source.png",
          &reference_gradient_source_png),
      "could not load reference gradient source image");

  TEST_ASSERT_EQUAL_INT_MESSAGE(
      0, png_compare(reference_solid_backdrop_png, solid_backdrop_png),
      "solid backdrop images did not match");
  TEST_ASSERT_EQUAL_INT_MESSAGE(
      0, png_compare(reference_solid_source_png, solid_source_png),
      "solid source images did not match");
  TEST_ASSERT_EQUAL_INT_MESSAGE(
      0, png_compare(reference_gradient_backdrop_png, gradient_backdrop_png),
      "gradient backdrop images did not match");
  TEST_ASSERT_EQUAL_INT_MESSAGE(
      0, png_compare(reference_gradient_source_png, gradient_source_png),
      "gradient source images did not match");
}

void tearDown(void) {
  // clean stuff up here
  release_screen(screen);
  release_libgd_interface(backdrop_interface);
  release_libgd_interface(source_interface);
}

void run_solid_tests(void) {
  // direct
  RUN_TEST(test_solid_direct_set);
  RUN_TEST(test_solid_direct_clear);
  RUN_TEST(test_solid_direct_none);

  // bitwise
  RUN_TEST(test_solid_bitwise_and);
  RUN_TEST(test_solid_bitwise_or);
  RUN_TEST(test_solid_bitwise_xor);
  RUN_TEST(test_solid_bitwise_nand);
  RUN_TEST(test_solid_bitwise_nor);
  RUN_TEST(test_solid_bitwise_xnor);

  // channelwise
  RUN_TEST(test_solid_channelwise_min);
  RUN_TEST(test_solid_channelwise_max);

  RUN_TEST(test_solid_channelwise_sum);
  RUN_TEST(test_solid_channelwise_diff);
  RUN_TEST(test_solid_channelwise_diff_reverse);
  RUN_TEST(test_solid_channelwise_multiply);
  RUN_TEST(test_solid_channelwise_divide);
  RUN_TEST(test_solid_channelwise_divide_reverse);

  RUN_TEST(test_solid_channelwise_sum_clamped);
  RUN_TEST(test_solid_channelwise_diff_clamped);
  RUN_TEST(test_solid_channelwise_diff_reverse_clamped);
  RUN_TEST(test_solid_channelwise_multiply_clamped);
  RUN_TEST(test_solid_channelwise_divide_clamped);
  RUN_TEST(test_solid_channelwise_divide_reverse_clamped);

  // alpha porter-duff
  RUN_TEST(test_solid_alpha_clear);
  RUN_TEST(test_solid_alpha_copy);
  RUN_TEST(test_solid_alpha_destination);
  RUN_TEST(test_solid_alpha_source_over);
  RUN_TEST(test_solid_alpha_destination_over);
  RUN_TEST(test_solid_alpha_source_in);
  RUN_TEST(test_solid_alpha_destination_in);
  RUN_TEST(test_solid_alpha_source_out);
  RUN_TEST(test_solid_alpha_destination_out);
  RUN_TEST(test_solid_alpha_source_atop);
  RUN_TEST(test_solid_alpha_destination_atop);
  RUN_TEST(test_solid_alpha_xor);
  RUN_TEST(test_solid_alpha_lighter);
}

void run_gradient_tests(void) {
  // direct
  RUN_TEST(test_gradient_direct_set);
  RUN_TEST(test_gradient_direct_clear);
  RUN_TEST(test_gradient_direct_none);

  // bitwise
  RUN_TEST(test_gradient_bitwise_and);
  RUN_TEST(test_gradient_bitwise_or);
  RUN_TEST(test_gradient_bitwise_xor);
  RUN_TEST(test_gradient_bitwise_nand);
  RUN_TEST(test_gradient_bitwise_nor);
  RUN_TEST(test_gradient_bitwise_xnor);

  // channelwise
  RUN_TEST(test_gradient_channelwise_min);
  RUN_TEST(test_gradient_channelwise_max);

  RUN_TEST(test_gradient_channelwise_sum);
  RUN_TEST(test_gradient_channelwise_diff);
  RUN_TEST(test_gradient_channelwise_diff_reverse);
  RUN_TEST(test_gradient_channelwise_multiply);
  RUN_TEST(test_gradient_channelwise_divide);
  RUN_TEST(test_gradient_channelwise_divide_reverse);

  RUN_TEST(test_gradient_channelwise_sum_clamped);
  RUN_TEST(test_gradient_channelwise_diff_clamped);
  RUN_TEST(test_gradient_channelwise_diff_reverse_clamped);
  RUN_TEST(test_gradient_channelwise_multiply_clamped);
  RUN_TEST(test_gradient_channelwise_divide_clamped);
  RUN_TEST(test_gradient_channelwise_divide_reverse_clamped);

  // alpha porter-duff
  RUN_TEST(test_gradient_alpha_clear);
  RUN_TEST(test_gradient_alpha_copy);
  RUN_TEST(test_gradient_alpha_destination);
  RUN_TEST(test_gradient_alpha_source_over);
  RUN_TEST(test_gradient_alpha_destination_over);
  RUN_TEST(test_gradient_alpha_source_in);
  RUN_TEST(test_gradient_alpha_destination_in);
  RUN_TEST(test_gradient_alpha_source_out);
  RUN_TEST(test_gradient_alpha_destination_out);
  RUN_TEST(test_gradient_alpha_source_atop);
  RUN_TEST(test_gradient_alpha_destination_atop);
  RUN_TEST(test_gradient_alpha_xor);
  RUN_TEST(test_gradient_alpha_lighter);
}

// not needed when using generate_test_runner.rb
int main(void) {
  UNITY_BEGIN();

  run_solid_tests();
  run_gradient_tests();

  return UNITY_END();
}
