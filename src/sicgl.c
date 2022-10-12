#include "sicgl.h"

void iter_foreach(iter_t* iter, void (*callback)(void*), void* init_arg) {
  for (void* arg = iter->first(init_arg); !iter->done(arg); arg = iter->next(arg)) {
    callback(arg);
  }
}

void sicgl_draw_pixel(interface_t* interface, color_t color, uext_t u, uext_t v) {
  interface->screenwriter.pixel(interface->screenwriter.arg, color, u, v);
}

void sicgl_draw_hline(interface_t* interface, color_t color, uext_t u0, uext_t v, uext_t u1) {
  interface->screenwriter.hline(interface->screenwriter.arg, color, u0, v, u1);
}

void sicgl_draw_vline(interface_t* interface, color_t color, uext_t u, uext_t v0, uext_t v1) {
  interface->screenwriter.vline(interface->screenwriter.arg, color, u, v0, v1);
}
