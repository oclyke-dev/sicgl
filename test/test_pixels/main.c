#include <stdio.h>

#include "bitmap_utils.h"
#include "sicgl.h"
#include "unity.h"

void setUp(void) {
  // set stuff up here
}

void tearDown(void) {
  // clean stuff up here
}

void test_pixel(void) {
  const uext_t width = 255;
  const uext_t height = 255;
  bitmap_t* bm = bitmap_new(width, height);
  TEST_ASSERT_NOT_NULL(bm);

  const uint32_t num_pix = 1000;

  // set up the interface
  generic_interface_t interface;
  interface.arg = (void*)bm;  // provide bitmap to screenwriter
  interface.pixel = bmp_pixel;

  // draw some pixels
  for (uint32_t count = 0; count < num_pix; count++) {
    uext_t u = rand() % width;
    uext_t v = rand() % height;
    bitmap_pixel_t pixel = bmp_random_color();

    // limit pixels to be within the region where u <= v
    if (u > v) {
      u = v;
    }

    // draw the pixel using the interface
    sicgl_generic_pixel(&interface, (void*)&pixel, u, v);
  }

  // clean up
  bitmap_to_file(bm, "test_pixels.png");
  bitmap_free(bm);
}

// not needed when using generate_test_runner.rb
int main(void) {
  UNITY_BEGIN();
  RUN_TEST(test_pixel);
  return UNITY_END();
}
