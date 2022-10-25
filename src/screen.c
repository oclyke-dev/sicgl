#include "sicgl/screen.h"

#include <errno.h>
#include <stddef.h>

#include "sicgl/minmax.h"

/**
 * @brief Set the public members of a screen all at once.
 * Note: this function does not normalize the screen.
 *
 * @param screen
 * @return int
 */
int screen_set(
    screen_t* screen, ext_t u0, ext_t v0, ext_t u1, ext_t v1, ext_t lu,
    ext_t lv) {
  int ret = 0;
  if (NULL == screen) {
    ret = -ENOMEM;
    goto out;
  }

  // apply public properties
  screen->u0 = u0;
  screen->v0 = v0;
  screen->u1 = u1;
  screen->v1 = v1;
  screen->lu = lu;
  screen->lv = lv;

out:
  return ret;
}

/**
 * @brief Normalize a screen for subsequent operations.
 * This function enforces assumptions about screen definition.
 *
 * @param screen
 * @return int
 */
int screen_normalize(screen_t* screen) {
  int ret = 0;
  ext_t tmp;
  if (NULL == screen) {
    ret = -ENOMEM;
    goto out;
  }

  // enforce u0 <= u1
  // it is valid to swap only the u coordinates borders share corners
  if (screen->u1 < screen->u0) {
    tmp = screen->u0;
    screen->u0 = screen->u1;
    screen->u1 = tmp;
  }

  // enforce v0 <= v1
  // it is valid to swap only the v coordinates borders share corners
  if (screen->v1 < screen->v0) {
    tmp = screen->v0;
    screen->v0 = screen->v1;
    screen->v1 = tmp;
  }

  // compute global location
  screen->_gu0 = screen->lu + screen->u0;
  screen->_gv0 = screen->lv + screen->v0;
  screen->_gu1 = screen->lu + screen->u1;
  screen->_gv1 = screen->lv + screen->v1;

out:
  return ret;
}

/**
 * @brief Intersect screens so that target defines
 * the common area between them. This intersection
 * is computed in global coordinates.
 *
 * Input screens must be normalized prior.
 *
 * If there is no intersection a negative error code
 * is returned, otherwise zero.
 *
 * @param target
 * @param s0
 * @param s1
 * @return int
 */
int screen_intersect(screen_t* target, screen_t* s0, screen_t* s1) {
  int ret = 0;
  if ((NULL == s0) || (NULL == s1)) {
    ret = -ENOMEM;
    goto out;
  }

  // check for complete disagreement
  if ((s0->_gu1 < s1->_gu0) || (s0->_gv1 < s1->_gv0) || (s1->_gu1 < s0->_gu0) ||
      (s1->_gv1 < s0->_gv0)) {
    ret = -EEXIST;
    goto out;
  }

  // optionally fill the target with the intersection
  if (NULL != target) {
    // determine global coordinates of intersection
    target->_gu0 = max(s0->_gu0, s1->_gu0);
    target->_gv0 = max(s0->_gv0, s1->_gv0);
    target->_gu1 = min(s0->_gu1, s1->_gu1);
    target->_gv1 = min(s0->_gv1, s1->_gv1);

    // arbitrarily set the origin to upper-left
    target->lu = target->_gu0;
    target->lv = target->_gv0;

    // set the new screen coordinates in local frame
    target->u0 = 0;
    target->v0 = 0;
    target->u1 = target->_gu1 - target->_gu0;
    target->v1 = target->_gv1 - target->_gv0;
  }

out:
  return ret;
}
