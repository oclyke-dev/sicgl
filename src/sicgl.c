#include "sicgl.h"

void iter_foreach(iter_t* iter, void (*callback)(void*), void* init_arg) {
  for (void* arg = iter->first(init_arg); !iter->done(arg); arg = iter->next(arg)) {
    callback(arg);
  }
}

void sicgl_draw_pixel(interface_t* interface, color_t color, uext_t u, uext_t v) {
  interface->screenwriter.pixel(interface->screenwriter.arg, color, u, v);
}
