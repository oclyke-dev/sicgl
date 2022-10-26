#include "sicgl/screen.h"
#include "utils.h"

void test_generic_naive_pixel(void) {
  uext_t width = 3;
  uext_t height = 3;

  gdImage* reference;
  gdImage* image;
  generic_interface_t* interface;
  color_sequence_t* color_sequence;
  png_t* ref;
  png_t* img;

  if (TEST_PROTECT()) {
    // create images
    reference = new_image(width, height);
    image = new_image(width, height);
    TEST_ASSERT_NOT_NULL_MESSAGE(
        reference, "could not allocate reference image");
    TEST_ASSERT_NOT_NULL_MESSAGE(image, "could not allocate test image");

    // create specific interface
    interface = new_libgd_generic_interface_naive(image);
    TEST_ASSERT_NOT_NULL_MESSAGE(interface, "could not create interface");

    // draw a pixel
    int color = truecolor_random_color();
    int ret = simultaneous_generic_pixel(reference, interface, &color, 1, 1);

    // save images to png
    ref = new_png_from_image(reference);
    img = new_png_from_image(image);
    TEST_ASSERT_NOT_NULL_MESSAGE(ref, "could not create ref png");
    TEST_ASSERT_NOT_NULL_MESSAGE(img, "could not create img png");
    TEST_ASSERT_EQUAL_INT(
        0, png_to_file(ref, TEST_OUTPUT_DIR "/generic_naive_pixel_ref.png"));
    TEST_ASSERT_EQUAL_INT(
        0, png_to_file(img, TEST_OUTPUT_DIR "/generic_naive_pixel_img.png"));
    TEST_ASSERT_EQUAL_INT_MESSAGE(0, ret, "failed to draw pixel");

    // compare the images
    TEST_ASSERT_EQUAL_INT(0, compare_image(reference, image));

  } else {
    release_image(reference);
    release_image(image);
    release_libgd_generic_interface(interface);
    release_color_sequence(color_sequence);
    release_png(ref);
    release_png(img);
  }
}

void test_generic_naive_hline(void) {
  uext_t width = 30;
  uext_t height = 3;

  gdImage* reference;
  gdImage* image;
  screen_t* screen;
  generic_interface_t* interface;
  color_sequence_t* color_sequence;
  png_t* ref;
  png_t* img;

  if (TEST_PROTECT()) {
    // create images
    reference = new_image(width, height);
    image = new_image(width, height);
    TEST_ASSERT_NOT_NULL_MESSAGE(
        reference, "could not allocate reference image");
    TEST_ASSERT_NOT_NULL_MESSAGE(image, "could not allocate test image");

    // create specific interface
    interface = new_libgd_generic_interface_naive(image);
    TEST_ASSERT_NOT_NULL_MESSAGE(interface, "could not create interface");

    // draw a hline
    int color = truecolor_random_color();
    int ret =
        simultaneous_generic_hline(reference, interface, &color, 1, 1, 28, 1);

    // save images to png
    ref = new_png_from_image(reference);
    img = new_png_from_image(image);
    TEST_ASSERT_NOT_NULL_MESSAGE(ref, "could not create ref png");
    TEST_ASSERT_NOT_NULL_MESSAGE(img, "could not create img png");
    TEST_ASSERT_EQUAL_INT(
        0, png_to_file(ref, TEST_OUTPUT_DIR "/generic_naive_hline_ref.png"));
    TEST_ASSERT_EQUAL_INT(
        0, png_to_file(img, TEST_OUTPUT_DIR "/generic_naive_hline_img.png"));
    TEST_ASSERT_EQUAL_INT_MESSAGE(0, ret, "failed to draw hline");

    // compare the images
    TEST_ASSERT_EQUAL_INT(0, compare_image(reference, image));

  } else {
    release_image(reference);
    release_image(image);
    release_libgd_generic_interface(interface);
    release_color_sequence(color_sequence);
    release_png(ref);
    release_png(img);
  }
}

