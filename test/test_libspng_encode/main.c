#include "bitmap_utils.h"

int main() {
  bitmap_t* bm = bitmap_new(75, 50);

  for (size_t y = 0; y < bm->height; ++y) {
    for (size_t x = 0; x < bm->width; ++x) {
      bitmap_pixel_t* px = &bm->pixels[bm->width * y + x];
      px->r = 255;
      px->g = 0;
      px->b = 0;
      px->a = 255;
    }
  }

  bitmap_to_file(bm, "test.png");
  bitmap_free(bm);

  return EXIT_SUCCESS;
}
