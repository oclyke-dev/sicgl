#include "sicgl/specific.h"

/**
 * @brief Display-relative drawing functions.
 * Coordinates are taken in display frame.
 * As interfaces define their own display this means passing coordinates along
 * with no translation.
 *
 */

int sicgl_specific_display_line(
    specific_interface_t* interface, color_sequence_t* color_sequence, ext_t u0,
    ext_t v0, ext_t u1, ext_t v1) {
  int ret = 0;
  ret = sicgl_specific_line(interface, color_sequence, u0, v0, u1, v1);
out:
  return ret;
}
