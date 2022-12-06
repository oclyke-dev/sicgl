#include "sicgl/debug.h"
#include "sicgl/specific/display.h"
#include "sicgl/translate.h"

/**
 * @brief Screen-relative drawing functions.
 * Coordinates are taken in screen frame.
 * Intersection of the screen and interface's display is the valid drawing area.
 *
 */

int sicgl_specific_screen_pixel(
    specific_interface_t* interface, screen_t* screen,
    color_t color, ext_t u0, ext_t v0) {
  int ret = 0;

  // translate coordinates from screen to display
  ret = translate_screen_to_screen(screen, &interface->screen, &u0, &v0);
  if (0 != ret) {
    goto out;
  }

  // draw pixel to display
  ret = sicgl_specific_display_pixel(interface, color, u0, v0);

out:
  return ret;
}

int sicgl_specific_screen_line(
    specific_interface_t* interface, screen_t* screen,
    color_t color, ext_t u0, ext_t v0, ext_t u1, ext_t v1) {
  int ret = 0;
  ret = translate_screen_to_screen(screen, &interface->screen, &u0, &v0);
  if (0 != ret) {
    goto out;
  }
  ret = translate_screen_to_screen(screen, &interface->screen, &u1, &v1);
  if (0 != ret) {
    goto out;
  }
  ret = sicgl_specific_display_line(interface, color, u0, v0, u1, v1);

out:
  return ret;
}

int sicgl_specific_screen_rectangle(
    specific_interface_t* interface, screen_t* screen,
    color_t color, ext_t u0, ext_t v0, ext_t u1, ext_t v1) {
  int ret = 0;
  ret = translate_screen_to_screen(screen, &interface->screen, &u0, &v0);
  if (0 != ret) {
    goto out;
  }
  ret = translate_screen_to_screen(screen, &interface->screen, &u1, &v1);
  if (0 != ret) {
    goto out;
  }
  ret = sicgl_specific_display_rectangle(
      interface, color, u0, v0, u1, v1);

out:
  return ret;
}

int sicgl_specific_screen_circle_bresenham(
    specific_interface_t* interface, screen_t* screen,
    color_t color, ext_t u0, ext_t v0, ext_t diameter) {
  int ret = 0;
  ret = translate_screen_to_screen(screen, &interface->screen, &u0, &v0);
  if (0 != ret) {
    goto out;
  }
  ret = sicgl_specific_display_circle_bresenham(
      interface, color, u0, v0, diameter);

out:
  return ret;
}

int sicgl_specific_screen_circle_ellipse(
    specific_interface_t* interface, screen_t* screen,
    color_t color, ext_t u0, ext_t v0, ext_t diameter) {
  int ret = 0;
  ret = translate_screen_to_screen(screen, &interface->screen, &u0, &v0);
  if (0 != ret) {
    goto out;
  }
  ret = sicgl_specific_display_circle_ellipse(
      interface, color, u0, v0, diameter);

out:
  return ret;
}

int sicgl_specific_screen_ellipse(
    specific_interface_t* interface, screen_t* screen,
    color_t color, ext_t u0, ext_t v0, ext_t semiu,
    ext_t semiv) {
  int ret = 0;
  ret = translate_screen_to_screen(screen, &interface->screen, &u0, &v0);
  if (0 != ret) {
    goto out;
  }
  ret = sicgl_specific_display_ellipse(
      interface, color, u0, v0, semiu, semiv);

out:
  return ret;
}
