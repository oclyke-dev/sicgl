#include "sicgl/color.h"
#include "utils.h"

void setUp(void) {
  // set stuff up here
}

void tearDown(void) {
  // clean stuff up here
}

void test_png_output(void) {
  uext_t width = 10;
  uext_t height = 10;

  screen_t* screen = NULL;
  interface_t* interface = NULL;
  png_t* img = NULL;

  if (TEST_PROTECT()) {
    // create specific interface
    screen = new_screen_extent(width, height, 0, 0);
    interface = new_libgd_interface(screen, NULL, 0);
    TEST_ASSERT_NOT_NULL_MESSAGE(screen, "could not create screen");
    TEST_ASSERT_NOT_NULL_MESSAGE(interface, "could not create interface");

    // draw a line
    int ret = sicgl_interface_line(interface, 0xF557ED, 1, 1, 7, 5);

    // save image to png
    img = new_png_from_libgd_interface(interface);
    TEST_ASSERT_NOT_NULL_MESSAGE(img, "could not create img png");
    TEST_ASSERT_EQUAL_INT(0, png_to_file(img, TEST_OUTPUT_DIR "/output.png"));
    TEST_ASSERT_EQUAL_INT_MESSAGE(0, ret, "failed to draw line");
  }

  // clean up
  release_screen(screen);
  release_libgd_interface(interface);
  release_png(img);
}

void test_png_io(void) {
  png_t* asset = NULL;
  png_t* output = NULL;

  if (TEST_PROTECT()) {
    // load the asset into a png
    int ret = png_from_file(TEST_SOURCE_DIR "/assets/synthsicgl.png", &asset);
    TEST_ASSERT_EQUAL_INT_MESSAGE(0, ret, "failed to load png from file");
    TEST_ASSERT_NOT_NULL_MESSAGE(asset, "failed to create png structure");

    // write the asset png to output
    ret = png_to_file(asset, TEST_OUTPUT_DIR "/output.png");
    TEST_ASSERT_EQUAL_INT_MESSAGE(0, ret, "failed to write out png to file");

    // load the output into a png
    ret = png_from_file(TEST_OUTPUT_DIR "/output.png", &output);
    TEST_ASSERT_EQUAL_INT_MESSAGE(0, ret, "failed to load png from file");
    TEST_ASSERT_NOT_NULL_MESSAGE(output, "failed to create png structure");

    // compare the loaded asset to the loaded output
    int difference = png_compare(asset, output);
    TEST_ASSERT_EQUAL_INT_MESSAGE(0, difference, "asset and output mismatched");
  }

  // clean up
  release_png(asset);
  release_png(output);
}

// not needed when using generate_test_runner.rb
int main(void) {
  UNITY_BEGIN();

  RUN_TEST(test_png_output);
  RUN_TEST(test_png_io);

  return UNITY_END();
}
