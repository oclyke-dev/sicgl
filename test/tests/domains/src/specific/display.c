#include "sicgl/screen.h"
#include "utils.h"

void test_specific_display_line(void) {
  uext_t width = 255;
  uext_t height = 255;

  gdImage* reference;
  gdImage* image;
  display_t* display;
  specific_interface_t* interface;
  color_sequence_t* color_sequence;
  png_t* ref;
  png_t* img;

  if (TEST_PROTECT()) {
    // create images
    reference = new_image(width, height);
    TEST_ASSERT_NOT_NULL_MESSAGE(
        reference, "could not allocate reference image");

    // create specific interface
    display = new_display(width, height, 0, 0);
    interface = new_libgd_specific_interface(display, NULL, 0);
    TEST_ASSERT_NOT_NULL_MESSAGE(display, "could not create display");
    TEST_ASSERT_NOT_NULL_MESSAGE(interface, "could not create interface");

    // create a color sequence
    int color = truecolor_random_color();
    color_sequence = new_color_sequence(
        SICGL_CS_STATIC, sizeof(int), (uint8_t*)&color, sizeof(color));
    TEST_ASSERT_NOT_NULL_MESSAGE(
        color_sequence, "could not create color sequence");

    // draw a pixel
    int ret =
        simultaneous_specific_display_line(reference, interface, color_sequence, width / 4, height / 8, 3*width/4, 7*height/8);
    image = new_image_from_libgd_specific_interface(interface);
    TEST_ASSERT_NOT_NULL_MESSAGE(image, "could not convert test image");

    // save images to png
    ref = new_png_from_image(reference);
    img = new_png_from_libgd_specific_interface(interface);
    TEST_ASSERT_NOT_NULL_MESSAGE(ref, "could not create ref png");
    TEST_ASSERT_NOT_NULL_MESSAGE(img, "could not create img png");
    TEST_ASSERT_EQUAL_INT(
        0, png_to_file(ref, TEST_OUTPUT_DIR "/specific_display_line_ref.png"));
    TEST_ASSERT_EQUAL_INT(
        0, png_to_file(img, TEST_OUTPUT_DIR "/specific_display_line_img.png"));
    TEST_ASSERT_EQUAL_INT_MESSAGE(0, ret, "failed to draw pixel");

    // compare the images
    TEST_ASSERT_EQUAL_INT(0, compare_image(reference, image));

  } else {
    release_image(reference);
    release_image(image);
    release_display(display);
    release_libgd_specific_interface(interface);
    release_color_sequence(color_sequence);
    release_png(ref);
    release_png(img);
  }
}

void test_specific_display_rectangle(void) {
  TEST_IGNORE_MESSAGE("not implemented");
}

void test_specific_display_circle(void) {
  TEST_IGNORE_MESSAGE("not implemented");
}

void test_specific_display_ellipse(void) {
  TEST_IGNORE_MESSAGE("not implemented");
}
