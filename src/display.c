#include <errno.h>
#include <stddef.h>

#include "sicgl/debug.h"
#include "sicgl/display.h"
#include "sicgl/minmax.h"

/**
 * @brief Set the public members of a display all at once.
 * Note: this function does not normalize the display.
 *
 * @param display
 * @return int
 */
int display_set(
    display_t* display, uext_t width, uext_t height, ext_t lu, ext_t lv) {
  int ret = 0;
  if (NULL == display) {
    ret = -ENOMEM;
    goto out;
  }

  // apply public properties
  display->width = width;
  display->height = height;
  display->lu = lu;
  display->lv = lv;

out:
  return ret;
}
