#include <stdio.h>
#include <stdlib.h>

#include "gd.h"
#include "sicgl.h"
#include "spng.h"
#include "test_utils.h"

void setUp(void) {
  // set stuff up here
}

void tearDown(void) {
  // clean stuff up here
}

void test_hline(void) {
  size_t width = 10;
  size_t height = 10;
  int truecolor = truecolor_random_color();

  // create test and reference images
  gdImagePtr ref_im = gdImageCreateTrueColor(width, height);
  gdImagePtr test_im = gdImageCreateTrueColor(width, height);

  // get sicgl interface
  generic_interface_t* generic = new_libgd_generic_interface_full(test_im);
  TEST_ASSERT_NOT_NULL_MESSAGE(
      generic, "could not allocate generic interface object");

  // draw using both sicgl and libgd
  sicgl_generic_hline(generic, &truecolor, 0, 2, width - 1);
  gdImageLine(ref_im, 0, 2, width - 1, 2, truecolor);

  // output both the images
  png_t* ref_png = new_png_from_image(ref_im);
  png_t* test_png = new_png_from_image(test_im);
  TEST_ASSERT_EQUAL_INT(
      0, png_to_file(ref_png, TEST_OUTPUT_DIR "/hline_ref.png"));
  TEST_ASSERT_EQUAL_INT(
      0, png_to_file(test_png, TEST_OUTPUT_DIR "/hline_test.png"));

  // compare the images
  TEST_ASSERT_EQUAL_INT(0, compare_image(ref_im, test_im));
  release_libgd_generic_interface(generic);
  release_png(ref_png);
  release_png(test_png);
}

void test_vline(void) {
  size_t width = 10;
  size_t height = 10;
  int truecolor = truecolor_random_color();

  // create test and reference images
  gdImagePtr ref_im = gdImageCreateTrueColor(width, height);
  gdImagePtr test_im = gdImageCreateTrueColor(width, height);

  // get sicgl interface
  generic_interface_t* generic = new_libgd_generic_interface_full(test_im);
  TEST_ASSERT_NOT_NULL_MESSAGE(
      generic, "could not allocate generic interface object");

  // draw using both sicgl and libgd
  sicgl_generic_vline(generic, &truecolor, 4, 1, height - 2);
  gdImageLine(ref_im, 4, 1, 4, height - 2, truecolor);

  // output both the images
  png_t* ref_png = new_png_from_image(ref_im);
  png_t* test_png = new_png_from_image(test_im);
  TEST_ASSERT_EQUAL_INT(
      0, png_to_file(ref_png, TEST_OUTPUT_DIR "/vline_ref.png"));
  TEST_ASSERT_EQUAL_INT(
      0, png_to_file(test_png, TEST_OUTPUT_DIR "/vline_test.png"));

  // compare the images
  TEST_ASSERT_EQUAL_INT(0, compare_image(ref_im, test_im));
  release_libgd_generic_interface(generic);
  release_png(ref_png);
  release_png(test_png);
}

void test_region(void) {
  size_t width = 10;
  size_t height = 10;
  int truecolor = truecolor_random_color();

  // create test and reference images
  gdImagePtr ref_im = gdImageCreateTrueColor(width, height);
  gdImagePtr test_im = gdImageCreateTrueColor(width, height);

  // get sicgl interface
  generic_interface_t* generic = new_libgd_generic_interface_full(test_im);
  TEST_ASSERT_NOT_NULL_MESSAGE(
      generic, "could not allocate generic interface object");

  // draw using both sicgl and libgd
  sicgl_generic_region(generic, &truecolor, 4, 1, 8, height - 2);
  gdImageFilledRectangle(ref_im, 4, 1, 8, height - 2, truecolor);

  // output both the images
  png_t* ref_png = new_png_from_image(ref_im);
  png_t* test_png = new_png_from_image(ref_im);
  TEST_ASSERT_EQUAL_INT(
      0, png_to_file(ref_png, TEST_OUTPUT_DIR "/region_ref.png"));
  TEST_ASSERT_EQUAL_INT(
      0, png_to_file(test_png, TEST_OUTPUT_DIR "/region_test.png"));

  // compare the images
  TEST_ASSERT_EQUAL_INT(0, compare_image(ref_im, test_im));
  release_libgd_generic_interface(generic);
  release_png(ref_png);
  release_png(test_png);
}

int main() {
  UNITY_BEGIN();
  RUN_TEST(test_hline);
  RUN_TEST(test_vline);
  RUN_TEST(test_region);
  return UNITY_END();
}
