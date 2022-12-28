#pragma once

#include <string.h>

#include "sicgl/color.h"
#include "sicgl/color_sequence.h"
#include "sicgl/extent.h"
#include "sicgl/screen.h"

typedef struct _specific_interface_t {
  screen_t* screen;  // geometrical display info

  // display memory
  color_t* memory;  // pointer to start of specific memory
  size_t length;    // memory length in pixels

  // scratch space
  color_t* scratch;       // memory for scratch space
  size_t scratch_length;  // number of pixels in scratch
} specific_interface_t;
