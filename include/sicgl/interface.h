#pragma once

#include <string.h>

#include "sicgl/color.h"
#include "sicgl/color_sequence.h"
#include "sicgl/extent.h"
#include "sicgl/screen.h"

typedef struct _interface_t {
  screen_t* screen;  // geometrical display info
  color_t* memory;   // pointer to start of specific memory
  size_t length;     // memory length in pixels
} interface_t;

color_t sicgl_interface_get_pixel_offset(interface_t* interface, uext_t offset);
color_t sicgl_interface_get_pixel(interface_t* interface, uext_t u, uext_t v);
