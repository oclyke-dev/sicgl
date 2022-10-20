#pragma once

#include <stdint.h>

// colors are user-defined
typedef void* color_t;

// physical extents are large signed/unsigned integers
typedef int32_t ext_t;
typedef uint32_t uext_t;

// a screen which exists within the global pixel space
typedef struct _screen_t {
  uext_t width;
  uext_t height;
  ext_t u0;
  ext_t v0;
} screen_t;
