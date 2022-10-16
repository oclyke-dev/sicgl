// utilities for testing
#pragma once

// #include <stdint.h>
// #include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "sicgl.h"

// this is a primitive interface for testing.
// colors are represented by single bytes.
typedef struct {
  size_t bpp;
  size_t length;
  size_t width;
  size_t height;
  uint8_t* memory;
} bytes_t;

static inline void bytes_free(bytes_t* bytes) { free(bytes); }

// offset within array for (u, v)
static inline size_t bytes_position(bytes_t* bytes, uext_t u, uext_t v) {
  return (bytes->width * v + u);
}

// sicgl generic interface functions
static inline void bytes_pixel(void* arg, color_t color, uext_t u, uext_t v) {
  bytes_t* bytes = (bytes_t*)arg;
  uint8_t* c = (uint8_t*)color;
  bytes->memory[bytes_position(bytes, u, v)] = *c;
}

static inline void bytes_hline(void* arg, color_t color, uext_t u0, uext_t v,
                               uext_t u1) {
  bytes_t* bytes = (bytes_t*)arg;
  uint8_t* c = (uint8_t*)color;

  int increment;
  uext_t distance;
  size_t offset;
  if (u0 < u1) {
    increment = 1;
    distance = u1 - u0 + 1;
    offset = bytes_position(bytes, u0, v);
  } else {
    increment = -1;
    distance = u0 - u1 + 1;
    offset = bytes_position(bytes, u1, v);
  }

  for (uext_t idu = 0; idu < distance; idu++) {
    bytes->memory[offset + idu] = *c;
  }
}

static inline void bytes_vline(void* arg, color_t color, uext_t u, uext_t v0,
                               uext_t v1) {
  bytes_t* bytes = (bytes_t*)arg;
  uint8_t* c = (uint8_t*)color;
  size_t width = bytes->width;

  uext_t distance;
  size_t offset;
  if (v0 < v1) {
    distance = v1 - v0 + 1;
    offset = bytes_position(bytes, u, v0);
  } else {
    distance = v0 - v1 + 1;
    offset = bytes_position(bytes, u, v1);
  }

  for (uext_t idv = 0; idv < distance; idv++) {
    bytes->memory[offset + (idv * width)] = *c;
  }
}

static inline void bytes_region(void* arg, color_t color, uext_t u0, uext_t v0,
                                uext_t u1, uext_t v1) {
  bytes_t* bytes = (bytes_t*)arg;
  uint8_t* c = (uint8_t*)color;
  size_t width = bytes->width;

  uext_t distance;
  uext_t voffset;
  if (v0 < v1) {
    distance = v1 - v0 + 1;
    voffset = v0;
  } else {
    distance = v0 - v1 + 1;
    voffset = v1;
  }

  for (uext_t idv = 0; idv < distance; idv++) {
    bytes_hline(arg, color, u0, voffset + idv, u1);
  }
}

static inline bytes_t* bytes_new(size_t width, size_t height) {
  size_t length = width * height;
  bytes_t* bytes = malloc(sizeof(bytes_t));
  if (bytes == NULL) {
    goto out;
  }
  uint8_t* memory = (uint8_t*)malloc(length);
  if (memory == NULL) {
    bytes_free(bytes);
    bytes = NULL;
    goto out;
  }
  bytes->memory = memory;
  bytes->length = length;
  bytes->width = width;
  bytes->height = height;
  bytes->bpp = 1;  // this is for compatibility with the specific api

out:
  return bytes;
}

static inline specific_interface_t* bytes_new_specific_interface(
    bytes_t* bytes) {
  specific_interface_t* intfc =
      (specific_interface_t*)malloc(sizeof(specific_interface_t));
  if (intfc == NULL) {
    goto out;
  }
  memset(intfc, 0U, sizeof(*intfc));

  // create easy defaults
  intfc->bpp = bytes->bpp;
  intfc->memory = bytes->memory;
  intfc->pixels = bytes->length;
  intfc->scratch = NULL;
  intfc->pixels_scratch = 0;

out:
  return intfc;
}

static inline screen_t* bytes_new_screen(bytes_t* bytes) {
  screen_t* screen = (screen_t*)malloc(sizeof(screen_t));
  if (screen == NULL) {
    goto out;
  }
  memset(screen, 0U, sizeof(*screen));
  screen->width = bytes->width;
  screen->height = bytes->height;
  screen->u0 = 0;
  screen->v0 = 0;
out:
  return screen;
}

static inline generic_interface_t* bytes_new_generic_interface(bytes_t* bytes,
                                                               bool full) {
  generic_interface_t* intfc =
      (generic_interface_t*)malloc(sizeof(generic_interface_t));
  if (intfc == NULL) {
    goto out;
  }
  memset(intfc, 0U, sizeof(*intfc));

  // create easy defaults
  intfc->arg = (void*)bytes;
  intfc->pixel = bytes_pixel;
  if (full) {
    intfc->hline = bytes_hline;
    intfc->vline = bytes_vline;
    intfc->region = bytes_region;
  }

out:
  return intfc;
}

static inline uint8_t bytes_random_color() { return (uint8_t)(rand() % 255); }
