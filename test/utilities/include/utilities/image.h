#pragma once

#include <stdint.h>

#include "gd.h"

#define TRUECOLOR_TRANSPARENT (127)
#define TRUECOLOR_OPAQUE (0)

static inline int truecolor_random_color() {
  uint8_t r = rand() % 255;
  uint8_t g = rand() % 255;
  uint8_t b = rand() % 255;
  uint8_t a = 255;
  return gdTrueColorAlpha(r, g, b, TRUECOLOR_OPAQUE);
}

int image_to_file(gdImage* image, char const* path);
