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
