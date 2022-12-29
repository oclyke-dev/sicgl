#include <math.h>
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

  ext_t u0 = 1;
  ext_t v0 = 1;
  ext_t u1 = 5;
  ext_t v1 = 6;

  // draw the line simultaneously
  simultaneous_line(
      &reference, &image, width, height, screen, u0, v0, u1, v1, color);
  TEST_ASSERT_NOT_NULL(reference);
  TEST_ASSERT_NOT_NULL(image);

  // compare the images
  int compare_status = compare_image(reference, image);

  // save the images
  png_t* ref_png = new_png_from_image(reference);
  png_t* test_png = new_png_from_image(image);
  int output_status_ref =
      png_to_file(ref_png, TEST_OUTPUT_DIR "/reference.png");
  int output_status_test = png_to_file(test_png, TEST_OUTPUT_DIR "/test.png");
  release_png(ref_png);
  release_png(test_png);

  // make assertions
  TEST_ASSERT_EQUAL_INT(0, compare_status);
  TEST_ASSERT_EQUAL_INT(0, output_status_ref);
  TEST_ASSERT_EQUAL_INT(0, output_status_test);
}

void test_rising_sun(void) {
  int ret = 0;
  size_t width = 255;
  size_t height = 255;

  const size_t buffer_length = width * sizeof(int);
  uint8_t buffer[buffer_length];

  screen_t* display = new_screen(width, height, 0, 0);
  interface_t* specific =
      new_libgd_specific_interface(display, buffer, buffer_length);

  screen_t* screen = new_screen(width, height, -127, -127);
  int color = truecolor_random_color();

  uext_t r = 100;
  size_t spokes = 56;
  for (size_t idx = 0; idx < spokes; idx++) {
    ext_t u, v;
    double theta = ((double)idx / (spokes)) * 2 * M_PI;
    u = r * sin(theta);
    v = r * cos(theta);

    sicgl_line(specific, screen, &color, 0, 0, u, v);
  }

  // compare the images
  gdImage* image = new_image_from_libgd_specific_interface(specific);
  TEST_ASSERT_NOT_NULL(image);

  // save the images
  png_t* png = new_png_from_image(image);
  int out_status = png_to_file(png, TEST_OUTPUT_DIR "/spokes.png");
  release_png(png);

  // make assertions
  TEST_ASSERT_EQUAL_INT(0, out_status);
}

void test_bounding(void) {
  int ret = 0;
  int color;
  size_t width = 41;
  size_t height = 41;

  const size_t buffer_length = width * sizeof(int);
  uint8_t buffer[buffer_length];

  screen_t* display = new_screen(width, height, 0, 0);
  interface_t* specific =
      new_libgd_specific_interface(display, buffer, buffer_length);
  screen_t* bounds = new_screen(20, 20, 10, 10);

  // draw bounds
  color = truecolor_random_color();
  sicgl_line(specific, bounds, &color, -10, -10, 10, -10);
  sicgl_line(specific, bounds, &color, 10, -10, 10, 10);
  sicgl_line(specific, bounds, &color, 10, 10, -10, 10);
  sicgl_line(specific, bounds, &color, -10, 10, -10, -10);

  // // draw lines to various locations
  // color = truecolor_random_color();
  // sicgl_line(specific, bounds, &color, -19, -10, 0, 0);
  // sicgl_line(specific, bounds, &color, 10, -10, 10, 10);
  // sicgl_line(specific, bounds, &color, 10, 10, -10, 10);
  // sicgl_line(specific, bounds, &color, -10, 10, -10, -10);

  // uext_t r = 100;
  // size_t spokes = 23;
  // for (size_t idx = 0; idx < spokes; idx++) {
  //   ext_t u, v;
  //   double theta = ((double)idx / (spokes)) * 2 * M_PI;
  //   u = r * sin(theta);
  //   v = r * cos(theta);

  //   printf("(%d, %d)\n", u, v);

  //   sicgl_line(specific, screen, &color, 0, 0, u, v);
  // }

  // compare the images
  gdImage* image = new_image_from_libgd_specific_interface(specific);
  TEST_ASSERT_NOT_NULL(image);

  // save the images
  png_t* png = new_png_from_image(image);
  int out_status = png_to_file(png, TEST_OUTPUT_DIR "/bounds.png");
  release_png(png);

  // make assertions
  TEST_ASSERT_EQUAL_INT(0, out_status);
}

int main() {
  UNITY_BEGIN();
  RUN_TEST(test_line);
  // RUN_TEST(test_rising_sun);
  RUN_TEST(test_bounding);
  return UNITY_END();
}
