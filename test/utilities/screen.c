#include <stdlib.h>

#include "sicgl.h"

screen_t* new_screen(uext_t width, uext_t height, ext_t u0, ext_t v0) {
  screen_t* screen = (screen_t*)malloc(sizeof(screen_t));
  if (screen == NULL) {
    goto out;
  }

  // zero the screen
  memset(screen, 0U, sizeof(*screen));

  // set the properties
  screen->width = width;
  screen->height = height;
  screen->u0 = u0;
  screen->v0 = v0;

out:
  return screen;
}
