#pragma once

#include <stdbool.h>
#include <stdint.h>

// colors are user-defined
typedef void* color_t;

// physical extents are large signed/unsigned integers
typedef int32_t ext_t;
typedef uint32_t uext_t;

// a generic iterator which carries user defined data
typedef struct _iter_t {
  // iterator function pointers
  void* (*first)(void* args);
  void* (*next)(void* args);
  bool (*done)(void* args);

  // user data
  void* args;
} iter_t;

void iter_foreach(iter_t iter, void (*callback)(void*), void* arg);

// drawing is always done on a grid with uv coordinates from [0, 0] to [width-1,
// height-1] a height or width of zero will make the grid un-writeable keeping
// this simple interface makes it very easy to write drawing code other
// functionalities, such as window management, should be handled externally for
// instance: WAIT - how DO you do this? you could of course create an interface
// which maps grid units into some other global coordinate system... is this
// fast? is this an extra lookup for each pixel? each drawing interface? can you
// even take advantage of bounds checking if you are then translating to some
// other coordinate system? (maybe you CAN because you know that the resulting
// coordinates are all bound within the original window...)
typedef struct _grid_t {
  uext_t width;
  uext_t height;
} grid_t;

// sicgl needs implementations of various writer functions which
// allow it to actually interact with the user application
// a user defined implementation for 'pixel' is required. this
// implementation may be used to inform default 'naive' sicgl
// implementations of the other functions.
typedef void (*pixel_fn_t)(void* arg, color_t color, uext_t u, uext_t v);
typedef void (*hline_fn_t)(void* arg, color_t color, uext_t u0, uext_t v,
                           uext_t u1);
typedef void (*vline_fn_t)(void* arg, color_t color, uext_t u, uext_t v0,
                           uext_t v1);
typedef void (*region_fn_t)(void* arg, color_t color, uext_t u0, uext_t v0,
                            uext_t u1, uext_t v1);

typedef struct _screenwriter_t {
  pixel_fn_t pixel;
  hline_fn_t hline;
  vline_fn_t vline;
  region_fn_t region;

  // argument provided to screenwriters
  void* arg;
} screenwriter_t;

typedef struct _interface_t {
  void* arg;  // not sure what this arg is doing or is meant to do right now...
  grid_t grid;
  screenwriter_t screenwriter;
} interface_t;

// draw iterator through interface
void sicgl_draw(interface_t* interface, iter_t* iter);

void sicgl_draw_pixel(interface_t* interface, color_t color, uext_t u,
                      uext_t v);
void sicgl_draw_hline(interface_t* interface, color_t color, uext_t u0,
                      uext_t v, uext_t u1);
void sicgl_draw_vline(interface_t* interface, color_t color, uext_t u,
                      uext_t v0, uext_t v1);
void sicgl_draw_region(interface_t* interface, color_t color, uext_t u0,
                       uext_t v0, uext_t u1, uext_t v1);
