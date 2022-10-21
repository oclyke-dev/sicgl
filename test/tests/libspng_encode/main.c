#include "test_utils.h"

void setUp(void) {
  // set stuff up here
}

void tearDown(void) {
  // clean stuff up here
}

int main() {
  png_t* bm = new_png(75, 50);

  for (size_t y = 0; y < bm->height; ++y) {
    for (size_t x = 0; x < bm->width; ++x) {
      png_pixel_t* px = &bm->pixels[bm->width * y + x];
      px->r = 255;
      px->g = 0;
      px->b = 0;
      px->a = 255;
    }
  }

  png_to_file(bm, TEST_OUTPUT_DIR "/test.png");
  release_png(bm);

  return EXIT_SUCCESS;
}
