#include "sicgl.h"
#include "bitmap_utils.h"
#include "unity.h"

#include<stdio.h>

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
  interface_t interface;
  interface.screenwriter.arg = (void*)bm; // provide bitmap to screenwriter
  interface.screenwriter.pixel = bmp_pixel;
  interface.screenwriter.vline = bmp_vline;
  interface.grid.height = height;
  interface.grid.width = width;

  // draw some pixels
  for (uint32_t count = 0; count < num_pix; count++) {
    uext_t u = rand() % width;
    uext_t v0 = rand() % height;
    uext_t v1 = rand() % height;
    bitmap_pixel_t pixel = bmp_random_color();

    // draw the pixel using the interface
    sicgl_draw_vline(&interface, (void*)&pixel, u, v0, v1);
  }

  // clean up
  bitmap_to_file(bm, "test_vline.png");
  bitmap_free(bm);
}

// not needed when using generate_test_runner.rb
int main(void) {
  UNITY_BEGIN();
  RUN_TEST(test_pixel);
  return UNITY_END();
}
