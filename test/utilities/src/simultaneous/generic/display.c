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
  return -EINVAL;
}

int simultaneous_generic_display_circle(
    gdImage* image, generic_interface_t* interface, color_t color, ext_t u0,
    ext_t v0, ext_t radius) {
  return -EINVAL;
}

int simultaneous_generic_display_ellipse(
    gdImage* image, generic_interface_t* interface, color_t color, ext_t u0,
    ext_t v0, ext_t major, ext_t minor) {
  return -EINVAL;
}
