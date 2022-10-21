#pragma once

#include <string.h>

#include "sicgl/types.h"

typedef struct _specific_interface_t {
  size_t bpp;  // size of color_t in bytes

  // display memory
  uint8_t* memory;  // pointer to start of specific memory
  size_t length;    // memory length in bytes

  // scratch space
  uint8_t* scratch;       // memory for scratch space
  size_t scratch_length;  // number of bytes in scratch
} specific_interface_t;

static inline void sicgl_specific_pixel(
    specific_interface_t* interface, screen_t* screen, color_t color, ext_t u,
    ext_t v) {
  uint8_t* p = interface->memory + interface->bpp * (screen->width * v + u);
  memcpy(p, color, interface->bpp);
}

void sicgl_specific_hline(
    specific_interface_t* interface, screen_t* screen, color_t color, uext_t u0,
    uext_t v, uext_t u1);
void sicgl_specific_vline(
    specific_interface_t* interface, screen_t* screen, color_t color, uext_t u,
    uext_t v0, uext_t v1);
void sicgl_specific_region(
    specific_interface_t* interface, screen_t* screen, color_t color, uext_t u0,
    uext_t v0, uext_t u1, uext_t v1);
