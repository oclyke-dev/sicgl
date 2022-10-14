#include "sicgl/specific.h"

#include <stddef.h>

void sicgl_specific_hline(specific_interface_t* interface, screen_t* screen, color_t color, uext_t u0, uext_t v, uext_t u1) {
  int increment;
  size_t distance;
  size_t bpp = interface->bpp;
  if (u0 < u1) {
    increment = bpp;
    distance = u1 - u0 + 1;
  } else {
    increment = -bpp;
    distance = u0 - u1 + 1;
  }

  uint8_t* p = interface->memory + screen->width * v + u0;
  for (size_t idx = 0; idx < distance; idx++) {
    memcpy(p, color, bpp);
    p += increment;
  }
}

void sicgl_specific_vline(specific_interface_t* interface, screen_t* screen, color_t color, uext_t u, uext_t v0, uext_t v1) {
  int increment;
  size_t distance;
  size_t bpp = interface->bpp;
  if (v0 < v1) {
    increment = bpp * screen->width;
    distance = v1 - v0 + 1;
  } else {
    increment = -bpp * screen->width;
    distance = v0 - v1 + 1;
  }

  uint8_t* p = interface->memory + screen->width * v0 + u;
  for (size_t idv = 0; idv < distance; idv++) {
    memcpy(p, color, bpp);
    p += increment;
  }
}

void sicgl_specific_region(specific_interface_t* interface, screen_t* screen, color_t color, uext_t u0, uext_t v0, uext_t u1, uext_t v1) {
  size_t du;
  size_t dv;
  size_t bpp = interface->bpp;
  uint8_t* p = interface->memory;
  size_t scratch_length = interface->pixels_scratch;
  uint8_t* scratch = interface->scratch;
  uext_t width = screen->width;

  // compute values
  if (u0 < u1) {
    du = u1 - u0 + 1;
    p += u0;
  } else {
    du = u0 - u1 + 1;
    p += u1;
  }
  if (v0 < v1) {
    dv = u1 - u0 + 1;
    p += width * v0;
  } else {
    dv = u0 - u1 + 1;
    p += width * u1;
  }

  if (scratch_length == 0) {
    // use naive pixel-by-pixel implementation
    for (size_t idv = 0; idv < dv; idv++) {
      for (size_t idu = 0; idu < du; idu++) {
        memcpy(p, color, bpp);
        p += bpp;
      }
      p += bpp * (width - du); // adv to next row and back to starting column
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
      memcpy(scratch + bpp * idu, color, bpp);
    }
    // copy scratch buffer into each 
    while (du > 0) {
      if (wu > du) {
        wu = du;
      }
      for (size_t idv = 0; idv < dv; idv++) {
        memcpy(p, scratch, wu);
        p += bpp * width; // adv. to next row
      }
      du -= wu;
      p += bpp * (wu - width * dv); // adv. to next starting column and back to first row
    }
  }
}