void test_generic_naive_vline(void) {
  uext_t width = 3;
  uext_t height = 30;

  gdImage* reference;
  gdImage* image;
  screen_t* screen;
  generic_interface_t* interface;
  color_sequence_t* color_sequence;
  png_t* ref;
  png_t* img;

  if (TEST_PROTECT()) {
    // create images
    reference = new_image(width, height);
    image = new_image(width, height);
    TEST_ASSERT_NOT_NULL_MESSAGE(
        reference, "could not allocate reference image");
    TEST_ASSERT_NOT_NULL_MESSAGE(image, "could not allocate test image");

    // create specific interface
    interface = new_libgd_generic_interface_naive(image);
    TEST_ASSERT_NOT_NULL_MESSAGE(interface, "could not create interface");

    // draw a vline
    int color = truecolor_random_color();
    int ret =
        simultaneous_generic_vline(reference, interface, &color, 1, 1, 1, 28);

    // save images to png
    ref = new_png_from_image(reference);
    img = new_png_from_image(image);
    TEST_ASSERT_NOT_NULL_MESSAGE(ref, "could not create ref png");
    TEST_ASSERT_NOT_NULL_MESSAGE(img, "could not create img png");
    TEST_ASSERT_EQUAL_INT(
        0, png_to_file(ref, TEST_OUTPUT_DIR "/generic_naive_vline_ref.png"));
    TEST_ASSERT_EQUAL_INT(
        0, png_to_file(img, TEST_OUTPUT_DIR "/generic_naive_vline_img.png"));
    TEST_ASSERT_EQUAL_INT_MESSAGE(0, ret, "failed to draw vline");

    // compare the images
    TEST_ASSERT_EQUAL_INT(0, compare_image(reference, image));

  } else {
    release_image(reference);
    release_image(image);
    release_libgd_generic_interface(interface);
    release_color_sequence(color_sequence);
    release_png(ref);
    release_png(img);
  }
}

void test_generic_naive_region(void) {
  uext_t width = 30;
  uext_t height = 30;

  gdImage* reference;
  gdImage* image;
  screen_t* screen;
  generic_interface_t* interface;
  color_sequence_t* color_sequence;
  png_t* ref;
  png_t* img;

  if (TEST_PROTECT()) {
    // create images
    reference = new_image(width, height);
    image = new_image(width, height);
    TEST_ASSERT_NOT_NULL_MESSAGE(
        reference, "could not allocate reference image");
    TEST_ASSERT_NOT_NULL_MESSAGE(image, "could not allocate test image");

    // create specific interface
    interface = new_libgd_generic_interface_naive(image);
    TEST_ASSERT_NOT_NULL_MESSAGE(interface, "could not create interface");

    // draw a region
    int color = truecolor_random_color();
    int ret =
        simultaneous_generic_region(reference, interface, &color, 1, 1, 28, 28);

    // save images to png
    ref = new_png_from_image(reference);
    img = new_png_from_image(image);
    TEST_ASSERT_NOT_NULL_MESSAGE(ref, "could not create ref png");
    TEST_ASSERT_NOT_NULL_MESSAGE(img, "could not create img png");
    TEST_ASSERT_EQUAL_INT(
        0, png_to_file(ref, TEST_OUTPUT_DIR "/generic_naive_region_ref.png"));
    TEST_ASSERT_EQUAL_INT(
        0, png_to_file(img, TEST_OUTPUT_DIR "/generic_naive_region_img.png"));
    TEST_ASSERT_EQUAL_INT_MESSAGE(0, ret, "failed to draw region");

    // compare the images
    TEST_ASSERT_EQUAL_INT(0, compare_image(reference, image));

  } else {
    release_image(reference);
    release_image(image);
    release_libgd_generic_interface(interface);
    release_color_sequence(color_sequence);
    release_png(ref);
    release_png(img);
  }
}
