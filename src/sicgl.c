#include "sicgl.h"

#include <stdio.h>

void iter_foreach(iter_t iter, void (*callback)(void*), void* arg) {
  for (iter.first(iter.args); !iter.done(iter.args); iter.next(iter.args)) {
    callback(arg);
  }
}

void sicgl_draw_pixel(interface_t* interface, color_t color, uext_t u, uext_t v) {
  // pixel must exist
  interface->screenwriter.pixel(interface->screenwriter.arg, color, u, v);
}

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
static hline_t hline_create(uext_t from, uext_t to, uext_t v) {
  hline_t hline;
  bool dir = (from < to);
  hline.umin = (dir) ? from : to;
  hline.umax = (dir) ? to : from;
  hline.u = hline.umin;
  hline.v = v;
  return hline;
}

static inline iter_t hline_get_iter(hline_t* hline) {
  iter_t iter;
  iter.first = hline_first;
  iter.next = hline_next;
  iter.done = hline_done;
  iter.args = hline;
  return iter;
}

typedef struct _hline_cb_arg_t {
  hline_t* hline;
  interface_t* interface;
  color_t color;
} hline_cb_arg_t;

static void naive_hline_cb(void* arg) {
  hline_cb_arg_t* cb_args = (hline_cb_arg_t*)arg;
  hline_t* hline = cb_args->hline;
  interface_t* interface = cb_args->interface;
  color_t color = cb_args->color;

  sicgl_draw_pixel(interface, color, hline->u, hline->v);
}

static inline void naive_hline(interface_t* interface, color_t color, uext_t u0, uext_t v, uext_t u1) {
  hline_t hline = hline_create(u0, u1, v);
  iter_t iter = hline_get_iter(&hline);
  hline_cb_arg_t cb_args;
  cb_args.hline = &hline;
  cb_args.interface = interface;
  cb_args.color = color;
  iter_foreach(iter, naive_hline_cb, &cb_args);
}
void sicgl_draw_hline(interface_t* interface, color_t color, uext_t u0, uext_t v, uext_t u1) {
  if (interface->screenwriter.hline) {
    interface->screenwriter.hline(interface->screenwriter.arg, color, u0, v, u1);
  } else {
    naive_hline(interface, color, u0, v, u1);
  }
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

static inline iter_t vline_get_iter(vline_t* vline) {
  iter_t iter;
  iter.first = vline_first;
  iter.next = vline_next;
  iter.done = vline_done;
  iter.args = vline;
  return iter;
}

typedef struct _vline_cb_arg_t {
  vline_t* vline;
  interface_t* interface;
  color_t color;
} vline_cb_arg_t;

static void naive_vline_cb(void* arg) {
  vline_cb_arg_t* cb_args = (vline_cb_arg_t*)arg;
  vline_t* vline = cb_args->vline;
  interface_t* interface = cb_args->interface;
  color_t color = cb_args->color;

  sicgl_draw_pixel(interface, color, vline->u, vline->v);
}

static inline void naive_vline(interface_t* interface, color_t color, uext_t u, uext_t v0, uext_t v1) {
  vline_t vline = vline_create(v0, v1, u);
  iter_t iter = vline_get_iter(&vline);
  vline_cb_arg_t cb_args;
  cb_args.vline = &vline;
  cb_args.interface = interface;
  cb_args.color = color;
  iter_foreach(iter, naive_vline_cb, &cb_args);
}
void sicgl_draw_vline(interface_t* interface, color_t color, uext_t u0, uext_t v, uext_t u1) {
  if (interface->screenwriter.vline) {
    interface->screenwriter.vline(interface->screenwriter.arg, color, u0, v, u1);
  } else {
    naive_vline(interface, color, u0, v, u1);
  }
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
  return region->v >= region->vmax;
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

static inline iter_t region_get_iter(region_t* region) {
  iter_t iter;
  iter.first = region_first;
  iter.next = region_next;
  iter.done = region_done;
  iter.args = region;
  return iter;
}

typedef struct _region_cb_arg_t {
  interface_t* interface;
  color_t color;
  region_t* region;
} region_cb_arg_t;

static void naive_region_cb(void* arg) {
  region_cb_arg_t* cb_args = (region_cb_arg_t*)arg;
  region_t* region = cb_args->region;
  interface_t* interface = cb_args->interface;
  color_t color = cb_args->color;

  sicgl_draw_hline(interface, color, region->u0, region->v, region->u1);
}

static void naive_region(interface_t* interface, color_t color, uext_t u0, uext_t v0, uext_t u1, uext_t v1) {
  // assume that hline is faster and select hline when available
  // todo: consider ways that the user can specify this choice
  region_t region = region_create(u0, v0, u1, v1);
  iter_t iter = region_get_iter(&region);
  region_cb_arg_t cb_args;
  cb_args.region = &region;
  cb_args.interface = interface;
  cb_args.color = color;
  iter_foreach(iter, naive_region_cb, &cb_args);
}
void sicgl_draw_region(interface_t* interface, color_t color, uext_t u0, uext_t v0, uext_t u1, uext_t v1) {
  if (interface->screenwriter.region) {
    interface->screenwriter.region(interface->screenwriter.arg, color, u0, v0, u1, v1);
  } else {
    naive_region(interface, color, u0, v0, u1, v1);
  }
}
