#pragma once

#include "gd.h"
#include "sicgl_specific.h"

int simultaneous_specific_display_line(
    gdImage* image, specific_interface_t* interface, color_t color, ext_t u0,
    ext_t v0, ext_t u1, ext_t v1);
int simultaneous_specific_display_rectangle(
    gdImage* image, specific_interface_t* interface, color_t color, ext_t u0,
    ext_t v0, ext_t u1, ext_t v1);
int simultaneous_specific_display_circle_bresenham(
    gdImage* image, specific_interface_t* interface, color_t color, ext_t u0,
    ext_t v0, ext_t diameter);
int simultaneous_specific_display_circle_ellipse(
    gdImage* image, specific_interface_t* interface, color_t color, ext_t u0,
    ext_t v0, ext_t diameter);
int simultaneous_specific_display_ellipse(
    gdImage* image, specific_interface_t* interface, color_t color, ext_t u0,
    ext_t v0, ext_t major, ext_t minor);
