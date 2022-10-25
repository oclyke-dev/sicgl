#include <errno.h>

#include "utilities/simultaneous.h"

int simultaneous_generic_display_pixel(
    gdImage* image, generic_interface_t* interface, color_t color, ext_t u0,
    ext_t v0) {
	return -EINVAL;
}

int simultaneous_generic_display_hline(
    gdImage* image, generic_interface_t* interface, color_t color, ext_t u0,
    ext_t v0, ext_t u1, ext_t v1) {
	return -EINVAL;
}

int simultaneous_generic_display_vline(
    gdImage* image, generic_interface_t* interface, color_t color, ext_t u0,
    ext_t v0, ext_t u1, ext_t v1) {
	return -EINVAL;
}

int simultaneous_generic_display_region(
    gdImage* image, generic_interface_t* interface, color_t color, ext_t u0,
    ext_t v0, ext_t u1, ext_t v1) {
	return -EINVAL;
}

int simultaneous_generic_display_line(
    gdImage* image, generic_interface_t* interface, color_t color, ext_t u0,
    ext_t v0, ext_t u1, ext_t v1) {
	return -EINVAL;
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
