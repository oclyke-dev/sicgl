#include "sicgl/screen.h"
#include "utils.h"

void test_generic_display_line(void) {
  uext_t width = 255;
  uext_t height = 255;

  gdImage* reference;
  gdImage* image;

  generic_interface_t* interface;
  png_t* ref;
  png_t* img;

  if (TEST_PROTECT()) {
    // create images
    reference = new_image(width, height);
    image = new_image(width, height);
    TEST_ASSERT_NOT_NULL_MESSAGE(
        reference, "could not allocate reference image");
    TEST_ASSERT_NOT_NULL_MESSAGE(image, "could not allocate test image");

    // create generic interface
    interface = new_libgd_generic_interface_full(image);
    TEST_ASSERT_NOT_NULL_MESSAGE(interface, "could not create interface");

    // create a color sequence
    int color = truecolor_random_color();
    int ret = simultaneous_generic_display_line(reference, interface, &color, 1, 1, width - 1, height/2);

    // save images to png
    ref = new_png_from_image(reference);
    img = new_png_from_image(image);
    TEST_ASSERT_NOT_NULL_MESSAGE(ref, "could not create ref png");
    TEST_ASSERT_NOT_NULL_MESSAGE(img, "could not create img png");
    TEST_ASSERT_EQUAL_INT(0, png_to_file(ref, TEST_OUTPUT_DIR "/generic_display_line_ref.png"));
    TEST_ASSERT_EQUAL_INT(0, png_to_file(img, TEST_OUTPUT_DIR "/generic_display_line_img.png"));
    TEST_ASSERT_EQUAL_INT_MESSAGE(0, ret, "failed to draw pixel");

    // compare the images
    TEST_ASSERT_EQUAL_INT(0, compare_image(reference, image));

  } else {
    release_image(reference);
    release_image(image);
    release_libgd_generic_interface(interface);
    release_png(ref);
    release_png(img);
  }
}

void test_generic_display_rectangle(void) {
  TEST_IGNORE_MESSAGE("not implemented");
}

void test_generic_display_circle(void) {
  TEST_IGNORE_MESSAGE("not implemented");
}

void test_generic_display_ellipse(void) {
  TEST_IGNORE_MESSAGE("not implemented");
}
