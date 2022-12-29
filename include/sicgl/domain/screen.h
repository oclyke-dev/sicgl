#pragma once

#include "sicgl/screen.h"
#include "sicgl/interface.h"

// write through virtual screens
int sicgl_screen_pixel(
    interface_t* interface, screen_t* screen, color_t color, ext_t u0,
    ext_t v0);
int sicgl_screen_line(
    interface_t* interface, screen_t* screen, color_t color, ext_t u0,
    ext_t v0, ext_t u1, ext_t v1);
int sicgl_screen_rectangle(
    interface_t* interface, screen_t* screen, color_t color, ext_t u0,
    ext_t v0, ext_t u1, ext_t v1);
int sicgl_screen_circle_bresenham(
    interface_t* interface, screen_t* screen, color_t color, ext_t u0,
    ext_t v0, ext_t diameter);
int sicgl_screen_circle_ellipse(
    interface_t* interface, screen_t* screen, color_t color, ext_t u0,
    ext_t v0, ext_t diameter);
int sicgl_screen_ellipse(
    interface_t* interface, screen_t* screen, color_t color, ext_t u0,
    ext_t v0, ext_t semiu, ext_t semiv);
