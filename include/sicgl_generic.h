#pragma once

#include "sicgl/display.h"
#include "sicgl/extent.h"
#include "sicgl/generic.h"
#include "sicgl/screen.h"

// write direct-to-display
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

// write through virtual screens
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
    ext_t v0, ext_t u1, ext_t v1);

// write in global coordinates through an optional screen
int sicgl_generic_global_line(
    generic_interface_t* interface, screen_t* screen, color_t color, ext_t u0,
    ext_t v0, ext_t u1, ext_t v1);
int sicgl_generic_global_rectangle(
    generic_interface_t* interface, screen_t* screen, color_t color, ext_t u0,
    ext_t v0, ext_t u1, ext_t v1);
int sicgl_generic_global_circle_bresenham(
    generic_interface_t* interface, screen_t* screen, color_t color, ext_t u0,
    ext_t v0, ext_t diameter);
int sicgl_generic_global_circle_ellipse(
    generic_interface_t* interface, screen_t* screen, color_t color, ext_t u0,
    ext_t v0, ext_t diameter);
int sicgl_generic_global_ellipse(
    generic_interface_t* interface, screen_t* screen, color_t color, ext_t u0,
    ext_t v0, ext_t u1, ext_t v1);
