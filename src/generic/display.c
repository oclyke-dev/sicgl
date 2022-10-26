#include "sicgl/generic.h"

/**
 * @brief Display-relative drawing functions.
 * Coordinates are taken in display frame.
 * As interfaces define their own display this means passing coordinates along
 * with no translation.
 *
 */

int sicgl_generic_display_line(
    generic_interface_t* interface, color_t color, ext_t u0, ext_t v0, ext_t u1,
    ext_t v1) {
  int ret = 0;
  ret = sicgl_generic_line(interface, color, u0, v0, u1, v1);
out:
  return ret;
}
