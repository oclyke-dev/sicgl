#include <stdio.h>

#include "test_utils.h"
#include "sicgl.h"

// expected result from simple location test
const uint8_t pixel_location_expected[9] = {
    0, 0, 0, 0, 0xEA, 0, 0, 0, 0,
};

void setUp(void) {
  // set stuff up here
}

void tearDown(void) {
  // clean stuff up here
}

void test_pixel_location_generic_full(void) {
  // simple test to verify that pixels are placed in the expected location
  bytes_t* bytes = bytes_new(3, 3);
  generic_interface_t* intfc = bytes_new_generic_interface(bytes, true);
  TEST_ASSERT_NOT_NULL_MESSAGE(bytes, "could not allocate bytes object");
  TEST_ASSERT_NOT_NULL_MESSAGE(intfc, "could not allocate interface object");

  // draw a pixel to the location
  sicgl_generic_pixel(intfc, (void*)&pixel_location_expected[4], 1, 1);

  // verify that the location matches
  TEST_ASSERT_EQUAL_MEMORY(pixel_location_expected, bytes->memory,
                           bytes->length);
  bytes_free(bytes);
}

void test_pixel_location_generic_naive(void) {
  // simple test to verify that pixels are placed in the expected location
  bytes_t* bytes = bytes_new(3, 3);
  generic_interface_t* intfc = bytes_new_generic_interface(bytes, false);
  TEST_ASSERT_NOT_NULL_MESSAGE(bytes, "could not allocate bytes object");
  TEST_ASSERT_NOT_NULL_MESSAGE(intfc, "could not allocate interface object");

  // draw a pixel to the location
  sicgl_generic_pixel(intfc, (void*)&pixel_location_expected[4], 1,
                      1);  // intentionally messed up the expected coordinates
                           // (1,1) here... for testing the test

  // verify that the location matches
  TEST_ASSERT_EQUAL_MEMORY(pixel_location_expected, bytes->memory,
                           bytes->length);
  bytes_free(bytes);
}

void test_pixel_location_specific(void) {
  // simple test to verify that pixels are placed in the expected location
  bytes_t* bytes = bytes_new(3, 3);
  TEST_ASSERT_NOT_NULL_MESSAGE(bytes, "could not allocate bytes object");

  specific_interface_t* intfc = bytes_new_specific_interface(bytes);
  screen_t* screen = bytes_new_screen(bytes);
  TEST_ASSERT_NOT_NULL_MESSAGE(intfc, "could not allocate interface object");
  TEST_ASSERT_NOT_NULL_MESSAGE(screen, "could not allocate screen object");

  // draw a pixel to the location
  sicgl_specific_pixel(intfc, screen, (void*)&pixel_location_expected[4], 1, 1);

  // verify that the location matches
  TEST_ASSERT_EQUAL_MEMORY(pixel_location_expected, bytes->memory,
                           bytes->length);
  bytes_free(bytes);
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
  RUN_TEST(test_pixel_location_generic_full);
  RUN_TEST(test_pixel_location_generic_naive);
  RUN_TEST(test_pixel_location_specific);
  RUN_TEST(test_pixel);
  return UNITY_END();
}
