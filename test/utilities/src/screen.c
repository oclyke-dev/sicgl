#include "sicgl/screen.h"

#include "utils.h"

screen_t* new_screen(
    ext_t u0, ext_t v0, ext_t u1, ext_t v1, ext_t lu, ext_t lv) {
  screen_t* screen = (screen_t*)malloc(sizeof(screen_t));
  if (screen == NULL) {
    goto out;
  }

  // zero the screen
  // (yes, calloc could do the same but this is more
  // explicit and the anticipated performance penalties
  // are small enough to be of no concern)
  memset(screen, 0U, sizeof(*screen));

  // set the properties
  int ret = screen_set(screen, u0, v0, u1, v1, lu, lv);
  if (0 != ret) {
    release_screen(screen);
    screen = NULL;
    goto out;
  }

out:
  return screen;
}

screen_t* new_screen_extent(ext_t width, ext_t height, ext_t lu, ext_t lv) {
  screen_t* screen = NULL;
  screen = new_screen(0, 0, width - 1, height - 1, lu, lv);

  // normalize the screen to apply the width / height
  int ret = screen_normalize(screen);
  if (0 != ret) {
    release_screen(screen);
    screen = NULL;
    goto out;
  }

out:
  return screen;
}

int release_screen(screen_t* screen) {
  int ret = 0;
  free(screen);
out:
  return ret;
}

/**
 * @brief Print screen information.
 *
 * @param screen
 * @return int
 */
int show_screen(screen_t* screen) {
  int ret = 0;
  if (NULL == screen) {
    ret = -ENOMEM;
    goto out;
  }
  printf("screen:\n");
  printf(
      "\tcorners (local): (%d, %d), (%d, %d)\n", screen->u0, screen->v0,
      screen->u1, screen->v1);
  printf(
      "\tcorners (global): (%d, %d), (%d, %d)\n", screen->_gu0, screen->_gv0,
      screen->_gu1, screen->_gv1);
  printf("\tlocation (global): (%d, %d)\n", screen->lu, screen->lv);

out:
  return ret;
}
