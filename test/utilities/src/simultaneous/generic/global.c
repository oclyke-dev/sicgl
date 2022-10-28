#include "utilities/simultaneous/generic/global.h"

#include <errno.h>

int simultaneous_generic_global_line(
    gdImage* image, generic_interface_t* interface, screen_t* screen, color_t color, ext_t u0,
    ext_t v0, ext_t u1, ext_t v1) {
  return -EINVAL;
}

int simultaneous_generic_global_rectangle(
    gdImage* image, generic_interface_t* interface, screen_t* screen, color_t color, ext_t u0,
    ext_t v0, ext_t u1, ext_t v1) {
  return -EINVAL;
}

int simultaneous_generic_global_circle(
    gdImage* image, generic_interface_t* interface, screen_t* screen, color_t color, ext_t u0,
    ext_t v0, ext_t radius) {
  return -EINVAL;
}

int simultaneous_generic_global_ellipse(
    gdImage* image, generic_interface_t* interface, screen_t* screen, color_t color, ext_t u0,
    ext_t v0, ext_t major, ext_t minor) {
  return -EINVAL;
}
