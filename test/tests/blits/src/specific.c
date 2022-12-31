#include "utils.h"

static void test_blit_coords(int u, int v) {
  uext_t width = 20;
  uext_t height = 20;

  gdImage* image = NULL;
  screen_t* screen = NULL;
  screen_t* sprite_screen = NULL;
  interface_t* interface = NULL;
  png_t* img = NULL;

  if (TEST_PROTECT()) {
    // create specific interface
    screen = new_screen_extent(width, height, 0, 0);
    interface = new_libgd_interface(screen, NULL, 0);
    TEST_ASSERT_NOT_NULL_MESSAGE(screen, "could not create screen");
    TEST_ASSERT_NOT_NULL_MESSAGE(interface, "could not create interface");

    // create sprite buffer information
    int color = truecolor_random_color();
    sprite_screen = new_screen_extent(3, 3, u, v);
    color_t sprite[] = {
        color, 0, color, 0, color, 0, color, 0, color,
    };

    // blit
    int ret = sicgl_blit(interface, sprite_screen, sprite);
    image = new_image_from_libgd_specific_interface(interface);
    TEST_ASSERT_NOT_NULL_MESSAGE(image, "could not convert test image");

    // save images to png
    int filename_length =
        snprintf(NULL, 0, TEST_OUTPUT_DIR "/blit_%d_%d.png", u, v) + 1;
    char filename[filename_length];
    snprintf(
        filename, filename_length, TEST_OUTPUT_DIR "/blit_%d_%d.png", u, v);
    img = new_png_from_libgd_interface(interface);
    TEST_ASSERT_NOT_NULL_MESSAGE(img, "could not create img png");
    TEST_ASSERT_EQUAL_INT(0, png_to_file(img, filename));
    TEST_ASSERT_EQUAL_INT_MESSAGE(0, ret, "failed to blit");

  } else {
    release_image(image);
    release_screen(screen);
    release_screen(sprite_screen);
    release_libgd_interface(interface);
    release_png(img);
  }
}

void test_blit(void) {
  test_blit_coords(1, 1);
  test_blit_coords(1, 0);
  test_blit_coords(1, -1);
  test_blit_coords(0, -1);
  test_blit_coords(-1, -1);
  test_blit_coords(-1, 0);
  test_blit_coords(-1, 1);
  test_blit_coords(0, 0);
}
