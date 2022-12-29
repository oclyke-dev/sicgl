#pragma once

#include "gd.h"
#include "sicgl.h"

int simultaneous_direct_pixel(
    gdImage* image, interface_t* interface, color_t color, ext_t u0,
    ext_t v0);
int simultaneous_direct_hline(
    gdImage* image, interface_t* interface, color_t color, ext_t u0,
    ext_t v0, ext_t u1, ext_t v1);
int simultaneous_direct_vline(
    gdImage* image, interface_t* interface, color_t color, ext_t u0,
    ext_t v0, ext_t u1, ext_t v1);
int simultaneous_direct_region(
    gdImage* image, interface_t* interface, color_t color, ext_t u0,
    ext_t v0, ext_t u1, ext_t v1);
