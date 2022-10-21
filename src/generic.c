#include <stdio.h>

#include "sicgl.h"
#include "sicgl/naive.h"

void sicgl_generic_pixel(
    generic_interface_t* interface, color_t color, uext_t u, uext_t v) {
  // pixel must exist
  interface->pixel(interface->arg, color, u, v);
}

void sicgl_generic_hline(
    generic_interface_t* interface, color_t color, uext_t u0, uext_t v,
    uext_t u1) {
  if (interface->hline) {
    interface->hline(interface->arg, color, u0, v, u1);
  } else {
    naive_hline(interface, color, u0, v, u1);
  }
}

void sicgl_generic_vline(
    generic_interface_t* interface, color_t color, uext_t u0, uext_t v,
    uext_t u1) {
  if (interface->vline) {
    interface->vline(interface->arg, color, u0, v, u1);
  } else {
    naive_vline(interface, color, u0, v, u1);
  }
}

void sicgl_generic_region(
    generic_interface_t* interface, color_t color, uext_t u0, uext_t v0,
    uext_t u1, uext_t v1) {
  if (interface->region) {
    interface->region(interface->arg, color, u0, v0, u1, v1);
  } else {
    naive_region(interface, color, u0, v0, u1, v1);
  }
}
