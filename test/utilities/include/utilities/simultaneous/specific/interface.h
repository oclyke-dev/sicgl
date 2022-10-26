#pragma once

#include "gd.h"
#include "sicgl_specific.h"

int simultaneous_specific_pixel(
    gdImage* image, specific_interface_t* interface, color_sequence_t* sequence,
    ext_t u0, ext_t v0);
int simultaneous_specific_hline(
    gdImage* image, specific_interface_t* interface, color_sequence_t* sequence,
    ext_t u0, ext_t v0, ext_t u1, ext_t v1);
int simultaneous_specific_vline(
    gdImage* image, specific_interface_t* interface, color_sequence_t* sequence,
    ext_t u0, ext_t v0, ext_t u1, ext_t v1);
int simultaneous_specific_region(
    gdImage* image, specific_interface_t* interface, color_sequence_t* sequence,
    ext_t u0, ext_t v0, ext_t u1, ext_t v1);
