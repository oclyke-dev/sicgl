#pragma once

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

// this is a primitive interface for testing.
// colors are represented by single bytes.
typedef struct {
  size_t width;
  size_t height;
  uint8_t* memory;
} bytes_t;

static inline size_t bytes_length_bytes(bytes_t bytes) {
  return (bytes.height * bytes.width);
}

static inline size_t bytes_length_pixels(bytes_t bytes) {
  return bytes_length_bytes(bytes);
}

static inline size_t bytes_bpp(bytes_t bytes) {
  return 1;
}

static inline void release_bytes(bytes_t* bytes) {
  if (NULL != bytes) {
    free(bytes->memory);
  }
  free(bytes);
}

static inline bytes_t* new_bytes(size_t width, size_t height) {
  size_t length = width * height;
  bytes_t* bytes = malloc(sizeof(bytes_t));
  if (bytes == NULL) {
    goto out;
  }
  uint8_t* memory = (uint8_t*)malloc(length);
  if (memory == NULL) {
    release_bytes(bytes);
    bytes = NULL;
    goto out;
  }
  bytes->memory = memory;
  bytes->width = width;
  bytes->height = height;

out:
  return bytes;
}

static inline uint8_t bytes_random_color() {
  return (uint8_t)(rand() % 255);
}
