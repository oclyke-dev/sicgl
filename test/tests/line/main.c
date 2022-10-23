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


  gdImagePtr _image = gdImageCreateTrueColor(width, height);
  specific_interface_t* specific_regular = new_libgd_specific_interface(_image, screen, NULL, 0);
  sicgl_specific_region(specific_regular, &color, 1, 1, 3, 3);

  // view the memory contents
  libgd_specific_interface_show_memory(specific_regular);


  png_t* png = new_png_from_libgd_specific_interface(specific_regular);
  TEST_ASSERT_EQUAL_INT(0, png_to_file(png, TEST_OUTPUT_DIR "/out.png"));
  
  release_libgd_specific_interface(specific_regular);
  release_screen(screen);
  release_png(png);



  
  // for (size_t idx = 0; idx < width * height; idx++) {
  //   if ((idx % width) == 0) {
  //     printf("\n");
  //   }
  //   printf("%08x ", _image->tpixels[idx]);    
  // }

  // printf("\n\n");

  // for (size_t idx = 0; idx < width * height; idx++) {
  //   if ((idx % width) == 0) {
  //     printf("\n");
  //   }
  //   printf("%08x ", _image->tpixels[idx % width][idx / width]);    
  // }

  // for (size_t idx = 0; idx < width * height; idx++) {
  //   if ((idx % width) == 0) {
  //     printf("\n");
  //   }
  //   // printf("%08x ", _image->tpixels[idx]);
  //   printf("%08x ", gdImageTrueColorPixel(_image, (idx % width), (idx / width)));
    
  // }


  // image_to_file(_image, "test.png");


  // // draw the line simultaneously
  // simultaneous_line(&reference, &image, width, height, screen, 1, 1, 3, 3, color);
  // TEST_ASSERT_NOT_NULL(reference);
  // TEST_ASSERT_NOT_NULL(image);

  // // save the images
  // TEST_ASSERT_EQUAL_INT(0, image_to_file(reference, TEST_OUTPUT_DIR "/reference.png"));
  // TEST_ASSERT_EQUAL_INT(0, image_to_file(image, TEST_OUTPUT_DIR "/fdgdftedsfst.png"));

  // // // compare the images
  // // TEST_ASSERT_EQUAL_INT(0, compare_image(reference, image));
}

int main() {
  UNITY_BEGIN();
  RUN_TEST(test_line);
  return UNITY_END();
}
