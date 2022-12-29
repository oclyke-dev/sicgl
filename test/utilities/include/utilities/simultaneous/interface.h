#pragma once

#include "gd.h"
#include "sicgl.h"

int simultaneous_interface_pixel(
    gdImage* image, interface_t* interface, color_t color, ext_t u0, ext_t v0);
int simultaneous_interface_line(
    gdImage* image, interface_t* interface, color_t color, ext_t u0, ext_t v0,
    ext_t u1, ext_t v1);
int simultaneous_interface_rectangle(
    gdImage* image, interface_t* interface, color_t color, ext_t u0, ext_t v0,
    ext_t u1, ext_t v1);
int simultaneous_interface_circle_bresenham(
    gdImage* image, interface_t* interface, color_t color, ext_t u0, ext_t v0,
    ext_t diameter);
int simultaneous_interface_circle_ellipse(
    gdImage* image, interface_t* interface, color_t color, ext_t u0, ext_t v0,
    ext_t diameter);
int simultaneous_interface_ellipse(
    gdImage* image, interface_t* interface, color_t color, ext_t u0, ext_t v0,
    ext_t major, ext_t minor);
