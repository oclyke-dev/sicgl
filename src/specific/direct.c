#include <errno.h>
#include <stddef.h>

#include "sicgl/debug.h"
#include "sicgl/specific/interface.h"

void specific_hrun(
    specific_interface_t* interface, color_t color, uext_t u, uext_t v,
    ext_t du) {
  int increment = (du > 0) ? 1 : -1;
  int count = (du > 0) ? du : -du;
  size_t offset = interface->display.width * v + u;
  while (count-- > 0) {
    interface->memory[offset] = color;
    offset += increment;
  }
}

void specific_vrun(
    specific_interface_t* interface, color_t color, uext_t u, uext_t v,
    ext_t dv) {
  uext_t width = interface->display.width;
  int increment = (dv > 0) ? width : -width;
  int count = (dv > 0) ? dv : -dv;
  size_t offset = width * v + u;
  while (count-- > 0) {
    interface->memory[offset] = color;
    offset += increment;
  }
}

void specific_hline(
    specific_interface_t* interface, color_t color, uext_t u0, uext_t v,
    uext_t u1) {
  int increment;
  size_t distance;
  if (u0 < u1) {
    increment = 1;
    distance = u1 - u0 + 1;
  } else {
    increment = -1;
    distance = u0 - u1 + 1;
  }

  size_t offset = interface->display.width * v + u0;
  for (size_t idx = 0; idx < distance; idx++) {
    interface->memory[offset] = color;
    offset += increment;
  }
}

void specific_vline(
    specific_interface_t* interface, color_t color, uext_t u, uext_t v0,
    uext_t v1) {
  int increment;
  size_t distance;
  if (v0 < v1) {
    increment = interface->display.width;
    distance = v1 - v0 + 1;
  } else {
    increment = -interface->display.width;
    distance = v0 - v1 + 1;
  }

  size_t offset = interface->display.width * v0 + u;
  for (size_t idv = 0; idv < distance; idv++) {
    interface->memory[offset] = color;
    offset += increment;
  }
}

void specific_diagonal(
    specific_interface_t* interface, color_t color, uext_t u0, uext_t v0,
    ext_t diru, ext_t dirv, uext_t count) {
  int du, dv;
  if (diru > 0) {
    du = 1;
  } else {
    du = -1;
  }
  if (dirv > 0) {
    dv = interface->display.width;
  } else {
    dv = -interface->display.width;
  }

  size_t offset = interface->display.width * v0 + u0;
  for (uext_t idx = 0; idx < count; idx++) {
    interface->memory[offset] = color;
    offset += du;
    offset += dv;
  }
}

void specific_region(
    specific_interface_t* interface, color_t color, uext_t u0, uext_t v0,
    uext_t u1, uext_t v1) {
  size_t du;
  size_t dv;
  color_t* p = interface->memory;
  size_t offset;
  size_t scratch_length = interface->scratch_length;
  color_t* scratch = interface->scratch;
  uext_t width = interface->display.width;

  // compute values
  if (u0 < u1) {
    offset = u0;
    du = u1 - u0 + 1;
  } else {
    offset = u1;
    du = u0 - u1 + 1;
  }
  if (v0 < v1) {
    offset += width * v0;
    dv = v1 - v0 + 1;
  } else {
    offset += width * v1;
    dv = v0 - v1 + 1;
  }

  if (scratch_length == 0) {
    // use naive pixel-by-pixel implementation
    for (size_t idv = 0; idv < dv; idv++) {
      for (size_t idu = 0; idu < du; idu++) {
        interface->memory[offset] = color;
        offset++;  // advance one column
      }
      offset += width;  // advance one row
      offset -= du;     // advance back to starting column
    }
  } else {
    // fill scratch buffer once then copy it repeatedly
    // this may be marginally faster than the above implementation
    // depending on whether the hardware supports fast memory copy
    size_t wu = scratch_length;
    size_t bpp = bytes_per_pixel();
    if (wu > du) {
      wu = du;
    }
    // copy color into scratch buffer
    for (size_t idu = 0; idu < wu; idu++) {
      scratch[idu] = color;
    }
    // copy scratch buffer into each
    while (du > 0) {
      if (wu > du) {
        wu = du;
      }
      for (size_t idv = 0; idv < dv; idv++) {
        memcpy(p, scratch, wu * bpp);
        p += width;  // adv. to next row
      }
      du -= wu;
      // adv. to next starting column and back to first row
      p += wu - width * dv;
    }
  }
}
