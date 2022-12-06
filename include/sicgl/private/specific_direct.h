#pragma once

#include "sicgl/specific/interface.h"

static inline void sicgl_specific_pixel(
    specific_interface_t* interface, color_t color, ext_t u,
    ext_t v) {
  uint8_t* p =
      interface->memory + COLOR_SIZE_BYTES * (interface->display.width * v + u);
  memcpy(p, &color, COLOR_SIZE_BYTES);
}

void specific_hrun(
    specific_interface_t* interface, color_t color, uext_t u,
    uext_t v, ext_t du);
void specific_vrun(
    specific_interface_t* interface, color_t color, uext_t u,
    uext_t v, ext_t dv);
void specific_hline(
    specific_interface_t* interface, color_t color,
    uext_t u0, uext_t v, uext_t u1);
void specific_vline(
    specific_interface_t* interface, color_t color, uext_t u,
    uext_t v0, uext_t v1);
void specific_diagonal(
    specific_interface_t* interface, color_t color,
    uext_t u0, uext_t v0, ext_t diru, ext_t dirv, uext_t count);
void specific_region(
    specific_interface_t* interface, color_t color,
    uext_t u0, uext_t v0, uext_t u1, uext_t v1);
