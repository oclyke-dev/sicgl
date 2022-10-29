#pragma once

#include "sicgl/specific.h"

static inline void sicgl_specific_pixel(
    specific_interface_t* interface, color_sequence_t* color_sequence, ext_t u,
    ext_t v) {
  color_t color = color_sequence_get_color(color_sequence);
  uint8_t* p =
      interface->memory + interface->bpp * (interface->display.width * v + u);
  memcpy(p, color, interface->bpp);
}

void specific_hrun(
    specific_interface_t* interface, color_sequence_t* color_sequence, uext_t u,
    uext_t v, ext_t du);
void specific_vrun(
    specific_interface_t* interface, color_sequence_t* color_sequence, uext_t u,
    uext_t v, ext_t dv);
void specific_hline(
    specific_interface_t* interface, color_sequence_t* color_sequence,
    uext_t u0, uext_t v, uext_t u1);
void specific_vline(
    specific_interface_t* interface, color_sequence_t* color_sequence, uext_t u,
    uext_t v0, uext_t v1);
void specific_diagonal(
    specific_interface_t* interface, color_sequence_t* color_sequence,
    uext_t u0, uext_t v0, ext_t diru, ext_t dirv, uext_t count);
void specific_region(
    specific_interface_t* interface, color_sequence_t* color_sequence,
    uext_t u0, uext_t v0, uext_t u1, uext_t v1);
