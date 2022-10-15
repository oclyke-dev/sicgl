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
  bitmap_t* spec_bm = bitmap_new(width, height);
  TEST_ASSERT_NOT_NULL(bm);
  TEST_ASSERT_NOT_NULL(spec_bm);

  // set up the interface
  generic_interface_t interface;
  interface.arg = (void*)bm;  // provide bitmap to screenwriter
  interface.pixel = bmp_pixel;

  // create info for specific api:
  specific_interface_t specfic_intfc;
  memset((void*)&specfic_intfc, 0U, sizeof(specific_interface_t));
  specfic_intfc.bpp = sizeof(bitmap_pixel_t);
  specfic_intfc.memory = (void*)spec_bm->pixels;
  specfic_intfc.pixels = spec_bm->num_pix;

  screen_t spec_screen;
  spec_screen.height = height;
  spec_screen.width = width;
  spec_screen.u0 = 0;
  spec_screen.v0 = 0;

  // draw some pixels
  const uint32_t num_pix = 1000;
  for (uint32_t count = 0; count < num_pix; count++) {
    uext_t u = rand() % width;
    uext_t v = rand() % height;
    bitmap_pixel_t pixel = bmp_random_color();

    // limit pixels to be within the region where u <= v
    if (u > v) {
      u = v;
    }

    // draw the pixel using the interface(s)
    sicgl_generic_pixel(&interface, (void*)&pixel, u, v);
    sicgl_specific_pixel(&specfic_intfc, &spec_screen, (void*)&pixel, u, v);
  }

  // store images
  bitmap_to_file(bm, "test_pixels_generic.png");
  bitmap_to_file(spec_bm, "test_pixels_specific.png");

  // compare the memory for the two images
  const size_t memory_len = sizeof(bitmap_pixel_t) * width * height;
  TEST_ASSERT_EQUAL_MEMORY(bm->pixels, spec_bm->pixels, memory_len);

  // clean up
  bitmap_free(bm);
  bitmap_free(spec_bm);
}

// not needed when using generate_test_runner.rb
int main(void) {
  UNITY_BEGIN();
  RUN_TEST(test_pixel);
  return UNITY_END();
}
