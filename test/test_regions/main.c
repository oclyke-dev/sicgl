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

void test_region(void) {
  const uext_t width = 255;
  const uext_t height = 255;

  // set up the interfaces
  // // a fast interface uses the bmp_vline implementation
  bitmap_t* fast_bm = bitmap_new(width, height);
  generic_interface_t fast_intfc = {0};
  fast_intfc.arg = (void*)fast_bm;
  fast_intfc.pixel = bmp_pixel;
  fast_intfc.vline = bmp_vline;

  // // a naive interface only provides the bmp_pixel implementation
  bitmap_t* naive_bm = bitmap_new(width, height);
  generic_interface_t naive_intfc = {0};
  naive_intfc.arg = (void*)naive_bm;
  naive_intfc.pixel = bmp_pixel;

  // create bitmap for specific api
  bitmap_t* spec_bm = bitmap_new(width, height);

  TEST_ASSERT_NOT_NULL(fast_bm);
  TEST_ASSERT_NOT_NULL(naive_bm);
  TEST_ASSERT_NOT_NULL(spec_bm);

  // create specific api:
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

  // draw some lines
  const uint32_t regions = 1;
  // const uint32_t regions = 250;
  for (uint32_t count = 0; count < regions; count++) {
    uext_t u0 = rand() % width;
    uext_t v0 = rand() % height;
    uext_t u1 = rand() % width;
    uext_t v1 = rand() % height;
    bitmap_pixel_t pixel = bmp_random_color();

    u0 = 0;
    v0 = 0;
    u1 = 0;
    v1 = 0;

    // draw the pixel using the interfaces
    sicgl_generic_region(&fast_intfc, (void*)&pixel, u0, v0, u1, v1);
    sicgl_generic_region(&naive_intfc, (void*)&pixel, u0, v0, u1, v1);
    sicgl_specific_region(&specfic_intfc, &spec_screen, (void*)&pixel, u0, v0, u1, v1);
  }

  // store images
  bitmap_to_file(fast_bm, "test_regions_fast.png");
  bitmap_to_file(naive_bm, "test_regions_naive.png");
  bitmap_to_file(spec_bm, "test_regions_specific.png");

  // compare the memory for the two images
  const size_t memory_len = sizeof(bitmap_pixel_t) * width * height;
  TEST_ASSERT_EQUAL_MEMORY(fast_bm->pixels, naive_bm->pixels, memory_len);
  TEST_ASSERT_EQUAL_MEMORY(spec_bm->pixels, naive_bm->pixels, memory_len);

  // clean up
  bitmap_free(fast_bm);
  bitmap_free(naive_bm);
}

// not needed when using generate_test_runner.rb
int main(void) {
  UNITY_BEGIN();
  RUN_TEST(test_region);
  return UNITY_END();
}
