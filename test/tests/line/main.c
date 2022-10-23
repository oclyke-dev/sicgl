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

void test_line(void) {
  int ret = 0;
  size_t width = 10;
  size_t height = 10;
  gdImage* reference = NULL;
  gdImage* image = NULL;
  int color = truecolor_random_color();
  screen_t* screen = new_screen(width, height, 0, 0);

  ext_t u0 = 0;
  ext_t v0 = 0;
  ext_t u1 = 5;
  ext_t v1 = 6;

  // draw the line simultaneously
  simultaneous_line(&reference, &image, width, height, screen, u0, v0, u1, v1, color);
  TEST_ASSERT_NOT_NULL(reference);
  TEST_ASSERT_NOT_NULL(image);

  // compare the images
  int compare_status = compare_image(reference, image);

  // save the images
  png_t* ref_png = new_png_from_image(reference);
  png_t* test_png = new_png_from_image(image);
  int output_status_ref = png_to_file(ref_png, TEST_OUTPUT_DIR "/reference.png");
  int output_status_test = png_to_file(test_png, TEST_OUTPUT_DIR "/test.png");
  release_png(ref_png);
  release_png(test_png);

  // make assertions
  TEST_ASSERT_EQUAL_INT(0, compare_status);
  TEST_ASSERT_EQUAL_INT(0, output_status_ref);
  TEST_ASSERT_EQUAL_INT(0, output_status_test);
}

int main() {
  UNITY_BEGIN();
  RUN_TEST(test_line);
  return UNITY_END();
}
