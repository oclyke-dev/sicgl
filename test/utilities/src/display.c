#include "sicgl/display.h"

#include "utils.h"

display_t* new_display(uext_t width, uext_t height, ext_t lu, ext_t lv) {
  display_t* display = (display_t*)malloc(sizeof(display_t));
  if (display == NULL) {
    goto out;
  }

  // zero the display
  // (yes, calloc could do the same but this is more
  // explicit and the anticipated performance penalties
  // are small enough to be of no concern)
  memset(display, 0U, sizeof(*display));

  // set the properties
  int ret = display_set(display, width, height, lu, lv);
  if (0 != ret) {
    release_display(display);
    display = NULL;
    goto out;
  }

out:
  return display;
}

int release_display(display_t* display) {
  int ret = 0;
  free(display);
out:
  return ret;
}

/**
 * @brief Print display information.
 *
 * @param display
 * @return int
 */
int show_display(display_t* display) {
  int ret = 0;
  if (NULL == display) {
    ret = -ENOMEM;
    goto out;
  }

  printf("display:\n");
  printf("\twidth: %d, height: %d\n", display->width, display->height);
  printf("\tlocation (global): (%d, %d)\n", display->lu, display->lv);

out:
  return ret;
}
