#pragma once

#include <stdint.h>

#include "gd.h"
#include "sicgl/extent.h"

#define TRUECOLOR_TRANSPARENT (127)
#define TRUECOLOR_OPAQUE (0)

static inline int truecolor_random_color() {
  uint8_t r = rand() % 255;
  uint8_t g = rand() % 255;
  uint8_t b = rand() % 255;
  return gdTrueColorAlpha(r, g, b, TRUECOLOR_OPAQUE);
}

gdImage* new_image(uext_t width, uext_t height);
void release_image(gdImage* image);

int compare_image(gdImage* reference, gdImage* image);
