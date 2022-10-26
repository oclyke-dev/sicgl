#include "utilities/simultaneous/generic/screen.h"

#include <errno.h>

int simultaneous_generic_screen_line(
    gdImage* image, generic_interface_t* interface, screen_t* screen,
    color_t color, ext_t u0, ext_t v0, ext_t u1, ext_t v1) {
  return -EINVAL;
}

int simultaneous_generic_screen_rectangle(
    gdImage* image, generic_interface_t* interface, screen_t* screen,
    color_t color, ext_t u0, ext_t v0, ext_t u1, ext_t v1) {
  return -EINVAL;
}

int simultaneous_generic_screen_circle(
    gdImage* image, generic_interface_t* interface, screen_t* screen,
    color_t color, ext_t u0, ext_t v0, ext_t radius) {
  return -EINVAL;
}

int simultaneous_generic_screen_ellipse(
    gdImage* image, generic_interface_t* interface, screen_t* screen,
    color_t color, ext_t u0, ext_t v0, ext_t major, ext_t minor) {
  return -EINVAL;
}
