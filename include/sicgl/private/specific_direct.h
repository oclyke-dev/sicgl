#pragma once

#include "sicgl/specific/interface.h"

static inline void sicgl_specific_pixel(
    specific_interface_t* interface, color_t color, ext_t u, ext_t v) {
  if (NULL == interface->screen) {
    goto out;
  }
  size_t offset = interface->screen->width * v + u;
  interface->memory[offset] = color;
out:
  return;
}

void specific_hrun(
    specific_interface_t* interface, color_t color, uext_t u, uext_t v,
    ext_t du);
void specific_vrun(
    specific_interface_t* interface, color_t color, uext_t u, uext_t v,
    ext_t dv);
void specific_hline(
    specific_interface_t* interface, color_t color, uext_t u0, uext_t v,
    uext_t u1);
void specific_vline(
    specific_interface_t* interface, color_t color, uext_t u, uext_t v0,
    uext_t v1);
void specific_diagonal(
    specific_interface_t* interface, color_t color, uext_t u0, uext_t v0,
    ext_t diru, ext_t dirv, uext_t count);
void specific_region(
    specific_interface_t* interface, color_t color, uext_t u0, uext_t v0,
    uext_t u1, uext_t v1);
