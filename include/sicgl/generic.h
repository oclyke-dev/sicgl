#pragma once

#include "sicgl/color.h"
#include "sicgl/extent.h"

// sicgl needs implementations of various writer functions which
// allow it to actually interact with the user application
// a user defined implementation for 'pixel' is required. this
// implementation may be used to inform default 'naive' sicgl
// implementations of the other functions.
typedef void (*pixel_fn_t)(void* arg, color_t color, uext_t u, uext_t v);
typedef void (*hline_fn_t)(
    void* arg, color_t color, uext_t u0, uext_t v, uext_t u1);
typedef void (*vline_fn_t)(
    void* arg, color_t color, uext_t u, uext_t v0, uext_t v1);
typedef void (*region_fn_t)(
    void* arg, color_t color, uext_t u0, uext_t v0, uext_t u1, uext_t v1);

// a generic interface give the user full flexibility
// at the expense of speed
typedef struct _generic_interface_t {
  pixel_fn_t pixel;
  hline_fn_t hline;
  vline_fn_t vline;
  region_fn_t region;

  // argument provided to functions
  void* arg;
} generic_interface_t;

// direct to interface functions
void sicgl_generic_pixel(
    generic_interface_t* interface, color_t color, uext_t u, uext_t v);
void sicgl_generic_hrun(
    generic_interface_t* interface, color_t color, uext_t u, uext_t v, ext_t du);
void sicgl_generic_vrun(
    generic_interface_t* interface, color_t color, uext_t u, uext_t v, ext_t dv);
void sicgl_generic_hline(
    generic_interface_t* interface, color_t color, uext_t u0, uext_t v,
    uext_t u1);
void sicgl_generic_vline(
    generic_interface_t* interface, color_t color, uext_t u, uext_t v0,
    uext_t v1);
void sicgl_generic_diagonal(
    generic_interface_t* interface, color_t color, uext_t u0, uext_t v0, ext_t diru, ext_t dirv, uext_t count);
void sicgl_generic_region(
    generic_interface_t* interface, color_t color, uext_t u0, uext_t v0,
    uext_t u1, uext_t v1);
int sicgl_generic_line(
    generic_interface_t* interface, color_t color, uext_t u0, uext_t v0,
    uext_t u1, uext_t v1);
