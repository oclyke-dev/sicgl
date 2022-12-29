#include "utilities/simultaneous/interface.h"

#include <errno.h>

int simultaneous_interface_pixel(
    gdImage* image, interface_t* interface, color_t color, ext_t u0,
    ext_t v0) {
  int ret = 0;
  gdImageSetPixel(image, u0, v0, color);
  sicgl_interface_pixel(interface, color, u0, v0);
out:
  return ret;
}

int simultaneous_interface_line(
    gdImage* image, interface_t* interface, color_t color, ext_t u0,
    ext_t v0, ext_t u1, ext_t v1) {
  int ret = 0;
  gdImageLine(image, u0, v0, u1, v1, (int)color);
  ret = sicgl_interface_line(interface, color, u0, v0, u1, v1);
out:
  return ret;
}

int simultaneous_interface_rectangle(
    gdImage* image, interface_t* interface, color_t color, ext_t u0,
    ext_t v0, ext_t u1, ext_t v1) {
  int ret = 0;
  gdImageRectangle(image, u0, v0, u1, v1, (int)color);
  ret = sicgl_interface_rectangle(interface, color, u0, v0, u1, v1);
out:
  return ret;
}

int simultaneous_interface_circle_bresenham(
    gdImage* image, interface_t* interface, color_t color, ext_t u0,
    ext_t v0, ext_t diameter) {
  int ret = 0;
  gdImageEllipse(image, u0, v0, diameter, diameter, (int)color);
  ret = sicgl_interface_circle_bresenham(
      interface, color, u0, v0, diameter);
  return ret;
}

int simultaneous_interface_circle_ellipse(
    gdImage* image, interface_t* interface, color_t color, ext_t u0,
    ext_t v0, ext_t diameter) {
  int ret = 0;
  gdImageEllipse(image, u0, v0, diameter, diameter, (int)color);
  ret =
      sicgl_interface_circle_ellipse(interface, color, u0, v0, diameter);
  return ret;
}

int simultaneous_interface_ellipse(
    gdImage* image, interface_t* interface, color_t color, ext_t u0,
    ext_t v0, ext_t major, ext_t minor) {
  return -EINVAL;
}
