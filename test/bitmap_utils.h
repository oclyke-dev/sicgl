// utilities for testing
#pragma once

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

/* values range from 0 to 255 */
typedef struct {
  uint8_t r;
  uint8_t g;
  uint8_t b;
  uint8_t a;
} bitmap_pixel_t;

typedef struct {
  size_t width;
  size_t height;
  bitmap_pixel_t pixels[];
} bitmap_t;

static inline bitmap_t* bitmap_new(size_t width, size_t height) {
  bitmap_t* bm =
      malloc(sizeof(bitmap_t) + sizeof(bitmap_pixel_t) * width * height);
  bm->width = width;
  bm->height = height;
  return bm;
}

static inline void bitmap_free(bitmap_t* bitmap) { free(bitmap); }

void bitmap_to_file(bitmap_t const* bitmap, char const* path);
