#pragma once

#include "sicgl/generic/interface.h"

// write direct-to-display
int sicgl_generic_display_pixel(
    generic_interface_t* interface, color_t color, ext_t u0, ext_t v0);
int sicgl_generic_display_line(
    generic_interface_t* interface, color_t color, ext_t u0, ext_t v0, ext_t u1,
    ext_t v1);
int sicgl_generic_display_rectangle(
    generic_interface_t* interface, color_t color, ext_t u0, ext_t v0, ext_t u1,
    ext_t v1);
int sicgl_generic_display_circle_bresenham(
    generic_interface_t* interface, color_t color, ext_t u0, ext_t v0,
    ext_t diameter);
int sicgl_generic_display_circle_ellipse(
    generic_interface_t* interface, color_t color, ext_t u0, ext_t v0,
    ext_t diameter);
int sicgl_generic_display_ellipse(
    generic_interface_t* interface, color_t color, ext_t u0, ext_t v0,
    ext_t semiu, ext_t semiv);
