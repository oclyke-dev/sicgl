#include <errno.h>
#include <stddef.h>

#include "sicgl/debug.h"
#include "sicgl/specific/interface.h"

void specific_hrun(
    specific_interface_t* interface, color_sequence_t* color_sequence, uext_t u,
    uext_t v, ext_t du) {
  color_t color = color_sequence_get_color(color_sequence);
  int increment = (du > 0) ? COLOR_SIZE_BYTES : -COLOR_SIZE_BYTES;
  int count = (du > 0) ? du : -du;
  uint8_t* p = interface->memory + COLOR_SIZE_BYTES * (interface->display.width * v + u);
  while (count-- > 0) {
    memcpy(p, &color, COLOR_SIZE_BYTES);
    p += increment;
  }
}

void specific_vrun(
    specific_interface_t* interface, color_sequence_t* color_sequence, uext_t u,
    uext_t v, ext_t dv) {
  color_t color = color_sequence_get_color(color_sequence);
  uext_t width = interface->display.width;
  int increment = (dv > 0) ? COLOR_SIZE_BYTES * width : -COLOR_SIZE_BYTES * width;
  int count = (dv > 0) ? dv : -dv;
  uint8_t* p = interface->memory + COLOR_SIZE_BYTES * (width * v + u);
  while (count-- > 0) {
    memcpy(p, &color, COLOR_SIZE_BYTES);
    p += increment;
  }
}

void specific_hline(
    specific_interface_t* interface, color_sequence_t* color_sequence,
    uext_t u0, uext_t v, uext_t u1) {
  color_t color = color_sequence_get_color(color_sequence);
  int increment;
  size_t distance;
  if (u0 < u1) {
    increment = COLOR_SIZE_BYTES;
    distance = u1 - u0 + 1;
  } else {
    increment = -COLOR_SIZE_BYTES;
    distance = u0 - u1 + 1;
  }

  uint8_t* p =
      interface->memory + COLOR_SIZE_BYTES * (interface->display.width * v + u0);
  for (size_t idx = 0; idx < distance; idx++) {
    memcpy(p, &color, COLOR_SIZE_BYTES);
    p += increment;
  }
}

void specific_vline(
    specific_interface_t* interface, color_sequence_t* color_sequence, uext_t u,
    uext_t v0, uext_t v1) {
  color_t color = color_sequence_get_color(color_sequence);
  int increment;
  size_t distance;
  if (v0 < v1) {
    increment = COLOR_SIZE_BYTES * interface->display.width;
    distance = v1 - v0 + 1;
  } else {
    increment = -COLOR_SIZE_BYTES * interface->display.width;
    distance = v0 - v1 + 1;
  }

  uint8_t* p =
      interface->memory + COLOR_SIZE_BYTES * (interface->display.width * v0 + u);
  for (size_t idv = 0; idv < distance; idv++) {
    memcpy(p, &color, COLOR_SIZE_BYTES);
    p += increment;
  }
}

void specific_diagonal(
    specific_interface_t* interface, color_sequence_t* color_sequence,
    uext_t u0, uext_t v0, ext_t diru, ext_t dirv, uext_t count) {
  int du, dv;
  color_t color = color_sequence_get_color(color_sequence);
  if (diru > 0) {
    du = COLOR_SIZE_BYTES;
  } else {
    du = -COLOR_SIZE_BYTES;
  }
  if (dirv > 0) {
    dv = COLOR_SIZE_BYTES * interface->display.width;
  } else {
    dv = -COLOR_SIZE_BYTES * interface->display.width;
  }

  uint8_t* p =
      interface->memory + COLOR_SIZE_BYTES * (interface->display.width * v0 + u0);
  for (uext_t idx = 0; idx < count; idx++) {
    memcpy(p, &color, COLOR_SIZE_BYTES);
    p += du;
    p += dv;
  }
}

void specific_region(
    specific_interface_t* interface, color_sequence_t* color_sequence,
    uext_t u0, uext_t v0, uext_t u1, uext_t v1) {
  color_t color = color_sequence_get_color(color_sequence);
  size_t du;
  size_t dv;
  uint8_t* p = interface->memory;
  size_t offset;  // length
  size_t scratch_length =
      interface->scratch_length / COLOR_SIZE_BYTES;  // compute available length in scratch
  uint8_t* scratch = interface->scratch;
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
        memcpy(interface->memory + COLOR_SIZE_BYTES * offset, &color, COLOR_SIZE_BYTES);
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
    if (wu > du) {
      wu = du;
    }
    // copy color into scratch buffer
    for (size_t idu = 0; idu < wu; idu++) {
      memcpy(scratch + COLOR_SIZE_BYTES * idu, &color, COLOR_SIZE_BYTES);
    }
    // copy scratch buffer into each
    while (du > 0) {
      if (wu > du) {
        wu = du;
      }
      for (size_t idv = 0; idv < dv; idv++) {
        memcpy(p, scratch, wu);
        p += COLOR_SIZE_BYTES * width;  // adv. to next row
      }
      du -= wu;
      // adv. to next starting column and back to first row
      p += COLOR_SIZE_BYTES * (wu - width * dv);
    }
  }
}
