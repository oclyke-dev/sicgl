#include "utilities/simultaneous/direct.h"

#include <errno.h>

#include "sicgl/private/direct.h"

int simultaneous_direct_pixel(
    gdImage* image, interface_t* interface, color_t color, ext_t u0, ext_t v0) {
  int ret = 0;
  gdImageSetPixel(image, u0, v0, color);
  sicgl_direct_pixel(interface, color, u0, v0);
out:
  return ret;
}

int simultaneous_direct_hline(
    gdImage* image, interface_t* interface, color_t color, ext_t u0, ext_t v0,
    ext_t u1, ext_t v1) {
  int ret = 0;
  gdImageLine(image, u0, v0, u1, v1, color);
  sicgl_direct_hline(interface, color, u0, v0, u1);
out:
  return ret;
}

int simultaneous_direct_vline(
    gdImage* image, interface_t* interface, color_t color, ext_t u0, ext_t v0,
    ext_t u1, ext_t v1) {
  int ret = 0;
  gdImageLine(image, u0, v0, u1, v1, color);
  sicgl_direct_vline(interface, color, u0, v0, v1);
out:
  return ret;
}

int simultaneous_direct_region(
    gdImage* image, interface_t* interface, color_t color, ext_t u0, ext_t v0,
    ext_t u1, ext_t v1) {
  int ret = 0;
  gdImageFilledRectangle(image, u0, v0, u1, v1, color);
  sicgl_direct_region(interface, color, u0, v0, u1, v1);
out:
  return ret;
}
