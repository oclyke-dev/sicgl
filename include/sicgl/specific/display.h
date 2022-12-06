#pragma once

#include "sicgl/specific/interface.h"

// write direct-to-display
int sicgl_specific_display_pixel(
    specific_interface_t* interface, color_t color, ext_t u0, ext_t v0);
int sicgl_specific_display_line(
    specific_interface_t* interface, color_t color, ext_t u0, ext_t v0,
    ext_t u1, ext_t v1);
int sicgl_specific_display_rectangle(
    specific_interface_t* interface, color_t color, ext_t u0, ext_t v0,
    ext_t u1, ext_t v1);
int sicgl_specific_display_circle_bresenham(
    specific_interface_t* interface, color_t color, ext_t u0, ext_t v0,
    ext_t diameter);
int sicgl_specific_display_circle_ellipse(
    specific_interface_t* interface, color_t color, ext_t u0, ext_t v0,
    ext_t diameter);
int sicgl_specific_display_ellipse(
    specific_interface_t* interface, color_t color, ext_t u0, ext_t v0,
    ext_t semiu, ext_t semiv);
