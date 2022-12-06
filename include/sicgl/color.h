#pragma once

#include <stdint.h>

// colors are represented as a system int
// https://github.com/oclyke/sicgl/issues/24
// if necessary the user can change this definition
typedef int color_t;

// size of a color_t variable in bytes (must be positive... duh)
#define COLOR_SIZE_BYTES ((int)(sizeof(color_t) / sizeof(uint8_t)))
