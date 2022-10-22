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
  sicgl_generic_hline(generic, (void*)truecolor, 0, 2, width - 1);
  gdImageLine(ref_im, 0, 2, width - 1, 2, truecolor);

  // output both the images
  TEST_ASSERT_EQUAL_INT(
      0, image_to_file(ref_im, TEST_OUTPUT_DIR "/hline_ref.png"));
  TEST_ASSERT_EQUAL_INT(
      0, image_to_file(test_im, TEST_OUTPUT_DIR "/hline_test.png"));

  // compare the images
  TEST_ASSERT_EQUAL_INT(0, compare_image(ref_im, test_im));
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
  sicgl_generic_vline(generic, (void*)truecolor, 4, 1, height - 2);
  gdImageLine(ref_im, 4, 1, 4, height - 2, truecolor);

  // output both the images
  TEST_ASSERT_EQUAL_INT(
      0, image_to_file(ref_im, TEST_OUTPUT_DIR "/vline_ref.png"));
  TEST_ASSERT_EQUAL_INT(
      0, image_to_file(test_im, TEST_OUTPUT_DIR "/vline_test.png"));

  // compare the images
  TEST_ASSERT_EQUAL_INT(0, compare_image(ref_im, test_im));
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
  sicgl_generic_region(generic, (void*)truecolor, 4, 1, 8, height - 2);
  gdImageFilledRectangle(ref_im, 4, 1, 8, height - 2, truecolor);

  // output both the images
  TEST_ASSERT_EQUAL_INT(
      0, image_to_file(ref_im, TEST_OUTPUT_DIR "/region_ref.png"));
  TEST_ASSERT_EQUAL_INT(
      0, image_to_file(test_im, TEST_OUTPUT_DIR "/region_test.png"));

  // compare the images
  TEST_ASSERT_EQUAL_INT(0, compare_image(ref_im, test_im));
}

int main() {
  UNITY_BEGIN();
  RUN_TEST(test_hline);
  RUN_TEST(test_vline);
  RUN_TEST(test_region);
  return UNITY_END();
}
