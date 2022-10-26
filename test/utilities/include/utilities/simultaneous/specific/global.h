#pragma once

#include "gd.h"
#include "sicgl_specific.h"

int simultaneous_specific_global_line(
    gdImage* image, specific_interface_t* interface, screen_t* screen,
    color_sequence_t* sequence, ext_t u0, ext_t v0, ext_t u1, ext_t v1);
int simultaneous_specific_global_rectangle(
    gdImage* image, specific_interface_t* interface, screen_t* screen,
    color_sequence_t* sequence, ext_t u0, ext_t v0, ext_t u1, ext_t v1);
int simultaneous_specific_global_circle(
    gdImage* image, specific_interface_t* interface, screen_t* screen,
    color_sequence_t* sequence, ext_t u0, ext_t v0, ext_t radius);
int simultaneous_specific_global_ellipse(
    gdImage* image, specific_interface_t* interface, screen_t* screen,
    color_sequence_t* sequence, ext_t u0, ext_t v0, ext_t major, ext_t minor);
