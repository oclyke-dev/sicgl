#include "sicgl/compositors.h"

void compositor_direct_set(
    color_t* source, color_t* destination, size_t width, void* args) {
  for (size_t idx = 0; idx < width; idx++) {
    destination[idx] = source[idx];
  }
}

void compositor_direct_clear(
    color_t* source, color_t* destination, size_t width, void* args) {
  for (size_t idx = 0; idx < width; idx++) {
    destination[idx] = 0x00;
  }
}

void compositor_direct_none(
    color_t* source, color_t* destination, size_t width, void* args) {}
