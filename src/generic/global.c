#include <stddef.h>

#include "sicgl/debug.h"
#include "sicgl/generic/display.h"
#include "sicgl/translate.h"

/**
 * @brief Global-relative drawing functions.
 * Coordinates are taken in global frame.
 * Valid drawing area is the interface's display only.
 *
 */

int sicgl_generic_global_pixel(
    generic_interface_t* interface, color_t color, ext_t u0,
    ext_t v0) {
  int ret = 0;

	// translate from global coordinates to display coordinates
	ret = translate_global_to_screen(&interface->screen, &u0, &v0);
	if (0 != ret) {
		goto out;
	}

  // draw pixel to display
  ret = sicgl_generic_display_pixel(interface, color, u0, v0);

out:
  return ret;
}

int sicgl_generic_global_line(
    generic_interface_t* interface, color_t color, ext_t u0,
    ext_t v0, ext_t u1, ext_t v1) {
  int ret = 0;

	ret = translate_global_to_screen(&interface->screen, &u0, &v0);
	if (0 != ret) {
		goto out;
	}
	ret = translate_global_to_screen(&interface->screen, &u1, &v1);
	if (0 != ret) {
		goto out;
	}
  ret = sicgl_generic_display_line(interface, color, u0, v0, u1, v1);

out:
  return ret;
}

int sicgl_generic_global_rectangle(
    generic_interface_t* interface, color_t color, ext_t u0,
    ext_t v0, ext_t u1, ext_t v1) {
  int ret = 0;
	ret = translate_global_to_screen(&interface->screen, &u0, &v0);
	if (0 != ret) {
		goto out;
	}
	ret = translate_global_to_screen(&interface->screen, &u1, &v1);
	if (0 != ret) {
		goto out;
	}
  ret = sicgl_generic_display_rectangle(interface, color, u0, v0, u1, v1);

out:
  return ret;
}

int sicgl_generic_global_circle_bresenham(
    generic_interface_t* interface, color_t color, ext_t u0,
    ext_t v0, ext_t diameter) {
  int ret = 0;
	ret = translate_global_to_screen(&interface->screen, &u0, &v0);
	if (0 != ret) {
		goto out;
	}
  ret = sicgl_generic_display_circle_bresenham(interface, color, u0, v0, diameter);

out:
  return ret;
}

int sicgl_generic_global_circle_ellipse(
    generic_interface_t* interface, color_t color, ext_t u0,
    ext_t v0, ext_t diameter) {
  int ret = 0;
	ret = translate_global_to_screen(&interface->screen, &u0, &v0);
	if (0 != ret) {
		goto out;
	}
  ret = sicgl_generic_display_circle_ellipse(interface, color, u0, v0, diameter);

out:
  return ret;
}

int sicgl_generic_global_ellipse(
    generic_interface_t* interface, color_t color, ext_t u0,
    ext_t v0, ext_t semiu, ext_t semiv) {
  int ret = 0;
	ret = translate_global_to_screen(&interface->screen, &u0, &v0);
	if (0 != ret) {
		goto out;
	}
  ret = sicgl_generic_display_ellipse(interface, color, u0, v0, semiu, semiv);

out:
  return ret;
}
