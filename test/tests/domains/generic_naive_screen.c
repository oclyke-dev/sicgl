#include "sicgl/screen.h"
#include "utils.h"

void test_generic_naive_screen_pixel(void) {
  uext_t width = 3;
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

    // create a color sequence
    int color = truecolor_random_color();
    color_sequence = new_color_sequence(
        SICGL_CS_STATIC, sizeof(int), (uint8_t*)&color, sizeof(color));
    TEST_ASSERT_NOT_NULL_MESSAGE(
        color_sequence, "could not create color sequence");

    // create a screen
    screen = new_screen(0, 0, 0, 0, 1, 1);

    // draw a pixel
    int ret = simultaneous_generic_screen_pixel(
        reference, interface, screen, color_sequence, 0, 0);

    // save images to png
    ref = new_png_from_image(reference);
    img = new_png_from_image(image);
    TEST_ASSERT_NOT_NULL_MESSAGE(ref, "could not create ref png");
    TEST_ASSERT_NOT_NULL_MESSAGE(img, "could not create img png");
    TEST_ASSERT_EQUAL_INT(
        0, png_to_file(
               ref, TEST_OUTPUT_DIR "/generic_naive_screen_pixel_ref.png"));
    TEST_ASSERT_EQUAL_INT(
        0, png_to_file(
               img, TEST_OUTPUT_DIR "/generic_naive_screen_pixel_img.png"));
    TEST_ASSERT_EQUAL_INT_MESSAGE(0, ret, "failed to draw pixel");

    // compare the images
    TEST_ASSERT_EQUAL_INT(0, compare_image(reference, image));

  } else {
    release_image(reference);
    release_image(image);
    release_screen(screen);
    release_libgd_generic_interface(interface);
    release_color_sequence(color_sequence);
    release_png(ref);
    release_png(img);
  }
}

void test_generic_naive_screen_hline(void) {
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

    // create a color sequence
    int color = truecolor_random_color();
    color_sequence = new_color_sequence(
        SICGL_CS_STATIC, sizeof(int), (uint8_t*)&color, sizeof(color));
    TEST_ASSERT_NOT_NULL_MESSAGE(
        color_sequence, "could not create color sequence");

    // create a screen
    screen = new_screen(0, 0, 27, 0, 1, 1);

    // draw an hline
    int ret = simultaneous_generic_screen_hline(
        reference, interface, screen, color_sequence, 0, 0, 27, 0);

    // save images to png
    ref = new_png_from_image(reference);
    img = new_png_from_image(image);
    TEST_ASSERT_NOT_NULL_MESSAGE(ref, "could not create ref png");
    TEST_ASSERT_NOT_NULL_MESSAGE(img, "could not create img png");
    TEST_ASSERT_EQUAL_INT(
        0, png_to_file(
               ref, TEST_OUTPUT_DIR "/generic_naive_screen_hline_ref.png"));
    TEST_ASSERT_EQUAL_INT(
        0, png_to_file(
               img, TEST_OUTPUT_DIR "/generic_naive_screen_hline_img.png"));
    TEST_ASSERT_EQUAL_INT_MESSAGE(0, ret, "failed to draw hline");

    // compare the images
    TEST_ASSERT_EQUAL_INT(0, compare_image(reference, image));

  } else {
    release_image(reference);
    release_image(image);
    release_screen(screen);
    release_libgd_generic_interface(interface);
    release_color_sequence(color_sequence);
    release_png(ref);
    release_png(img);
  }
}

void test_generic_naive_screen_vline(void) {
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

    // create a color sequence
    int color = truecolor_random_color();
    color_sequence = new_color_sequence(
        SICGL_CS_STATIC, sizeof(int), (uint8_t*)&color, sizeof(color));
    TEST_ASSERT_NOT_NULL_MESSAGE(
        color_sequence, "could not create color sequence");

    // create a screen
    screen = new_screen(0, 0, 0, 27, 2, 1);

    // draw a vline
    int ret = simultaneous_generic_screen_vline(
        reference, interface, screen, color_sequence, 0, 0, 0, 27);

    // save images to png
    ref = new_png_from_image(reference);
    img = new_png_from_image(image);
    TEST_ASSERT_NOT_NULL_MESSAGE(ref, "could not create ref png");
    TEST_ASSERT_NOT_NULL_MESSAGE(img, "could not create img png");
    TEST_ASSERT_EQUAL_INT(
        0, png_to_file(
               ref, TEST_OUTPUT_DIR "/generic_naive_screen_vline_ref.png"));
    TEST_ASSERT_EQUAL_INT(
        0, png_to_file(
               img, TEST_OUTPUT_DIR "/generic_naive_screen_vline_img.png"));
    TEST_ASSERT_EQUAL_INT_MESSAGE(0, ret, "failed to draw vline");

    // compare the images
    TEST_ASSERT_EQUAL_INT(0, compare_image(reference, image));

  } else {
    release_image(reference);
    release_image(image);
    release_screen(screen);
    release_libgd_generic_interface(interface);
    release_color_sequence(color_sequence);
    release_png(ref);
    release_png(img);
  }
}

void test_generic_naive_screen_region(void) {
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

    // create a color sequence
    int color = truecolor_random_color();
    color_sequence = new_color_sequence(
        SICGL_CS_STATIC, sizeof(int), (uint8_t*)&color, sizeof(color));
    TEST_ASSERT_NOT_NULL_MESSAGE(
        color_sequence, "could not create color sequence");

    // create a screen
    screen = new_screen(0, 0, 27, 27, 1, 1);

    // draw a region
    int ret = simultaneous_generic_screen_region(
        reference, interface, screen, color_sequence, 0, 0, 27, 27);

    // save images to png
    ref = new_png_from_image(reference);
    img = new_png_from_image(image);
    TEST_ASSERT_NOT_NULL_MESSAGE(ref, "could not create ref png");
    TEST_ASSERT_NOT_NULL_MESSAGE(img, "could not create img png");
    TEST_ASSERT_EQUAL_INT(
        0, png_to_file(
               ref, TEST_OUTPUT_DIR "/generic_naive_screen_region_ref.png"));
    TEST_ASSERT_EQUAL_INT(
        0, png_to_file(
               img, TEST_OUTPUT_DIR "/generic_naive_screen_region_img.png"));
    TEST_ASSERT_EQUAL_INT_MESSAGE(0, ret, "failed to draw region");

    // compare the images
    TEST_ASSERT_EQUAL_INT(0, compare_image(reference, image));

  } else {
    release_image(reference);
    release_image(image);
    release_screen(screen);
    release_libgd_generic_interface(interface);
    release_color_sequence(color_sequence);
    release_png(ref);
    release_png(img);
  }
}
