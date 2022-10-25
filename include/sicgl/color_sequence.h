#pragma once

#include <stddef.h>
#include <stdint.h>

typedef enum {
  SICGL_CS_STATIC,
  SICGL_CS_FORWARD,
  SICGL_CS_REVERSE,

  // helpers
  SICGL_CS_NUM_TYPES,
  SICGL_CS_UNKNOWN,
} color_sequence_type_e;

typedef struct _color_sequence_t {
  color_sequence_type_e type;
  size_t scale;  // how many pixels to draw with each color before advance

  size_t bpp;
  uint8_t* buffer;
  size_t length;
} color_sequence_t;

static inline size_t color_sequence_length_pixels(color_sequence_t* sequence) {
  size_t len = 0;
  if (NULL == sequence) {
    goto out;
  }
  len = sequence->length / sequence->bpp;
out:
  return len;
}

int color_sequence_set(
    color_sequence_t* sequence, color_sequence_type_e type, size_t bpp,
    uint8_t* buffer, size_t length);
