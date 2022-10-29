#pragma once

#include "sicgl/generic.h"

// direct to interface functions
void sicgl_generic_pixel(
    generic_interface_t* interface, color_t color, uext_t u, uext_t v);
void sicgl_generic_hrun(
    generic_interface_t* interface, color_t color, uext_t u, uext_t v,
    ext_t du);
void sicgl_generic_vrun(
    generic_interface_t* interface, color_t color, uext_t u, uext_t v,
    ext_t dv);
void sicgl_generic_hline(
    generic_interface_t* interface, color_t color, uext_t u0, uext_t v,
    uext_t u1);
void sicgl_generic_vline(
    generic_interface_t* interface, color_t color, uext_t u, uext_t v0,
    uext_t v1);
void sicgl_generic_diagonal(
    generic_interface_t* interface, color_t color, uext_t u0, uext_t v0,
    ext_t diru, ext_t dirv, uext_t count);
void sicgl_generic_region(
    generic_interface_t* interface, color_t color, uext_t u0, uext_t v0,
    uext_t u1, uext_t v1);
