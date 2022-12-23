#include "sicgl/specific/blit.h"

#include <errno.h>

#include "sicgl/debug.h"
#include "sicgl/screen.h"

/**
 * @brief Bit-blit a sprite into the region determined by screen upon the
 * interface.
 *
 * @param interface
 * @param screen
 * @param sprite
 * @return int
 */
int sicgl_specific_blit(
    specific_interface_t* interface, screen_t* screen, color_t* sprite) {
  int ret = 0;

  if (NULL == interface) {
    goto out;
  }
  if (NULL == screen) {
    ret = -ENOMEM;
  }

  // find screen overlap
  screen_t target;
  ret = screen_intersect(&target, screen, &interface->screen);
  if (ret == SICGL_SCREEN_INTERSECTION_NONEXISTENT) {
    ret = 0;
    goto out;
  } else if (0 != ret) {
    goto out;
  }

  printf("target overlap: \n");
  printf("width: %d, height: %d\n", target.width, target.height);

out:
  return ret;
}
