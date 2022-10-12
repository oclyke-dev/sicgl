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

void test_hline(void) {
  const uext_t width = 255;
  const uext_t height = 255;
  bitmap_t* bm = bitmap_new(width, height);
  TEST_ASSERT_NOT_NULL(bm);

  const uint32_t num_pix = 100;

  // set up the interface
  interface_t interface;
  interface.screenwriter.arg = (void*)bm; // provide bitmap to screenwriter
  interface.screenwriter.pixel = bmp_pixel;
  interface.screenwriter.hline = bmp_hline;
  interface.grid.height = height;
  interface.grid.width = width;

  // draw some hlines
  for (uint32_t count = 0; count < num_pix; count++) {
    uext_t u0 = rand() % width;
    uext_t u1 = rand() % width;
    uext_t v = rand() % height;

    bitmap_pixel_t pixel = bmp_random_color();

    // draw the pixel using the interface
    sicgl_draw_hline(&interface, (void*)&pixel, u0, v, u1);
  }

  // clean up
  bitmap_to_file(bm, "test_hline.png");
  bitmap_free(bm);
}

// not needed when using generate_test_runner.rb
int main(void) {
  UNITY_BEGIN();
  RUN_TEST(test_hline);
  return UNITY_END();
}
