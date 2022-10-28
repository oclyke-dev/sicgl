#pragma once

#include <string.h>

#include "sicgl/color.h"
#include "sicgl/color_sequence.h"
#include "sicgl/display.h"
#include "sicgl/extent.h"
#include "sicgl/screen.h"

typedef struct _specific_interface_t {
  size_t bpp;         // size of color_t in bytes
  display_t display;  // hardware display information
  screen_t screen;    // display information represented as screen

  // display memory
  uint8_t* memory;  // pointer to start of specific memory
  size_t length;    // memory length in bytes

  // scratch space
  uint8_t* scratch;       // memory for scratch space
  size_t scratch_length;  // number of bytes in scratch
} specific_interface_t;

static inline color_t color_sequence_get_color(
    color_sequence_t* color_sequence) {
  color_t color = NULL;
  if (NULL == color_sequence) {
    goto out;
  }
  // todo: advance through the sequence according to the type and scale of the
  // sequence
  color = color_sequence->buffer;
out:
  return color;
}

static inline void sicgl_specific_pixel(
    specific_interface_t* interface, color_sequence_t* color_sequence, ext_t u,
    ext_t v) {
  color_t color = color_sequence_get_color(color_sequence);
  uint8_t* p =
      interface->memory + interface->bpp * (interface->display.width * v + u);
  memcpy(p, color, interface->bpp);
}

void sicgl_specific_hrun(
    specific_interface_t* interface, color_sequence_t* color_sequence, uext_t u,
    uext_t v, ext_t du);
void sicgl_specific_vrun(
    specific_interface_t* interface, color_sequence_t* color_sequence, uext_t u,
    uext_t v, ext_t dv);
void sicgl_specific_hline(
    specific_interface_t* interface, color_sequence_t* color_sequence,
    uext_t u0, uext_t v, uext_t u1);
void sicgl_specific_vline(
    specific_interface_t* interface, color_sequence_t* color_sequence, uext_t u,
    uext_t v0, uext_t v1);
void sicgl_specific_diagonal(
    specific_interface_t* interface, color_sequence_t* color_sequence,
    uext_t u0, uext_t v0, ext_t diru, ext_t dirv, uext_t count);
void sicgl_specific_region(
    specific_interface_t* interface, color_sequence_t* color_sequence,
    uext_t u0, uext_t v0, uext_t u1, uext_t v1);
