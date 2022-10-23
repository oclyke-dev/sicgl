#include <stdio.h>
#include <stdlib.h>

#include "gd.h"
#include "sicgl.h"
#include "spng.h"
#include "test_utils.h"

void setUp(void) {
  // set stuff up here
}

void tearDown(void) {
  // clean stuff up here
}

void test_line(void) {
  int ret = 0;
  size_t width = 10;
  size_t height = 10;
  gdImage* reference = NULL;
  gdImage* image = NULL;
  int color = truecolor_random_color();
  screen_t* screen = new_screen(width, height, 0, 0);


  // gdImagePtr _image = gdImageCreateTrueColor(width, height);
  // specific_interface_t* specific_regular = new_libgd_specific_interface(_image, screen, NULL, 0);
  // sicgl_specific_region(specific_regular, &color, 1, 1, 3, 3);

  // // view the memory contents
  // libgd_specific_interface_show_memory(specific_regular);


  // png_t* png = new_png_from_libgd_specific_interface(specific_regular);
  // TEST_ASSERT_EQUAL_INT(0, png_to_file(png, TEST_OUTPUT_DIR "/out.png"));
  
  // release_libgd_specific_interface(specific_regular);
  // release_screen(screen);
  // release_png(png);

  // draw the line simultaneously
  simultaneous_line(&reference, &image, width, height, screen, 1, 1, 3, 3, color);
  TEST_ASSERT_NOT_NULL(reference);
  TEST_ASSERT_NOT_NULL(image);

  // compare the images
  int compare_status = compare_image(reference, image);

  // save the images
  png_t* ref_png = new_png_from_image(reference);
  png_t* test_png = new_png_from_image(image);
  int output_status_ref = png_to_file(ref_png, TEST_OUTPUT_DIR "/reference.png");
  int output_status_test = png_to_file(test_png, TEST_OUTPUT_DIR "/test.png");
  release_png(ref_png);
  release_png(test_png);

  // make assertions
  TEST_ASSERT_EQUAL_INT(0, compare_status);
  TEST_ASSERT_EQUAL_INT(0, output_status_ref);
  TEST_ASSERT_EQUAL_INT(0, output_status_test);
}

int main() {
  UNITY_BEGIN();
  RUN_TEST(test_line);
  return UNITY_END();
}
