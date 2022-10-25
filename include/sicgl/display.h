#pragma once

#include "sicgl/extent.h"

// boundaries of a physical display
typedef struct _display_t {
  // size of the display, pixels
  uext_t width;
  uext_t height;

  // location of the display in global coordinates
  ext_t lu;
  ext_t lv;
} display_t;

int display_set(
    display_t* display, uext_t width, uext_t height, ext_t lu, ext_t lv);
