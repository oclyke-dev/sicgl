#pragma once

#include "gd.h"
#include "sicgl_generic.h"

int simultaneous_generic_pixel(
    gdImage* image, generic_interface_t* interface, color_t color, ext_t u0,
    ext_t v0);
int simultaneous_generic_hline(
    gdImage* image, generic_interface_t* interface, color_t color, ext_t u0,
    ext_t v0, ext_t u1, ext_t v1);
int simultaneous_generic_vline(
    gdImage* image, generic_interface_t* interface, color_t color, ext_t u0,
    ext_t v0, ext_t u1, ext_t v1);
int simultaneous_generic_region(
    gdImage* image, generic_interface_t* interface, color_t color, ext_t u0,
    ext_t v0, ext_t u1, ext_t v1);
