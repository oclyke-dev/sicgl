#include "sicgl/debug.h"
#include "sicgl/specific/display.h"
#include "sicgl/translate.h"

/**
 * @brief Global-relative drawing functions.
 * Coordinates are taken in global frame.
 * Valid drawing area is the interface's display only.
 *
 */

int sicgl_specific_global_pixel(
    specific_interface_t* interface,
    color_sequence_t* color_sequence, ext_t u0, ext_t v0) {
  int ret = 0;
	ret = translate_global_to_screen(&interface->screen, &u0, &v0);
	if (0 != ret) {
		goto out;
	}
  ret = sicgl_specific_display_pixel(interface, color_sequence, u0, v0);

out:
  return ret;
}

int sicgl_specific_global_line(
    specific_interface_t* interface,
    color_sequence_t* color_sequence, ext_t u0, ext_t v0, ext_t u1, ext_t v1) {
  int ret = 0;
	ret = translate_global_to_screen(&interface->screen, &u0, &v0);
	if (0 != ret) {
		goto out;
	}
	ret = translate_global_to_screen(&interface->screen, &u1, &v1);
	if (0 != ret) {
		goto out;
	}
  ret = sicgl_specific_display_line(interface, color_sequence, u0, v0, u1, v1);

out:
  return ret;
}

int sicgl_specific_global_rectangle(
    specific_interface_t* interface,
    color_sequence_t* color_sequence, ext_t u0, ext_t v0, ext_t u1, ext_t v1) {
  int ret = 0;
	ret = translate_global_to_screen(&interface->screen, &u0, &v0);
	if (0 != ret) {
		goto out;
	}
	ret = translate_global_to_screen(&interface->screen, &u1, &v1);
	if (0 != ret) {
		goto out;
	}
  ret = sicgl_specific_display_rectangle(interface, color_sequence, u0, v0, u1, v1);

out:
  return ret;
}

int sicgl_specific_global_circle_bresenham(
    specific_interface_t* interface,
    color_sequence_t* color_sequence, ext_t u0, ext_t v0, ext_t diameter) {
  int ret = 0;
	ret = translate_global_to_screen(&interface->screen, &u0, &v0);
	if (0 != ret) {
		goto out;
	}
  ret = sicgl_specific_display_circle_bresenham(interface, color_sequence, u0, v0, diameter);

out:
  return ret;
}

int sicgl_specific_global_circle_ellipse(
    specific_interface_t* interface,
    color_sequence_t* color_sequence, ext_t u0, ext_t v0, ext_t diameter) {
  int ret = 0;
	ret = translate_global_to_screen(&interface->screen, &u0, &v0);
	if (0 != ret) {
		goto out;
	}
  ret = sicgl_specific_display_circle_ellipse(interface, color_sequence, u0, v0, diameter);

out:
  return ret;
}

int sicgl_specific_global_ellipse(
    specific_interface_t* interface,
    color_sequence_t* color_sequence, ext_t u0, ext_t v0, ext_t semiu, ext_t semiv) {
  int ret = 0;
	ret = translate_global_to_screen(&interface->screen, &u0, &v0);
	if (0 != ret) {
		goto out;
	}
  ret = sicgl_specific_display_ellipse(interface, color_sequence, u0, v0, semiu, semiv);

out:
  return ret;
}
