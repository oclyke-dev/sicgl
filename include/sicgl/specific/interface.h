#pragma once

#include <string.h>

#include "sicgl/color.h"
#include "sicgl/color_sequence.h"
#include "sicgl/display.h"
#include "sicgl/extent.h"
#include "sicgl/screen.h"

typedef struct _specific_interface_t {
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
  color_t color = 0;
  if (NULL == color_sequence) {
    goto out;
  }
  // todo: advance through the sequence according to the type and scale of the
  // sequence
  color = color_sequence->buffer[0];
out:
  return color;
}
