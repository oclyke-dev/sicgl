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

    // draw a line
    int color = truecolor_random_color();
    int ret = simultaneous_generic_display_line(
        reference, interface, &color, 1, 1, width - 1, height / 2);

    // save images to png
    ref = new_png_from_image(reference);
    img = new_png_from_image(image);
    TEST_ASSERT_NOT_NULL_MESSAGE(ref, "could not create ref png");
    TEST_ASSERT_NOT_NULL_MESSAGE(img, "could not create img png");
    TEST_ASSERT_EQUAL_INT(
        0, png_to_file(ref, TEST_OUTPUT_DIR "/generic_display_line_ref.png"));
    TEST_ASSERT_EQUAL_INT(
        0, png_to_file(img, TEST_OUTPUT_DIR "/generic_display_line_img.png"));
    TEST_ASSERT_EQUAL_INT_MESSAGE(0, ret, "failed to draw line");

    // compare the images
    TEST_ASSERT_EQUAL_INT(0, compare_image(reference, image));
  }

  // clean up
  release_image(reference);
  release_image(image);
  release_libgd_generic_interface(interface);
  release_png(ref);
  release_png(img);
}

void test_generic_display_rectangle(void) {
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

    // draw a rectangle
    int color = truecolor_random_color();
    int ret = simultaneous_generic_display_rectangle(
        reference, interface, &color, -(width / 4), height / 8, 3 * width / 4,
        7 * height / 8);

    // save images to png
    ref = new_png_from_image(reference);
    img = new_png_from_image(image);
    TEST_ASSERT_NOT_NULL_MESSAGE(ref, "could not create ref png");
    TEST_ASSERT_NOT_NULL_MESSAGE(img, "could not create img png");
    TEST_ASSERT_EQUAL_INT(
        0,
        png_to_file(ref, TEST_OUTPUT_DIR "/generic_display_rectangle_ref.png"));
    TEST_ASSERT_EQUAL_INT(
        0,
        png_to_file(img, TEST_OUTPUT_DIR "/generic_display_rectangle_img.png"));
    TEST_ASSERT_EQUAL_INT_MESSAGE(0, ret, "failed to draw rectangle");

    // compare the images
    TEST_ASSERT_EQUAL_INT(0, compare_image(reference, image));
  }

  // clean up
  release_image(reference);
  release_image(image);
  release_libgd_generic_interface(interface);
  release_png(ref);
  release_png(img);
}

void test_generic_display_circle_bresenham(void) {
  uext_t width = 30;
  uext_t height = 30;

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

    // draw a rectangle
    int color = truecolor_random_color();
    int ret = simultaneous_generic_display_circle_bresenham(
        reference, interface, &color, width / 2, height / 2, 10);

    // save images to png
    ref = new_png_from_image(reference);
    img = new_png_from_image(image);
    TEST_ASSERT_NOT_NULL_MESSAGE(ref, "could not create ref png");
    TEST_ASSERT_NOT_NULL_MESSAGE(img, "could not create img png");
    TEST_ASSERT_EQUAL_INT(
        0,
        png_to_file(
            ref, TEST_OUTPUT_DIR "/generic_display_circle_bresenham_ref.png"));
    TEST_ASSERT_EQUAL_INT(
        0,
        png_to_file(
            img, TEST_OUTPUT_DIR "/generic_display_circle_bresenham_img.png"));
    TEST_ASSERT_EQUAL_INT_MESSAGE(0, ret, "failed to draw rectangle");

    // compare the images
    // // note: bresenham is not expected to match with libgd
  }

  // clean up
  release_image(reference);
  release_image(image);
  release_libgd_generic_interface(interface);
  release_png(ref);
  release_png(img);
}

void test_generic_display_circle_ellipse(void) {
  uext_t width = 30;
  uext_t height = 30;

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

    // draw a rectangle
    int color = truecolor_random_color();
    int ret = simultaneous_generic_display_circle_ellipse(
        reference, interface, &color, 0, height / 2, 10);

    // save images to png
    ref = new_png_from_image(reference);
    img = new_png_from_image(image);
    TEST_ASSERT_NOT_NULL_MESSAGE(ref, "could not create ref png");
    TEST_ASSERT_NOT_NULL_MESSAGE(img, "could not create img png");
    TEST_ASSERT_EQUAL_INT(
        0, png_to_file(
               ref, TEST_OUTPUT_DIR "/generic_display_circle_ellipse_ref.png"));
    TEST_ASSERT_EQUAL_INT(
        0, png_to_file(
               img, TEST_OUTPUT_DIR "/generic_display_circle_ellipse_img.png"));
    TEST_ASSERT_EQUAL_INT_MESSAGE(0, ret, "failed to draw rectangle");

    // compare the images
    TEST_ASSERT_EQUAL_INT(0, compare_image(reference, image));
  }

  // clean up
  release_image(reference);
  release_image(image);
  release_libgd_generic_interface(interface);
  release_png(ref);
  release_png(img);
}

void test_generic_display_ellipse(void) {
  TEST_IGNORE_MESSAGE("not implemented");
}

void test_generic_display_line_case1(void) {
  uext_t width = 8;
  uext_t height = 8;

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

    // draw a line
    int color = truecolor_random_color();
    int ret = simultaneous_generic_display_line(
        reference, interface, &color, 1, 1, 0, 6);

    // save images to png
    ref = new_png_from_image(reference);
    img = new_png_from_image(image);
    TEST_ASSERT_NOT_NULL_MESSAGE(ref, "could not create ref png");
    TEST_ASSERT_NOT_NULL_MESSAGE(img, "could not create img png");
    TEST_ASSERT_EQUAL_INT(
        0, png_to_file(ref, TEST_OUTPUT_DIR "/generic_display_line_case1_ref.png"));
    TEST_ASSERT_EQUAL_INT(
        0, png_to_file(img, TEST_OUTPUT_DIR "/generic_display_line_case1_img.png"));
    TEST_ASSERT_EQUAL_INT_MESSAGE(0, ret, "failed to draw line");

    // compare the images
    TEST_ASSERT_EQUAL_INT(0, compare_image(reference, image));
  }

  // clean up
  release_image(reference);
  release_image(image);
  release_libgd_generic_interface(interface);
  release_png(ref);
  release_png(img);
}
