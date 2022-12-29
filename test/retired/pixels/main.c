#include <stdio.h>

#include "sicgl.h"
#include "test_utils.h"

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
  bytes_t* bytes = new_bytes(3, 3);
  generic_interface_t* intfc = new_bytes_generic_interface_full(bytes);
  TEST_ASSERT_NOT_NULL_MESSAGE(bytes, "could not allocate bytes object");
  TEST_ASSERT_NOT_NULL_MESSAGE(intfc, "could not allocate interface object");

  // draw a pixel to the location
  generic_pixel(intfc, (void*)&pixel_location_expected[4], 1, 1);

  // verify that the location matches
  TEST_ASSERT_EQUAL_MEMORY(
      pixel_location_expected, bytes->memory, bytes_length_bytes(bytes));
  release_bytes_generic_interface(intfc);
  release_bytes(bytes);
}

void test_pixel_location_generic_naive(void) {
  // simple test to verify that pixels are placed in the expected location
  bytes_t* bytes = new_bytes(3, 3);
  generic_interface_t prototype = {
      .pixel = (void*)true,
  };
  generic_interface_t* intfc =
      new_bytes_generic_interface_partial(bytes, prototype);
  TEST_ASSERT_NOT_NULL_MESSAGE(bytes, "could not allocate bytes object");
  TEST_ASSERT_NOT_NULL_MESSAGE(intfc, "could not allocate interface object");

  // draw a pixel to the location
  generic_pixel(
      intfc, (void*)&pixel_location_expected[4], 1,
      1);  // intentionally messed up the expected coordinates
           // (1,1) here... for testing the test

  // verify that the location matches
  TEST_ASSERT_EQUAL_MEMORY(
      pixel_location_expected, bytes->memory, bytes_length_bytes(bytes));
  release_bytes_generic_interface(intfc);
  release_bytes(bytes);
}

void test_pixel_location_specific(void) {
  // simple test to verify that pixels are placed in the expected location
  bytes_t* bytes = new_bytes(3, 3);
  TEST_ASSERT_NOT_NULL_MESSAGE(bytes, "could not allocate bytes object");

  screen_t* screen = new_screen(bytes->width, bytes->height, 0, 0);
  TEST_ASSERT_NOT_NULL_MESSAGE(screen, "could not allocate screen object");

  interface_t* intfc =
      new_bytes_specific_interface(bytes, screen, NULL, 0);
  TEST_ASSERT_NOT_NULL_MESSAGE(intfc, "could not allocate interface object");

  // draw a pixel to the location
  sicgl_specific_pixel(intfc, (void*)&pixel_location_expected[4], 1, 1);

  // verify that the location matches
  TEST_ASSERT_EQUAL_MEMORY(
      pixel_location_expected, bytes->memory, bytes_length_bytes(bytes));
  release_bytes_specific_interface(intfc);
  release_bytes(bytes);
  release_screen(screen);
}

void test_pixel(void) {
  const uext_t width = 255;
  const uext_t height = 255;
  screen_t* screen = new_screen(width, height, 0, 0);

  // make png bitmaps
  png_t* fast_bm = new_png(width, height);
  png_t* naive_bm = new_png(width, height);
  png_t* spec_bm = new_png(width, height);

  // set up the interfaces
  generic_interface_t naive_prototype = {
      .pixel = (void*)true,
  };
  generic_interface_t* fast_intfc = new_png_generic_interface_full(fast_bm);
  generic_interface_t* naive_intfc =
      new_png_generic_interface_partial(naive_bm, naive_prototype);
  interface_t* specfic_intfc =
      new_png_specific_interface(spec_bm, screen, NULL, 0);

  TEST_ASSERT_NOT_NULL(fast_bm);
  TEST_ASSERT_NOT_NULL(naive_bm);
  TEST_ASSERT_NOT_NULL(spec_bm);

  TEST_ASSERT_NOT_NULL(fast_intfc);
  TEST_ASSERT_NOT_NULL(naive_intfc);
  TEST_ASSERT_NOT_NULL(specfic_intfc);

  // draw some pixels
  const uint32_t num_pix = 1000;
  for (uint32_t count = 0; count < num_pix; count++) {
    uext_t u = rand() % width;
    uext_t v = rand() % height;
    png_pixel_t pixel = png_color_random();

    // limit pixels to be within the region where u <= v
    if (u > v) {
      u = v;
    }

    // draw the pixel using the interface(s)
    generic_pixel(fast_intfc, (void*)&pixel, u, v);
    generic_pixel(naive_intfc, (void*)&pixel, u, v);
    sicgl_specific_pixel(specfic_intfc, (void*)&pixel, u, v);
  }

  // store images
  TEST_ASSERT_EQUAL_INT(0, png_to_file(fast_bm, TEST_OUTPUT_DIR "/fast.png"));
  TEST_ASSERT_EQUAL_INT(0, png_to_file(naive_bm, TEST_OUTPUT_DIR "/naive.png"));
  TEST_ASSERT_EQUAL_INT(
      0, png_to_file(spec_bm, TEST_OUTPUT_DIR "/specific.png"));

  // compare the memory for the two images
  size_t compare_len = png_compare_len_bytes(fast_bm, naive_bm);
  TEST_ASSERT_EQUAL_MEMORY(fast_bm->pixels, naive_bm->pixels, compare_len);
  TEST_ASSERT_EQUAL_MEMORY(spec_bm->pixels, naive_bm->pixels, compare_len);

  // clean up
  release_png(fast_bm);
  release_png(naive_bm);
  release_png(spec_bm);
  release_png_generic_interface(fast_intfc);
  release_png_generic_interface(naive_intfc);
  release_png_specific_interface(specfic_intfc);
  release_screen(screen);
}

// not needed when using generate_test_runner.rb
int main(void) {
  UNITY_BEGIN();
  // RUN_TEST(test_pixel_location_generic_full);
  // RUN_TEST(test_pixel_location_generic_naive);
  // RUN_TEST(test_pixel_location_specific);
  RUN_TEST(test_pixel);
  return UNITY_END();
}
