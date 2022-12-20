#include "sicgl/screen.h"
#include "utils.h"

void test_specific_pixel(void) {
  uext_t width = 3;
  uext_t height = 3;

  gdImage* reference = NULL;
  gdImage* image = NULL;
  screen_t* screen = NULL;
  specific_interface_t* interface = NULL;
  png_t* ref = NULL;
  png_t* img = NULL;

  if (TEST_PROTECT()) {
    // create images
    reference = new_image(width, height);
    TEST_ASSERT_NOT_NULL_MESSAGE(
        reference, "could not allocate reference image");

    // create specific interface
    screen = new_screen_extent(width, height, 0, 0);
    interface = new_libgd_specific_interface(screen, NULL, 0);
    TEST_ASSERT_NOT_NULL_MESSAGE(screen, "could not create screen");
    TEST_ASSERT_NOT_NULL_MESSAGE(interface, "could not create interface");

    // draw a pixel
    int color = truecolor_random_color();
    int ret = simultaneous_specific_pixel(reference, interface, color, 1, 1);
    image = new_image_from_libgd_specific_interface(interface);
    TEST_ASSERT_NOT_NULL_MESSAGE(image, "could not convert test image");

    // save images to png
    ref = new_png_from_image(reference);
    img = new_png_from_libgd_specific_interface(interface);
    TEST_ASSERT_NOT_NULL_MESSAGE(ref, "could not create ref png");
    TEST_ASSERT_NOT_NULL_MESSAGE(img, "could not create img png");
    TEST_ASSERT_EQUAL_INT(
        0, png_to_file(ref, TEST_OUTPUT_DIR "/specific_pixel_ref.png"));
    TEST_ASSERT_EQUAL_INT(
        0, png_to_file(img, TEST_OUTPUT_DIR "/specific_pixel_img.png"));
    TEST_ASSERT_EQUAL_INT_MESSAGE(0, ret, "failed to draw pixel");

    // compare the images
    TEST_ASSERT_EQUAL_INT(0, compare_image(reference, image));

  } else {
    release_image(reference);
    release_image(image);
    release_screen(screen);
    release_libgd_specific_interface(interface);
    release_png(ref);
    release_png(img);
  }
}

void test_specific_hline(void) {
  uext_t width = 30;
  uext_t height = 3;

  gdImage* reference = NULL;
  gdImage* image = NULL;
  screen_t* screen = NULL;
  specific_interface_t* interface = NULL;
  png_t* ref = NULL;
  png_t* img = NULL;

  if (TEST_PROTECT()) {
    // create images
    reference = new_image(width, height);
    TEST_ASSERT_NOT_NULL_MESSAGE(
        reference, "could not allocate reference image");

    // create specific interface
    screen = new_screen_extent(width, height, 0, 0);
    interface = new_libgd_specific_interface(screen, NULL, 0);
    TEST_ASSERT_NOT_NULL_MESSAGE(screen, "could not create screen");
    TEST_ASSERT_NOT_NULL_MESSAGE(interface, "could not create interface");

    // draw a hline
    int color = truecolor_random_color();
    int ret =
        simultaneous_specific_hline(reference, interface, color, 1, 1, 28, 1);
    image = new_image_from_libgd_specific_interface(interface);
    TEST_ASSERT_NOT_NULL_MESSAGE(image, "could not convert test image");

    // save images to png
    ref = new_png_from_image(reference);
    img = new_png_from_libgd_specific_interface(interface);
    TEST_ASSERT_NOT_NULL_MESSAGE(ref, "could not create ref png");
    TEST_ASSERT_NOT_NULL_MESSAGE(img, "could not create img png");
    TEST_ASSERT_EQUAL_INT(
        0, png_to_file(ref, TEST_OUTPUT_DIR "/specific_hline_ref.png"));
    TEST_ASSERT_EQUAL_INT(
        0, png_to_file(img, TEST_OUTPUT_DIR "/specific_hline_img.png"));
    TEST_ASSERT_EQUAL_INT_MESSAGE(0, ret, "failed to draw hline");

    // compare the images
    TEST_ASSERT_EQUAL_INT(0, compare_image(reference, image));

  } else {
    release_image(reference);
    release_image(image);
    release_screen(screen);
    release_libgd_specific_interface(interface);
    release_png(ref);
    release_png(img);
  }
}

