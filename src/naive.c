#include "sicgl/naive.h"
#include "sicgl/generic.h"
#include "sicgl/iter.h"

// // naive pixel cannot exist - its an oxymoron
// // the user *must* at least provide the generic pixel function
// static inline void naive_pixel(generic_interface_t* interface, color_t color, uext_t u, uext_t v) {
//   interface->pixel(interface->arg, color, u, v);
// }

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
  generic_interface_t* interface;
  color_t color;
} hline_cb_arg_t;

static void naive_hline_cb(void* arg) {
  hline_cb_arg_t* cb_args = (hline_cb_arg_t*)arg;
  hline_t* hline = cb_args->hline;
  generic_interface_t* interface = cb_args->interface;
  color_t color = cb_args->color;

  sicgl_generic_pixel(interface, color, hline->u, hline->v);
}

/**
 * @brief 
 * 
 * @param interface 
 * @param color 
 * @param u0 
 * @param v 
 * @param u1 
 */
void naive_hline(generic_interface_t* interface, color_t color, uext_t u0, uext_t v, uext_t u1) {
  hline_t hline = hline_create(u0, u1, v);
  iter_t iter = hline_get_iter(&hline);
  hline_cb_arg_t cb_args;
  cb_args.hline = &hline;
  cb_args.interface = interface;
  cb_args.color = color;
  iter_foreach(iter, naive_hline_cb, &cb_args);
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
  generic_interface_t* interface;
  color_t color;
} vline_cb_arg_t;

static void naive_vline_cb(void* arg) {
  vline_cb_arg_t* cb_args = (vline_cb_arg_t*)arg;
  vline_t* vline = cb_args->vline;
  generic_interface_t* interface = cb_args->interface;
  color_t color = cb_args->color;

  sicgl_generic_pixel(interface, color, vline->u, vline->v);
}

/**
 * @brief 
 * 
 * @param interface 
 * @param color 
 * @param u 
 * @param v0 
 * @param v1 
 */
void naive_vline(generic_interface_t* interface, color_t color, uext_t u, uext_t v0, uext_t v1) {
  vline_t vline = vline_create(v0, v1, u);
  iter_t iter = vline_get_iter(&vline);
  vline_cb_arg_t cb_args;
  cb_args.vline = &vline;
  cb_args.interface = interface;
  cb_args.color = color;
  iter_foreach(iter, naive_vline_cb, &cb_args);
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
  generic_interface_t* interface;
  color_t color;
  region_t* region;
} region_cb_arg_t;

static void naive_region_cb(void* arg) {
  region_cb_arg_t* cb_args = (region_cb_arg_t*)arg;
  region_t* region = cb_args->region;
  generic_interface_t* interface = cb_args->interface;
  color_t color = cb_args->color;

  sicgl_generic_hline(interface, color, region->u0, region->v, region->u1);
}

/**
 * @brief 
 * 
 * @param interface 
 * @param color 
 * @param u0 
 * @param v0 
 * @param u1 
 * @param v1 
 */
void naive_region(generic_interface_t* interface, color_t color, uext_t u0,
                         uext_t v0, uext_t u1, uext_t v1) {
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
