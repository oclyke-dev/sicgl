#include <stdbool.h>
#include <stdio.h>

#include "test_utils.h"
#include "sicgl.h"

// allow for multiple tests
typedef struct {
  const char* name;
  bool generic;
  bool full;
  color_t test_color;
  const uint8_t* reference;
  size_t width;
  size_t height;
  uext_t u0;
  uext_t v0;
  uext_t u1;
  uext_t v1;
} location_test_case_t;

#define DECLARE_TEST_CASE(_name, _generic, _width, _height, _full, _reference, \
                          _tc, _u0, _v0, _u1, _v1)                             \
  location_test_case_t _name = {                                               \
      .name = #_name,                                                          \
      .width = _width,                                                         \
      .height = _height,                                                       \
      .u0 = _u0,                                                               \
      .v0 = _v0,                                                               \
      .u1 = _u1,                                                               \
      .v1 = _v1,                                                               \
      .test_color = _tc,                                                       \
      .reference = _reference,                                                 \
      .full = _full,                                                           \
      .generic = _generic,                                                     \
  };

// a color definition to use
const uint8_t test_color = 0xEA;

// expected result from simple location test
const uint8_t pixel_location_expected_one[9] = {
    0, 0, 0, 0, test_color, 0, 0, 0, 0,
};
DECLARE_TEST_CASE(location_test_one_generic_full, true, 3, 3, true,
                  pixel_location_expected_one, (void*)&test_color, 1, 1, 1, 1);
DECLARE_TEST_CASE(location_test_one_generic_naive, true, 3, 3, false,
                  pixel_location_expected_one, (void*)&test_color, 1, 1, 1, 1);
DECLARE_TEST_CASE(location_test_one_specific, false, 3, 3, false,
                  pixel_location_expected_one, (void*)&test_color, 1, 1, 1, 1);

const uint8_t pixel_location_expected_two[15] = {
    0, 0, 0, 0, test_color, 0, 0, test_color, 0, 0, test_color, 0, 0, 0, 0,
};
DECLARE_TEST_CASE(location_test_two_generic_full, true, 3, 5, true,
                  pixel_location_expected_two, (void*)&test_color, 1, 1, 1, 3);
DECLARE_TEST_CASE(location_test_two_generic_naive, true, 3, 5, false,
                  pixel_location_expected_two, (void*)&test_color, 1, 1, 1, 3);
DECLARE_TEST_CASE(location_test_two_specific, false, 3, 5, false,
                  pixel_location_expected_two, (void*)&test_color, 1, 1, 1, 3);

const uint8_t pixel_location_expected_three[20] = {
    0,          0, 0,          0,          0, test_color, test_color,
    0,          0, test_color, test_color, 0, 0,          test_color,
    test_color, 0, 0,          0,          0, 0,
};
DECLARE_TEST_CASE(location_test_three_generic_full, true, 4, 5, true,
                  pixel_location_expected_three, (void*)&test_color, 1, 1, 2,
                  3);
DECLARE_TEST_CASE(location_test_three_generic_naive, true, 4, 5, false,
                  pixel_location_expected_three, (void*)&test_color, 1, 1, 2,
                  3);
DECLARE_TEST_CASE(location_test_three_specific, false, 4, 5, false,
                  pixel_location_expected_three, (void*)&test_color, 1, 1, 2,
                  3);

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

    // third test
    &location_test_three_generic_full,
    &location_test_three_generic_naive,
    &location_test_three_specific,
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
  uext_t u0 = test_case.u0;
  uext_t v0 = test_case.v0;
  uext_t u1 = test_case.u1;
  uext_t v1 = test_case.v1;

  bytes_t* bytes = bytes_new(width, height);
  TEST_ASSERT_NOT_NULL_MESSAGE(bytes, "could not allocate bytes object");

  printf("running test case: %s\n", case_name);
  if (generic) {
    generic_interface_t* intfc = bytes_new_generic_interface(bytes, full);
    TEST_ASSERT_NOT_NULL_MESSAGE(intfc, "could not allocate interface object");
    sicgl_generic_region(intfc, test_color, u0, v0, u1, v1);
  } else {
    specific_interface_t* intfc = bytes_new_specific_interface(bytes);
    TEST_ASSERT_NOT_NULL_MESSAGE(intfc, "could not allocate interface object");
    screen_t* screen = bytes_new_screen(bytes);
    TEST_ASSERT_NOT_NULL_MESSAGE(intfc, "could not allocate screen object");
    sicgl_specific_region(intfc, screen, test_color, u0, v0, u1, v1);
  }

  // verify that the location matches
  TEST_ASSERT_EQUAL_MEMORY_MESSAGE(reference, bytes->memory, bytes->length,
                                   case_name);

  // bummer - if a test assert fails the execution does not continue and clean
  // up...
  bytes_free(bytes);
}

void test_locations(void) {
  int num_tests = sizeof(location_tests) / sizeof(location_test_case_t*);
  printf("%d test cases to run\n", num_tests);
  for (int idx = 0; idx < num_tests; idx++) {
    run_test_case(*location_tests[idx]);
  }
}

void test_region(void) {
  const uext_t width = 255;
  const uext_t height = 255;

  // set up the interfaces
  // // right now this implementation relies on the naive
  // // region, but that falls back to one of hline or vline
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
  const uint32_t regions = 250;
  for (uint32_t count = 0; count < regions; count++) {
    uext_t u0 = rand() % width;
    uext_t v0 = rand() % height;
    uext_t u1 = rand() % width;
    uext_t v1 = rand() % height;
    bitmap_pixel_t pixel = bmp_random_color();

    // draw the pixel using the interfaces
    sicgl_generic_region(&fast_intfc, (void*)&pixel, u0, v0, u1, v1);
    sicgl_generic_region(&naive_intfc, (void*)&pixel, u0, v0, u1, v1);
    sicgl_specific_region(&specfic_intfc, &spec_screen, (void*)&pixel, u0, v0,
                          u1, v1);
  }

  // store images
  bitmap_to_file(fast_bm, "test_region_fast.png");
  bitmap_to_file(naive_bm, "test_region_naive.png");
  bitmap_to_file(spec_bm, "test_region_specific.png");

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
  RUN_TEST(test_locations);
  RUN_TEST(test_region);
  return UNITY_END();
}
