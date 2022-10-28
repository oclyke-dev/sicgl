#pragma once

#include "gd.h"
#include "sicgl_generic.h"

int simultaneous_generic_display_line(
    gdImage* image, generic_interface_t* interface, color_t color, ext_t u0,
    ext_t v0, ext_t u1, ext_t v1);
int simultaneous_generic_display_rectangle(
    gdImage* image, generic_interface_t* interface, color_t color, ext_t u0,
    ext_t v0, ext_t u1, ext_t v1);
int simultaneous_generic_display_circle_bresenham(
    gdImage* image, generic_interface_t* interface, color_t color, ext_t u0,
    ext_t v0, ext_t diameter);
int simultaneous_generic_display_circle_ellipse(
    gdImage* image, generic_interface_t* interface, color_t color, ext_t u0,
    ext_t v0, ext_t diameter);
int simultaneous_generic_display_ellipse(
    gdImage* image, generic_interface_t* interface, color_t color, ext_t u0,
    ext_t v0, ext_t major, ext_t minor);
