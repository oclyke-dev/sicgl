#include <errno.h>

#include "utilities/simultaneous/generic/interface.h"
#include "sicgl/private/generic_direct.h"

int simultaneous_generic_pixel(
    gdImage* image, generic_interface_t* interface, color_t color, ext_t u0,
    ext_t v0) {
  int ret = 0;
  gdImageSetPixel(image, u0, v0, *(int*)color);
  generic_pixel(interface, color, u0, v0);
out:
  return ret;
}

int simultaneous_generic_hline(
    gdImage* image, generic_interface_t* interface, color_t color, ext_t u0,
    ext_t v0, ext_t u1, ext_t v1) {
  int ret = 0;
  gdImageLine(image, u0, v0, u1, v1, *(int*)color);
  generic_hline(interface, color, u0, v0, u1);
out:
  return ret;
}

int simultaneous_generic_vline(
    gdImage* image, generic_interface_t* interface, color_t color, ext_t u0,
    ext_t v0, ext_t u1, ext_t v1) {
  int ret = 0;
  gdImageLine(image, u0, v0, u1, v1, *(int*)color);
  generic_vline(interface, color, u0, v0, v1);
out:
  return ret;
}

int simultaneous_generic_region(
    gdImage* image, generic_interface_t* interface, color_t color, ext_t u0,
    ext_t v0, ext_t u1, ext_t v1) {
  int ret = 0;
  gdImageFilledRectangle(image, u0, v0, u1, v1, *(int*)color);
  generic_region(interface, color, u0, v0, u1, v1);
out:
  return ret;
}