void test_specific_vline(void) {
  uext_t width = 3;
  uext_t height = 30;

  gdImage* reference = NULL;
  gdImage* image = NULL;
  screen_t* screen = NULL;
  specific_interface_t* interface = NULL;
  png_t* ref = NULL;
  png_t* img = NULL;

  if (TEST_PROTECT()) {
    // create images
    reference = new_image(width, height);
    TEST_ASSERT_NOT_NULL_MESSAGE(
        reference, "could not allocate reference image");

    // create specific interface
    screen = new_screen_extent(width, height, 0, 0);
    interface = new_libgd_specific_interface(screen, NULL, 0);
    TEST_ASSERT_NOT_NULL_MESSAGE(screen, "could not create screen");
    TEST_ASSERT_NOT_NULL_MESSAGE(interface, "could not create interface");

    // draw a vline
    int color = truecolor_random_color();
    int ret =
        simultaneous_specific_vline(reference, interface, color, 1, 1, 1, 28);
    image = new_image_from_libgd_specific_interface(interface);
    TEST_ASSERT_NOT_NULL_MESSAGE(image, "could not convert test image");

    // save images to png
    ref = new_png_from_image(reference);
    img = new_png_from_libgd_specific_interface(interface);
    TEST_ASSERT_NOT_NULL_MESSAGE(ref, "could not create ref png");
    TEST_ASSERT_NOT_NULL_MESSAGE(img, "could not create img png");
    TEST_ASSERT_EQUAL_INT(
        0, png_to_file(ref, TEST_OUTPUT_DIR "/specific_vline_ref.png"));
    TEST_ASSERT_EQUAL_INT(
        0, png_to_file(img, TEST_OUTPUT_DIR "/specific_vline_img.png"));
    TEST_ASSERT_EQUAL_INT_MESSAGE(0, ret, "failed to draw vline");

    // compare the images
    TEST_ASSERT_EQUAL_INT(0, compare_image(reference, image));

  } else {
    release_image(reference);
    release_image(image);
    release_screen(screen);
    release_libgd_specific_interface(interface);
    release_png(ref);
    release_png(img);
  }
}

void test_specific_region(void) {
  uext_t width = 30;
  uext_t height = 30;

  gdImage* reference = NULL;
  gdImage* image = NULL;
  screen_t* screen = NULL;
  specific_interface_t* interface = NULL;
  png_t* ref = NULL;
  png_t* img = NULL;

  if (TEST_PROTECT()) {
    // create images
    reference = new_image(width, height);
    TEST_ASSERT_NOT_NULL_MESSAGE(
        reference, "could not allocate reference image");

    // create specific interface
    screen = new_screen_extent(width, height, 0, 0);
    interface = new_libgd_specific_interface(screen, NULL, 0);
    TEST_ASSERT_NOT_NULL_MESSAGE(screen, "could not create screen");
    TEST_ASSERT_NOT_NULL_MESSAGE(interface, "could not create interface");

    // draw a pixel
    int color = truecolor_random_color();
    int ret =
        simultaneous_specific_region(reference, interface, color, 1, 1, 28, 28);
    image = new_image_from_libgd_specific_interface(interface);
    TEST_ASSERT_NOT_NULL_MESSAGE(image, "could not convert test image");

    // save images to png
    ref = new_png_from_image(reference);
    img = new_png_from_libgd_specific_interface(interface);
    TEST_ASSERT_NOT_NULL_MESSAGE(ref, "could not create ref png");
    TEST_ASSERT_NOT_NULL_MESSAGE(img, "could not create img png");
    TEST_ASSERT_EQUAL_INT(
        0, png_to_file(ref, TEST_OUTPUT_DIR "/specific_region_ref.png"));
    TEST_ASSERT_EQUAL_INT(
        0, png_to_file(img, TEST_OUTPUT_DIR "/specific_region_img.png"));
    TEST_ASSERT_EQUAL_INT_MESSAGE(0, ret, "failed to draw region");

    // compare the images
    TEST_ASSERT_EQUAL_INT(0, compare_image(reference, image));

  } else {
    release_image(reference);
    release_image(image);
    release_screen(screen);
    release_libgd_specific_interface(interface);
    release_png(ref);
    release_png(img);
  }
}
