#include "sicgl/screen.h"
#include "utils.h"

void test_specific_display_line(void) {
  uext_t width = 255;
  uext_t height = 255;

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

    // draw a line
    int color = truecolor_random_color();
    int ret = simultaneous_specific_display_line(
        reference, interface, color, width / 4, height / 8, 3 * width / 4,
        7 * height / 8);
    image = new_image_from_libgd_specific_interface(interface);
    TEST_ASSERT_NOT_NULL_MESSAGE(image, "could not convert test image");

    // save images to png
    ref = new_png_from_image(reference);
    img = new_png_from_libgd_specific_interface(interface);
    TEST_ASSERT_NOT_NULL_MESSAGE(ref, "could not create ref png");
    TEST_ASSERT_NOT_NULL_MESSAGE(img, "could not create img png");
    TEST_ASSERT_EQUAL_INT(
        0, png_to_file(ref, TEST_OUTPUT_DIR "/specific_screen_line_ref.png"));
    TEST_ASSERT_EQUAL_INT(
        0, png_to_file(img, TEST_OUTPUT_DIR "/specific_screen_line_img.png"));
    TEST_ASSERT_EQUAL_INT_MESSAGE(0, ret, "failed to draw line");

    // compare the images
    TEST_ASSERT_EQUAL_INT(0, compare_image(reference, image));
  }

  // clean up
  release_image(reference);
  release_image(image);
  release_screen(screen);
  release_libgd_specific_interface(interface);
  release_png(ref);
  release_png(img);
}

void test_specific_display_rectangle(void) {
  uext_t width = 255;
  uext_t height = 255;

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

    // draw a rectangle
    int color = truecolor_random_color();
    int ret = simultaneous_specific_display_rectangle(
        reference, interface, color, -(width / 4), height / 8, 3 * width / 4,
        7 * height / 8);
    image = new_image_from_libgd_specific_interface(interface);
    TEST_ASSERT_NOT_NULL_MESSAGE(image, "could not convert test image");

    // save images to png
    ref = new_png_from_image(reference);
    img = new_png_from_libgd_specific_interface(interface);
    TEST_ASSERT_NOT_NULL_MESSAGE(ref, "could not create ref png");
    TEST_ASSERT_NOT_NULL_MESSAGE(img, "could not create img png");
    TEST_ASSERT_EQUAL_INT(
        0,
        png_to_file(ref, TEST_OUTPUT_DIR "/specific_screen_rectangle_ref.png"));
    TEST_ASSERT_EQUAL_INT(
        0,
        png_to_file(img, TEST_OUTPUT_DIR "/specific_screen_rectangle_img.png"));
    TEST_ASSERT_EQUAL_INT_MESSAGE(0, ret, "failed to draw rectangle");

    // compare the images
    TEST_ASSERT_EQUAL_INT(0, compare_image(reference, image));
  }

  // clean up
  release_image(reference);
  release_image(image);
  release_screen(screen);
  release_libgd_specific_interface(interface);
  release_png(ref);
  release_png(img);
}

void test_specific_display_circle_bresenham(void) {
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

    // draw a circle
    int color = truecolor_random_color();
    int ret = simultaneous_specific_display_circle_bresenham(
        reference, interface, color, width / 2, height / 2, 20);
    image = new_image_from_libgd_specific_interface(interface);
    TEST_ASSERT_NOT_NULL_MESSAGE(image, "could not convert test image");

    // save images to png
    ref = new_png_from_image(reference);
    img = new_png_from_libgd_specific_interface(interface);
    TEST_ASSERT_NOT_NULL_MESSAGE(ref, "could not create ref png");
    TEST_ASSERT_NOT_NULL_MESSAGE(img, "could not create img png");
    TEST_ASSERT_EQUAL_INT(
        0,
        png_to_file(
            ref, TEST_OUTPUT_DIR "/specific_screen_circle_bresenham_ref.png"));
    TEST_ASSERT_EQUAL_INT(
        0,
        png_to_file(
            img, TEST_OUTPUT_DIR "/specific_screen_circle_bresenham_img.png"));
    TEST_ASSERT_EQUAL_INT_MESSAGE(0, ret, "failed to draw circle");

    // compare the images
    // // note: bresenham circles are not expected to match the libgd
    // implementation
  }

  // clean up
  release_image(reference);
  release_image(image);
  release_screen(screen);
  release_libgd_specific_interface(interface);
  release_png(ref);
  release_png(img);
}

