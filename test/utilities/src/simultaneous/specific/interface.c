#include "utilities/simultaneous/specific/interface.h"

#include <errno.h>

#include "sicgl/private/specific_direct.h"

int simultaneous_specific_pixel(
    gdImage* image, specific_interface_t* interface, color_t color, ext_t u0,
    ext_t v0) {
  int ret = 0;
  gdImageSetPixel(image, u0, v0, color);
  sicgl_specific_pixel(interface, color, u0, v0);
out:
  return ret;
}

int simultaneous_specific_hline(
    gdImage* image, specific_interface_t* interface, color_t color, ext_t u0,
    ext_t v0, ext_t u1, ext_t v1) {
  int ret = 0;
  gdImageLine(image, u0, v0, u1, v1, color);
  specific_hline(interface, color, u0, v0, u1);
out:
  return ret;
}

int simultaneous_specific_vline(
    gdImage* image, specific_interface_t* interface, color_t color, ext_t u0,
    ext_t v0, ext_t u1, ext_t v1) {
  int ret = 0;
  gdImageLine(image, u0, v0, u1, v1, color);
  specific_vline(interface, color, u0, v0, v1);
out:
  return ret;
}

int simultaneous_specific_region(
    gdImage* image, specific_interface_t* interface, color_t color, ext_t u0,
    ext_t v0, ext_t u1, ext_t v1) {
  int ret = 0;
  gdImageFilledRectangle(image, u0, v0, u1, v1, color);
  specific_region(interface, color, u0, v0, u1, v1);
out:
  return ret;
}
