#include <stdbool.h>
#include <stdio.h>

#include "sicgl.h"
#include "test_utils.h"

// allow for multiple tests
typedef struct {
  const char* name;
  bool generic;
  bool full;
  color_t test_color;
  const uint8_t* reference;
  size_t width;
  size_t height;
  uext_t u;
  uext_t v0;
  uext_t v1;
} location_test_case_t;

#define DECLARE_TEST_CASE(                                                  \
    _name, _generic, _width, _height, _full, _reference, _tc, _u, _v0, _v1) \
  location_test_case_t _name = {                                            \
      .name = #_name,                                                       \
      .width = _width,                                                      \
      .height = _height,                                                    \
      .u = _u,                                                              \
      .v0 = _v0,                                                            \
      .v1 = _v1,                                                            \
      .test_color = _tc,                                                    \
      .reference = _reference,                                              \
      .full = _full,                                                        \
      .generic = _generic,                                                  \
  };

// a color definition to use
const uint8_t test_color = 0xEA;

// expected result from simple location test
const uint8_t pixel_location_expected_one[9] = {
    0, 0, 0, 0, test_color, 0, 0, 0, 0,
};
DECLARE_TEST_CASE(
    location_test_one_generic_full, true, 3, 3, true,
    pixel_location_expected_one, (void*)&test_color, 1, 1, 1);
DECLARE_TEST_CASE(
    location_test_one_generic_naive, true, 3, 3, false,
    pixel_location_expected_one, (void*)&test_color, 1, 1, 1);
DECLARE_TEST_CASE(
    location_test_one_specific, false, 3, 3, false, pixel_location_expected_one,
    (void*)&test_color, 1, 1, 1);

const uint8_t pixel_location_expected_two[15] = {
    0, 0, 0, 0, test_color, 0, 0, test_color, 0, 0, test_color, 0, 0, 0, 0,
};
DECLARE_TEST_CASE(
    location_test_two_generic_full, true, 3, 5, true,
    pixel_location_expected_two, (void*)&test_color, 1, 1, 3);
DECLARE_TEST_CASE(
    location_test_two_generic_naive, true, 3, 5, false,
    pixel_location_expected_two, (void*)&test_color, 1, 1, 3);
DECLARE_TEST_CASE(
    location_test_two_specific, false, 3, 5, false, pixel_location_expected_two,
    (void*)&test_color, 1, 1, 3);

// assemble the tests
const location_test_case_t* location_tests[] = {
    // first test
    &location_test_one_generic_full,
    &location_test_one_generic_naive,
    &location_test_one_specific,

    // second test
    &location_test_two_generic_full,
    &location_test_two_generic_naive,
    &location_test_two_specific,
};

void setUp(void) {
  // set stuff up here
}

void tearDown(void) {
  // clean stuff up here
}

void run_test_case(location_test_case_t test_case) {
  const char* case_name = test_case.name;
  bool generic = test_case.generic;
  size_t width = test_case.width;
  size_t height = test_case.height;
  bool full = test_case.full;
  const uint8_t* reference = test_case.reference;
  color_t test_color = test_case.test_color;
  uext_t u = test_case.u;
  uext_t v0 = test_case.v0;
  uext_t v1 = test_case.v1;

  bytes_t* bytes = new_bytes(width, height);
  TEST_ASSERT_NOT_NULL_MESSAGE(bytes, "could not allocate bytes object");

  printf("running test case: %s\n", case_name);
  if (generic) {
    generic_interface_t* intfc = NULL;
    if (full) {
      intfc = new_bytes_generic_interface_full(bytes);
    } else {
      generic_interface_t prototype = {
          .pixel = (void*)true,
      };
      intfc = new_bytes_generic_interface_partial(bytes, prototype);
    }
    TEST_ASSERT_NOT_NULL_MESSAGE(intfc, "could not allocate interface object");
    generic_vline(intfc, test_color, u, v0, v1);
    release_bytes_generic_interface(intfc);
  } else {
    screen_t* screen = new_screen(bytes->width, bytes->height, 0, 0);
    TEST_ASSERT_NOT_NULL_MESSAGE(screen, "could not allocate screen object");
    specific_interface_t* intfc =
        new_bytes_specific_interface(bytes, screen, NULL, 0);
    TEST_ASSERT_NOT_NULL_MESSAGE(intfc, "could not allocate interface object");
    specific_vline(intfc, test_color, u, v0, v1);
    release_bytes_specific_interface(intfc);
    release_screen(screen);
  }

  // verify that the location matches
  TEST_ASSERT_EQUAL_MEMORY_MESSAGE(
      reference, bytes->memory, bytes_length_bytes(bytes), case_name);
  release_bytes(bytes);
}

void test_locations(void) {
  int num_tests = sizeof(location_tests) / sizeof(location_test_case_t*);
  printf("%d test cases to run\n", num_tests);
  for (int idx = 0; idx < num_tests; idx++) {
    run_test_case(*location_tests[idx]);
  }
}

void test_vline(void) {
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
  specific_interface_t* specfic_intfc =
      new_png_specific_interface(spec_bm, screen, NULL, 0);

  TEST_ASSERT_NOT_NULL(fast_bm);
  TEST_ASSERT_NOT_NULL(naive_bm);
  TEST_ASSERT_NOT_NULL(spec_bm);

  TEST_ASSERT_NOT_NULL(fast_intfc);
  TEST_ASSERT_NOT_NULL(naive_intfc);
  TEST_ASSERT_NOT_NULL(specfic_intfc);

  // draw some lines
  const uint32_t num_lines = 250;
  for (uint32_t count = 0; count < num_lines; count++) {
    uext_t u = rand() % width;
    uext_t v0 = rand() % height;
    uext_t v1 = rand() % height;
    png_pixel_t pixel = png_color_random();

    // draw the pixel using the interfaces
    generic_vline(fast_intfc, &pixel, u, v0, v1);
    generic_vline(naive_intfc, &pixel, u, v0, v1);
    specific_vline(specfic_intfc, &pixel, u, v0, v1);
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
  RUN_TEST(test_locations);
  RUN_TEST(test_vline);
  return UNITY_END();
}
