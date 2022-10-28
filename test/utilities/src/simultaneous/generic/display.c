#include "utilities/simultaneous/generic/display.h"

#include <errno.h>

int simultaneous_generic_display_line(
    gdImage* image, generic_interface_t* interface, color_t color, ext_t u0,
    ext_t v0, ext_t u1, ext_t v1) {
  int ret = 0;
  gdImageLine(image, u0, v0, u1, v1, *(int*)color);
  sicgl_generic_display_line(interface, color, u0, v0, u1, v1);
out:
  return ret;
}

int simultaneous_generic_display_rectangle(
    gdImage* image, generic_interface_t* interface, color_t color, ext_t u0,
    ext_t v0, ext_t u1, ext_t v1) {
  int ret = 0;
  gdImageRectangle(image, u0, v0, u1, v1, *(int*)color);
  ret = sicgl_generic_display_rectangle(interface, color, u0, v0, u1, v1);
out:
  return ret;
}

int simultaneous_generic_display_circle_bresenham(
    gdImage* image, generic_interface_t* interface, color_t color, ext_t u0,
    ext_t v0, ext_t diameter) {
  int ret = 0;
  gdImageEllipse(image, u0, v0, diameter, diameter, *(int*)color);
  ret = sicgl_generic_display_circle_bresenham(
      interface, color, u0, v0, diameter);
  return ret;
}

int simultaneous_generic_display_circle_ellipse(
    gdImage* image, generic_interface_t* interface, color_t color, ext_t u0,
    ext_t v0, ext_t diameter) {
  int ret = 0;
  gdImageEllipse(image, u0, v0, diameter, diameter, *(int*)color);
  ret =
      sicgl_generic_display_circle_ellipse(interface, color, u0, v0, diameter);
  return ret;
}

int simultaneous_generic_display_ellipse(
    gdImage* image, generic_interface_t* interface, color_t color, ext_t u0,
    ext_t v0, ext_t major, ext_t minor) {
  return -EINVAL;
}
