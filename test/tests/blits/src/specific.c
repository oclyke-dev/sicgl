#include "utils.h"

void test_specific_blit(void) {
  uext_t width = 20;
  uext_t height = 20;

  gdImage* image = NULL;
  screen_t* screen = NULL;
  specific_interface_t* interface = NULL;
  png_t* img = NULL;

  printf("here I am!\n");

  if (TEST_PROTECT()) {
    // create specific interface
    screen = new_screen_extent(width, height, 0, 0);
    interface = new_libgd_specific_interface(screen, NULL, 0);
    TEST_ASSERT_NOT_NULL_MESSAGE(screen, "could not create screen");
    TEST_ASSERT_NOT_NULL_MESSAGE(interface, "could not create interface");

    // create sprite buffer information
    int color = truecolor_random_color();
    screen_t* sprite_screen = new_screen_extent(3, 3, 0, 0);

    screen_t intersection;
    screen_intersect(&intersection, sprite_screen, &interface->screen);

    printf("interface screen:\n");
    show_screen(&interface->screen);

    printf("sprite screen:\n");
    show_screen(sprite_screen);

    printf("intersection screen:\n");
    show_screen(&intersection);


    // printf("screen width: %d\n", sprite_screen->width);
    // printf("screen height: %d\n", sprite_screen->height);

    // printf("screen width: %d\n", interface->screen.width);
    // printf("screen height: %d\n", interface->screen.height);

    color_t sprite[] = {
        color, 0, color, 0, color, 0, color, 0, color,
    };

    // blit
    int ret = sicgl_specific_blit(interface, sprite_screen, sprite);
    image = new_image_from_libgd_specific_interface(interface);
    TEST_ASSERT_NOT_NULL_MESSAGE(image, "could not convert test image");

    // save images to png
    img = new_png_from_libgd_specific_interface(interface);
    TEST_ASSERT_NOT_NULL_MESSAGE(img, "could not create img png");
    TEST_ASSERT_EQUAL_INT(
        0, png_to_file(img, TEST_OUTPUT_DIR "/specific_blit_img.png"));
    TEST_ASSERT_EQUAL_INT_MESSAGE(0, ret, "failed to blit");

  } else {
    release_image(image);
    release_screen(screen);
    release_libgd_specific_interface(interface);
    release_png(img);
  }
}
