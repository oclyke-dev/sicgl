#pragma once

#include <stdint.h>
#include <stdbool.h>

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

void iter_foreach(iter_t* iter, void (*callback)(void*), void* init_arg);

// drawing is always done on a grid with uv coordinates from [0, 0] to [width-1, height-1]
typedef struct _grid_t {
  uext_t width;
  uext_t height;
} grid_t;

// sicgl needs implementations of various writer functions which
// allow it to actually interact with the user application
// a user defined implementation for 'pixel' is required. this
// implementation may be used to inform default 'naive' sicgl 
// implementations of the other functions.
typedef struct _screenwriter_t {
  void (*pixel)(void* arg, color_t color, uext_t u, uext_t v);
  void (*hline)(void* arg, color_t color, uext_t u0, uext_t v, uext_t u1);
  void (*vline)(void* arg, color_t color, uext_t u, uext_t v0, uext_t v1);
  void (*region)(void* arg, color_t color, uext_t u0, uext_t v0, uext_t u1, uext_t v1);
  
  // argument provided to screenwriters
  void* arg;
} screenwriter_t;

typedef struct _interface_t {
  void* arg;
  grid_t grid;
  screenwriter_t screenwriter;
} interface_t;

// draw iterator through interface
void sicgl_draw(interface_t* interface, iter_t* iter);

void sicgl_draw_pixel(interface_t* interface, color_t color, uext_t u, uext_t v);
