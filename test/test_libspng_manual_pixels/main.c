#include "test_utils.h"

void setUp(void) {
  // set stuff up here
}

void tearDown(void) {
  // clean stuff up here
}

int main() {
  bitmap_t* bm = bitmap_new(255, 255);

  for (size_t y = 0; y < bm->height; ++y) {
    for (size_t x = 0; x < bm->width; ++x) {
      bitmap_pixel_t* px = &bm->pixels[bm->width * y + x];
      px->r = y;
      px->g = 0;
      px->b = x;
      px->a = 255;
    }
  }

  bitmap_to_file(bm, "test.png");
  bitmap_free(bm);

  return EXIT_SUCCESS;
}
