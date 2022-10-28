#include <errno.h>
#include <stddef.h>

#include "sicgl/debug.h"
#include "sicgl/naive.h"
#include "sicgl_generic.h"

void sicgl_generic_pixel(
    generic_interface_t* interface, color_t color, uext_t u, uext_t v) {
  // pixel must exist
  interface->pixel(interface->arg, color, u, v);
}

void sicgl_generic_hrun(
    generic_interface_t* interface, color_t color, uext_t u, uext_t v,
    ext_t du) {
  if (du == 0) {
    interface->pixel(interface->arg, color, u, v);
  }
  if (interface->hline) {
    interface->hline(interface->arg, color, u, v, u + du - 1);
  } else {
    naive_hline(interface, color, u, v, u + du - 1);
  }
}

void sicgl_generic_vrun(
    generic_interface_t* interface, color_t color, uext_t u, uext_t v,
    ext_t dv) {
  if (dv == 0) {
    interface->pixel(interface->arg, color, u, v);
  }
  if (interface->hline) {
    interface->vline(interface->arg, color, u, v, v + dv - 1);
  } else {
    naive_vline(interface, color, u, v, v + dv - 1);
  }
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
    generic_interface_t* interface, color_t color, uext_t u, uext_t v0,
    uext_t v1) {
  if (interface->vline) {
    interface->vline(interface->arg, color, u, v0, v1);
  } else {
    naive_vline(interface, color, u, v0, v1);
  }
}

void sicgl_generic_diagonal(
    generic_interface_t* interface, color_t color, uext_t u0, uext_t v0,
    ext_t diru, ext_t dirv, uext_t count) {
  uext_t u = u0;
  uext_t v = v0;
  int du, dv;

  if (diru > 0) {
    du = 1;
  } else {
    du = -1;
  }
  if (dirv > 0) {
    dv = 1;
  } else {
    dv = -1;
  }

  for (uext_t idx = 0; idx < count; idx++) {
    interface->pixel(interface->arg, color, u, v);
    u += du;
    v += dv;
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
