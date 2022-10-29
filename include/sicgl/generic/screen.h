#pragma once

#include "sicgl/generic/interface.h"
#include "sicgl/screen.h"

// write through virtual screens
int sicgl_generic_screen_pixel(
    generic_interface_t* interface, screen_t* screen, color_t color, ext_t u0,
    ext_t v0);
int sicgl_generic_screen_line(
    generic_interface_t* interface, screen_t* screen, color_t color, ext_t u0,
    ext_t v0, ext_t u1, ext_t v1);
int sicgl_generic_screen_rectangle(
    generic_interface_t* interface, screen_t* screen, color_t color, ext_t u0,
    ext_t v0, ext_t u1, ext_t v1);
int sicgl_generic_screen_circle_bresenham(
    generic_interface_t* interface, screen_t* screen, color_t color, ext_t u0,
    ext_t v0, ext_t diameter);
int sicgl_generic_screen_circle_ellipse(
    generic_interface_t* interface, screen_t* screen, color_t color, ext_t u0,
    ext_t v0, ext_t diameter);
int sicgl_generic_screen_ellipse(
    generic_interface_t* interface, screen_t* screen, color_t color, ext_t u0,
    ext_t v0, ext_t semiu, ext_t semiv);
