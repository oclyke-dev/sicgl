#pragma once

#include "sicgl/extent.h"

// a screen which exists within the global pixel space
typedef struct _screen_t {
  // corners of the screen
  // relative to the screen's origin (0, 0)
  // corner coordinates are inclusive
  // the corners (u0, v0) and (u1, v1) must satisfy:
  // u0 <= u1
  // v0 <= v1
  ext_t u0;
  ext_t v0;
  ext_t u1;
  ext_t v1;

  // location of the screen in global space
  // relative to the global origin (0, 0)
  ext_t lu;
  ext_t lv;

  // private
  // global screen corners
  // derived from local corners and global offset during normalization
  ext_t _gu0;
  ext_t _gv0;
  ext_t _gu1;
  ext_t _gv1;
} screen_t;

int screen_set(
    screen_t* screen, ext_t u0, ext_t v0, ext_t u1, ext_t v1, ext_t lu,
    ext_t lv);
int screen_normalize(screen_t* screen);
int screen_intersect(screen_t* target, screen_t* s0, screen_t* s1);