void test_specific_display_circle_ellipse(void) {
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

    // draw a circle
    int color = truecolor_random_color();
    int ret = simultaneous_specific_display_circle_ellipse(
        reference, interface, color, width / 2, height / 2, 20);
    image = new_image_from_libgd_specific_interface(interface);
    TEST_ASSERT_NOT_NULL_MESSAGE(image, "could not convert test image");

    // save images to png
    ref = new_png_from_image(reference);
    img = new_png_from_libgd_specific_interface(interface);
    TEST_ASSERT_NOT_NULL_MESSAGE(ref, "could not create ref png");
    TEST_ASSERT_NOT_NULL_MESSAGE(img, "could not create img png");
    TEST_ASSERT_EQUAL_INT(
        0, png_to_file(
               ref, TEST_OUTPUT_DIR "/specific_screen_circle_ellipse_ref.png"));
    TEST_ASSERT_EQUAL_INT(
        0, png_to_file(
               img, TEST_OUTPUT_DIR "/specific_screen_circle_ellipse_img.png"));
    TEST_ASSERT_EQUAL_INT_MESSAGE(0, ret, "failed to draw circle");

    // compare the images
    TEST_ASSERT_EQUAL_INT(0, compare_image(reference, image));
  }

  // clean up
  release_image(reference);
  release_image(image);
  release_screen(screen);
  release_libgd_specific_interface(interface);
  release_png(ref);
  release_png(img);
}

void test_specific_display_ellipse(void) {
  TEST_IGNORE_MESSAGE("not implemented");
}

void test_specific_display_line_case1(void) {
  uext_t width = 8;
  uext_t height = 8;

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

    // draw a line
    int color = truecolor_random_color();
    int ret = simultaneous_specific_display_line(
        reference, interface, color, 1, 1, 0, 6);
    image = new_image_from_libgd_specific_interface(interface);
    TEST_ASSERT_NOT_NULL_MESSAGE(image, "could not convert test image");

    // save images to png
    ref = new_png_from_image(reference);
    img = new_png_from_libgd_specific_interface(interface);
    TEST_ASSERT_NOT_NULL_MESSAGE(ref, "could not create ref png");
    TEST_ASSERT_NOT_NULL_MESSAGE(img, "could not create img png");
    TEST_ASSERT_EQUAL_INT(
        0, png_to_file(
               ref, TEST_OUTPUT_DIR "/specific_screen_line_case1_ref.png"));
    TEST_ASSERT_EQUAL_INT(
        0, png_to_file(
               img, TEST_OUTPUT_DIR "/specific_screen_line_case1_img.png"));
    TEST_ASSERT_EQUAL_INT_MESSAGE(0, ret, "failed to draw line");

    // compare the images
    TEST_ASSERT_EQUAL_INT(0, compare_image(reference, image));
  }

  // clean up
  release_image(reference);
  release_image(image);
  release_screen(screen);
  release_libgd_specific_interface(interface);
  release_png(ref);
  release_png(img);
}

void test_specific_display_line_case2(void) {
  uext_t width = 8;
  uext_t height = 8;

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

    // draw a line
    int color = truecolor_random_color();
    int ret = simultaneous_specific_display_line(
        reference, interface, color, 1, 1, 25, 6);
    image = new_image_from_libgd_specific_interface(interface);
    TEST_ASSERT_NOT_NULL_MESSAGE(image, "could not convert test image");

    // save images to png
    ref = new_png_from_image(reference);
    img = new_png_from_libgd_specific_interface(interface);
    TEST_ASSERT_NOT_NULL_MESSAGE(ref, "could not create ref png");
    TEST_ASSERT_NOT_NULL_MESSAGE(img, "could not create img png");
    TEST_ASSERT_EQUAL_INT(
        0, png_to_file(
               ref, TEST_OUTPUT_DIR "/specific_screen_line_case2_ref.png"));
    TEST_ASSERT_EQUAL_INT(
        0, png_to_file(
               img, TEST_OUTPUT_DIR "/specific_screen_line_case2_img.png"));
    TEST_ASSERT_EQUAL_INT_MESSAGE(0, ret, "failed to draw line");

    // compare the images
    TEST_ASSERT_EQUAL_INT(0, compare_image(reference, image));
  }

  // clean up
  release_image(reference);
  release_image(image);
  release_screen(screen);
  release_libgd_specific_interface(interface);
  release_png(ref);
  release_png(img);
}
