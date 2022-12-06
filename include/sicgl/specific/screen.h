#pragma once

#include "sicgl/screen.h"
#include "sicgl/specific/interface.h"

// write through virtual screens
int sicgl_specific_screen_pixel(
    specific_interface_t* interface, screen_t* screen, color_t color, ext_t u0,
    ext_t v0);
int sicgl_specific_screen_line(
    specific_interface_t* interface, screen_t* screen, color_t color, ext_t u0,
    ext_t v0, ext_t u1, ext_t v1);
int sicgl_specific_screen_rectangle(
    specific_interface_t* interface, screen_t* screen, color_t color, ext_t u0,
    ext_t v0, ext_t u1, ext_t v1);
int sicgl_specific_screen_circle_bresenham(
    specific_interface_t* interface, screen_t* screen, color_t color, ext_t u0,
    ext_t v0, ext_t diameter);
int sicgl_specific_screen_circle_ellipse(
    specific_interface_t* interface, screen_t* screen, color_t color, ext_t u0,
    ext_t v0, ext_t diameter);
int sicgl_specific_screen_ellipse(
    specific_interface_t* interface, screen_t* screen, color_t color, ext_t u0,
    ext_t v0, ext_t semiu, ext_t semiv);
