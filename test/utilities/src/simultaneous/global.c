#include "utilities/simultaneous/global.h"

#include <errno.h>

int simultaneous_specific_global_line(
    gdImage* image, interface_t* interface, screen_t* screen,
    color_sequence_t* sequence, ext_t u0, ext_t v0, ext_t u1, ext_t v1) {
  return -EINVAL;
}

int simultaneous_specific_global_rectangle(
    gdImage* image, interface_t* interface, screen_t* screen,
    color_sequence_t* sequence, ext_t u0, ext_t v0, ext_t u1, ext_t v1) {
  return -EINVAL;
}

int simultaneous_specific_global_circle(
    gdImage* image, interface_t* interface, screen_t* screen,
    color_sequence_t* sequence, ext_t u0, ext_t v0, ext_t radius) {
  return -EINVAL;
}

int simultaneous_specific_global_ellipse(
    gdImage* image, interface_t* interface, screen_t* screen,
    color_sequence_t* sequence, ext_t u0, ext_t v0, ext_t major, ext_t minor) {
  return -EINVAL;
}
