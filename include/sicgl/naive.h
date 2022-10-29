#pragma once

#include <stdbool.h>

#include "sicgl/generic/interface.h"

// naive fallbacks for generic interface
void naive_hline(
    generic_interface_t* interface, color_t color, uext_t u0, uext_t v,
    uext_t u1);
void naive_vline(
    generic_interface_t* interface, color_t color, uext_t u, uext_t v0,
    uext_t v1);
void naive_region(
    generic_interface_t* interface, color_t color, uext_t u0, uext_t v0,
    uext_t u1, uext_t v1);

// structure to iterate hline
typedef struct _hline_t {
  uext_t umin;
  uext_t umax;
  uext_t u;
  uext_t v;
} hline_t;

static inline void* hline_first(void* args) {
  hline_t* hline = (hline_t*)args;
  return args;
}
static inline void* hline_next(void* args) {
  // u only increments
  hline_t* hline = (hline_t*)args;
  hline->u++;
  return args;
}
static inline bool hline_done(void* args) {
  hline_t* hline = (hline_t*)args;
  return hline->u > hline->umax;
}
static inline hline_t hline_create(uext_t from, uext_t to, uext_t v) {
  hline_t hline;
  bool dir = (from < to);
  hline.umin = (dir) ? from : to;
  hline.umax = (dir) ? to : from;
  hline.u = hline.umin;
  hline.v = v;
  return hline;
}

// structure to iterate vline
typedef struct _vline_t {
  uext_t vmin;
  uext_t vmax;
  uext_t u;
  uext_t v;
} vline_t;

static inline void* vline_first(void* args) {
  vline_t* vline = (vline_t*)args;
  return args;
}
static inline void* vline_next(void* args) {
  // v only increments
  vline_t* vline = (vline_t*)args;
  vline->v++;
  return args;
}
static inline bool vline_done(void* args) {
  vline_t* vline = (vline_t*)args;
  return vline->v > vline->vmax;
}
static vline_t vline_create(uext_t from, uext_t to, uext_t u) {
  vline_t vline;
  bool dir = (from < to);
  vline.vmin = (dir) ? from : to;
  vline.vmax = (dir) ? to : from;
  vline.u = u;
  vline.v = vline.vmin;
  return vline;
}

// structure to iterate region
typedef struct _region_t {
  uext_t vmin;
  uext_t vmax;
  uext_t v;
  uext_t u0;
  uext_t u1;
} region_t;

static inline void* region_first(void* args) {
  region_t* region = (region_t*)args;
  return args;
}
static inline void* region_next(void* args) {
  // v only increments
  region_t* region = (region_t*)args;
  region->v++;
  return args;
}
static inline bool region_done(void* args) {
  region_t* region = (region_t*)args;
  return region->v > region->vmax;
}
static region_t region_create(uext_t u0, uext_t v0, uext_t u1, uext_t v1) {
  region_t region;
  bool dir = (v0 < v1);
  region.vmin = (dir) ? v0 : v1;
  region.vmax = (dir) ? v1 : v0;
  region.v = region.vmin;
  region.u0 = u0;
  region.u1 = u1;
  return region;
}
