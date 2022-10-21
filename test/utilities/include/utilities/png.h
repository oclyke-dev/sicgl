#pragma once

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

#include "gd.h"
#include "sicgl.h"

// because truecolor alpha supports a smaller range of alphas the easiest move
// is to restrict the valid alpha values to [0, 127] for display these will be
// mapped back to the [0, 254] range but any comparisons will be done in the
// reduced range (to avoid off-by-one or incorrect range type)
#define PNG_ALPHA_FROM_TRUECOLOR_ALPHA(_tca) \
  (255 - (2 * ((_tca > 127) ? 127 : (_tca))))

/* values range from 0 to 255 */
typedef struct {
  uint8_t r;
  uint8_t g;
  uint8_t b;
  uint8_t a;
} png_pixel_t;

typedef struct {
  uext_t width;
  uext_t height;
  png_pixel_t pixels[];
} png_t;

static inline size_t png_length_pixels(png_t* png) {
  if (NULL == png) {
    return 0;
  }
  return (png->height * png->width);
}

static inline size_t png_length_bytes(png_t* png) {
  if (NULL == png) {
    return 0;
  }
  return (png->height * png->width) * sizeof(png_pixel_t);
}

static inline size_t png_compare_len_bytes(png_t* png0, png_t* png1) {
  size_t len0 = png_length_bytes(png0);
  size_t len1 = png_length_bytes(png1);
  return (len0 < len1) ? len0 : len1;
}

// color tools
png_pixel_t png_color(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
png_pixel_t png_color_random(void);

// png creation tools
png_t* new_png(uext_t width, uext_t height);
void release_png(png_t* png);

// output tools
png_t* new_png_from_image(gdImage* image);
int png_to_file(png_t const* png, char const* path);
