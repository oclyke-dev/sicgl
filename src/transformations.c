#include "sicgl/transformations.h"

/**
 * @brief Screen transformations.
 * 
 */
int transform_screen_to_global(
  screen_t* screen,
  ext_t* u, ext_t* v
) {
  *u = *u + screen->u0;
  *v = *v + screen->v0;
  return 0;
}

int transform_global_to_screen(
  screen_t* screen,
  uext_t* u, uext_t* v
) {
  *u = *u - screen->u0;
  *v = *v - screen->v0;
  return 0;
}
