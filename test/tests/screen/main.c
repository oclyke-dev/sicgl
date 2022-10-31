#include "sicgl/screen.h"
#include "utils.h"

void setUp(void) {
  // set stuff up here
}

void tearDown(void) {
  // clean stuff up here
}

void test_utils_new_screen(void) {
  const uext_t width = 1204;
  const uext_t height = 642;
  const ext_t u0 = 74;
  const ext_t v0 = -340;
  const ext_t u1 = u0 + width;
  const ext_t v1 = v0 + height;
  const ext_t lu = 2342340;
  const ext_t lv = 452012;
  screen_t* screen = new_screen(u0, v0, u1, v1, lu, lv);
  TEST_ASSERT_NOT_NULL(screen);
  if (TEST_PROTECT()) {
    TEST_ASSERT_EQUAL_INT(u0, screen->u0);
    TEST_ASSERT_EQUAL_INT(v0, screen->v0);
    TEST_ASSERT_EQUAL_INT(u1, screen->u1);
    TEST_ASSERT_EQUAL_INT(v1, screen->v1);
    TEST_ASSERT_EQUAL_INT(lu, screen->lu);
    TEST_ASSERT_EQUAL_INT(lv, screen->lv);
  } else {
    release_screen(screen);
  }
}

void test_screen_normalize(void) {
  int ret = 0;
  uext_t width = 632;
  uext_t height = 155;
  ext_t umin = -23;
  ext_t vmin = 456;
  ext_t umax = umin + width;
  ext_t vmax = vmin + height;
  ext_t lu = -69;
  ext_t lv = 420;
  ext_t _gu0 = lu + umin;
  ext_t _gv0 = lv + vmin;
  ext_t _gu1 = lu + umax;
  ext_t _gv1 = lv + vmax;
  screen_t* screen = new_screen(umax, vmax, umin, vmin, lu, lv);
  TEST_ASSERT_NOT_NULL(screen);
  if (TEST_PROTECT()) {
    TEST_ASSERT_EQUAL_INT_MESSAGE(
        0, screen_normalize(screen), "failed to normalize");
    TEST_ASSERT_EQUAL_INT(umin, screen->u0);
    TEST_ASSERT_EQUAL_INT(vmin, screen->v0);
    TEST_ASSERT_EQUAL_INT(umax, screen->u1);
    TEST_ASSERT_EQUAL_INT(vmax, screen->v1);
    TEST_ASSERT_EQUAL_INT(lu, screen->lu);
    TEST_ASSERT_EQUAL_INT(lv, screen->lv);
    TEST_ASSERT_EQUAL_INT(_gu0, screen->_gu0);
    TEST_ASSERT_EQUAL_INT(_gv0, screen->_gv0);
    TEST_ASSERT_EQUAL_INT(_gu1, screen->_gu1);
    TEST_ASSERT_EQUAL_INT(_gv1, screen->_gv1);

    // another case:
    screen_set(screen, 0, 0, -64, 38, 231, -5);
    ret = screen_normalize(screen);
    TEST_ASSERT_EQUAL_INT_MESSAGE(0, ret, "failed to normalize");
    TEST_ASSERT_EQUAL_INT(-64, screen->u0);
    TEST_ASSERT_EQUAL_INT(0, screen->v0);
    TEST_ASSERT_EQUAL_INT(0, screen->u1);
    TEST_ASSERT_EQUAL_INT(38, screen->v1);

  } else {
    release_screen(screen);
  }
}

void test_screen_intersect(void) {
  screen_t* s0 = new_screen(0, 0, 0, 0, 0, 0);
  screen_t* s1 = new_screen(0, 0, 0, 0, 0, 0);
  screen_t* intersection = new_screen(0, 0, 0, 0, 0, 0);
  TEST_ASSERT_NOT_NULL(s0);
  TEST_ASSERT_NOT_NULL(s1);
  TEST_ASSERT_NOT_NULL(intersection);

  // begin tests
  if (TEST_PROTECT()) {
    int ret = 0;

    // case 1: no overlap
    screen_set(s0, 0, 0, 2, 2, 1, 1);    // 3x3 screen top-left at (1, 1)
    screen_set(s1, 0, 0, 2, 2, -3, -3);  // 3x3 screen bottom-right at (-1, -1)
    screen_normalize(s0);
    screen_normalize(s1);
    ret = screen_intersect(intersection, s0, s1);
    TEST_ASSERT_MESSAGE((ret != 0), "case 1: screens should not intersect");

    // case 2: little overlap
    screen_set(s0, 0, 0, 2, 2, 0, 0);    // 3x3 screen top-left at (0, 0)
    screen_set(s1, 0, 0, 2, 2, -2, -2);  // 3x3 screen bottom-right at (0, 0)
    screen_normalize(s0);
    screen_normalize(s1);
    ret = screen_intersect(intersection, s0, s1);
    TEST_ASSERT_EQUAL_INT(0, ret);
    TEST_ASSERT_EQUAL_INT(0, intersection->u0);
    TEST_ASSERT_EQUAL_INT(0, intersection->v0);
    TEST_ASSERT_EQUAL_INT(0, intersection->u1);
    TEST_ASSERT_EQUAL_INT(0, intersection->v1);
    TEST_ASSERT_EQUAL_INT(0, intersection->lu);
    TEST_ASSERT_EQUAL_INT(0, intersection->lv);
    TEST_ASSERT_EQUAL_INT(0, intersection->_gu0);
    TEST_ASSERT_EQUAL_INT(0, intersection->_gv0);
    TEST_ASSERT_EQUAL_INT(0, intersection->_gu1);
    TEST_ASSERT_EQUAL_INT(0, intersection->_gv1);

    // case 3: more overlap
    screen_set(s0, 0, 0, 6, 6, 0, 0);  // 7x7 screen top-left at (0, 0)
    screen_set(s1, 0, 0, 2, 2, 1, 1);  // 3x3 screen top-left at (1, 1) (should
                                       // be engulfed by larger screen)
    screen_normalize(s0);
    screen_normalize(s1);
    ret = screen_intersect(intersection, s0, s1);
    TEST_ASSERT_EQUAL_INT(0, ret);
    TEST_ASSERT_EQUAL_INT(
        0, intersection->u0);  // intersection has (u0, v0) == (0, 0)
    TEST_ASSERT_EQUAL_INT(0, intersection->v0);
    TEST_ASSERT_EQUAL_INT(s1->u1, intersection->u1);
    TEST_ASSERT_EQUAL_INT(s1->v1, intersection->v1);
    TEST_ASSERT_EQUAL_INT(s1->lu, intersection->lu);
    TEST_ASSERT_EQUAL_INT(s1->lv, intersection->lv);
    TEST_ASSERT_EQUAL_INT(s1->_gu0, intersection->_gu0);
    TEST_ASSERT_EQUAL_INT(s1->_gv0, intersection->_gv0);
    TEST_ASSERT_EQUAL_INT(s1->_gu1, intersection->_gu1);
    TEST_ASSERT_EQUAL_INT(s1->_gv1, intersection->_gv1);

    // case 4: identical
    screen_set(s0, 0, 0, -64, 38, 231, -5);  // this screen is a mess
    screen_set(s1, 0, 0, -64, 38, 231, -5);  // and this one is identically bad
    screen_normalize(s0);
    screen_normalize(s1);
    ret = screen_intersect(intersection, s0, s1);
    TEST_ASSERT_EQUAL_INT(0, ret);
    TEST_ASSERT_EQUAL_INT(0, intersection->u0);
    TEST_ASSERT_EQUAL_INT(0, intersection->v0);
    TEST_ASSERT_EQUAL_INT(
        intersection->u1, intersection->_gu1 - intersection->_gu0);
    TEST_ASSERT_EQUAL_INT(
        intersection->v1, intersection->_gv1 - intersection->_gv0);

    // // helpful print statements
    // printf("s0:\n");
    // show_screen(s0);
    // printf("\ns1:\n");
    // show_screen(s1);
    // printf("return value: %d\n", ret);
    // show_screen(intersection);
  } else {
    // cleanup on failure
    release_screen(s0);
    release_screen(s1);
    release_screen(intersection);
  }
}

void test_screen_clip_hline(void) {
  int ret = 0;
  screen_t screen;
  screen_set(&screen, 0, 0, 0, 0, 0, 0);
  ext_t u0, v, u1;
  if (TEST_PROTECT()) {
    // check null inputs
    ret = screen_clip_hline(NULL, &u0, &v, &u1);
    TEST_ASSERT_LESS_THAN_INT32_MESSAGE(
        0, ret, "should return negative error code");

    ret = screen_clip_hline(&screen, NULL, &v, &u1);
    TEST_ASSERT_LESS_THAN_INT32_MESSAGE(
        0, ret, "should return negative error code");

    ret = screen_clip_hline(&screen, &u0, NULL, &u1);
    TEST_ASSERT_LESS_THAN_INT32_MESSAGE(
        0, ret, "should return negative error code");

    ret = screen_clip_hline(&screen, &u0, &v, NULL);
    TEST_ASSERT_LESS_THAN_INT32_MESSAGE(
        0, ret, "should return negative error code");

    // 3x3 screen
    ret = screen_set(&screen, 0, 0, 2, 2, 0, 0);
    TEST_ASSERT_EQUAL_INT(0, ret);

    // test lines which should not be clipped
    u0 = 0;
    u1 = 2;
    v = 1;
    ret = screen_clip_hline(&screen, &u0, &v, &u1);
    TEST_ASSERT_EQUAL_INT(0, ret);
    TEST_ASSERT_EQUAL_INT(0, u0);
    TEST_ASSERT_EQUAL_INT(2, u1);
    TEST_ASSERT_EQUAL_INT(1, v);

    // test lines which should be clipped
    u0 = 2;
    u1 = 60;
    v = 1;
    ret = screen_clip_hline(&screen, &u0, &v, &u1);
    TEST_ASSERT_EQUAL_INT(0, ret);
    TEST_ASSERT_EQUAL_INT(2, u0);
    TEST_ASSERT_EQUAL_INT(2, u1);
    TEST_ASSERT_EQUAL_INT(1, v);

    u0 = -655;
    u1 = 1;
    v = 0;
    ret = screen_clip_hline(&screen, &u0, &v, &u1);
    TEST_ASSERT_EQUAL_INT(0, ret);
    TEST_ASSERT_EQUAL_INT(0, u0);
    TEST_ASSERT_EQUAL_INT(1, u1);
    TEST_ASSERT_EQUAL_INT(0, v);

    u0 = -655;
    u1 = 4234;
    v = 0;
    ret = screen_clip_hline(&screen, &u0, &v, &u1);
    TEST_ASSERT_EQUAL_INT(0, ret);
    TEST_ASSERT_EQUAL_INT(0, u0);
    TEST_ASSERT_EQUAL_INT(2, u1);
    TEST_ASSERT_EQUAL_INT(0, v);

    // test lines which have no pixels to draw
    u0 = 0;
    u1 = 1;
    v = -1;
    ret = screen_clip_hline(&screen, &u0, &v, &u1);
    TEST_ASSERT_GREATER_THAN_INT32(0, ret);

    u0 = 0;
    u1 = 1;
    v = 3;
    ret = screen_clip_hline(&screen, &u0, &v, &u1);
    TEST_ASSERT_GREATER_THAN_INT32(0, ret);
  } else {
    // this area for cleanup of dynamically allocated items
  }
}

void test_screen_clip_vline(void) {
  int ret = 0;
  screen_t screen;
  screen_set(&screen, 0, 0, 0, 0, 0, 0);
  ext_t u, v0, v1;
  if (TEST_PROTECT()) {
    // check null inputs
    ret = screen_clip_vline(NULL, &u, &v0, &v1);
    TEST_ASSERT_LESS_THAN_INT32_MESSAGE(
        0, ret, "should return negative error code");

    ret = screen_clip_vline(&screen, NULL, &v0, &v1);
    TEST_ASSERT_LESS_THAN_INT32_MESSAGE(
        0, ret, "should return negative error code");

    ret = screen_clip_vline(&screen, &u, NULL, &v1);
    TEST_ASSERT_LESS_THAN_INT32_MESSAGE(
        0, ret, "should return negative error code");

    ret = screen_clip_vline(&screen, &u, &v0, NULL);
    TEST_ASSERT_LESS_THAN_INT32_MESSAGE(
        0, ret, "should return negative error code");

    // 3x3 screen
    ret = screen_set(&screen, 0, 0, 2, 2, 0, 0);
    TEST_ASSERT_EQUAL_INT(0, ret);

    // test lines which should not be clipped
    u = 0;
    v0 = 2;
    v1 = 1;
    ret = screen_clip_vline(&screen, &u, &v0, &v1);
    TEST_ASSERT_EQUAL_INT(0, ret);
    TEST_ASSERT_EQUAL_INT(0, u);
    TEST_ASSERT_EQUAL_INT(2, v0);
    TEST_ASSERT_EQUAL_INT(1, v1);

    // test lines which should be clipped
    u = 1;
    v0 = 2;
    v1 = 60;
    ret = screen_clip_vline(&screen, &u, &v0, &v1);
    TEST_ASSERT_EQUAL_INT(0, ret);
    TEST_ASSERT_EQUAL_INT(1, u);
    TEST_ASSERT_EQUAL_INT(2, v0);
    TEST_ASSERT_EQUAL_INT(2, v1);

    u = 0;
    v0 = -655;
    v1 = 1;
    ret = screen_clip_vline(&screen, &u, &v0, &v1);
    TEST_ASSERT_EQUAL_INT(0, ret);
    TEST_ASSERT_EQUAL_INT(0, u);
    TEST_ASSERT_EQUAL_INT(0, v0);
    TEST_ASSERT_EQUAL_INT(1, v1);

    u = 0;
    v0 = -655;
    v1 = 4234;
    ret = screen_clip_vline(&screen, &u, &v0, &v1);
    TEST_ASSERT_EQUAL_INT(0, ret);
    TEST_ASSERT_EQUAL_INT(0, u);
    TEST_ASSERT_EQUAL_INT(0, v0);
    TEST_ASSERT_EQUAL_INT(2, v1);

    // test lines which have no pixels to draw
    u = -1;
    v0 = 0;
    v1 = 1;
    ret = screen_clip_vline(&screen, &u, &v0, &v1);
    TEST_ASSERT_GREATER_THAN_INT32(0, ret);

    u = 3;
    v0 = 0;
    v1 = 1;
    ret = screen_clip_vline(&screen, &u, &v0, &v1);
    TEST_ASSERT_GREATER_THAN_INT32(0, ret);
  } else {
    // this area for cleanup of dynamically allocated items
  }
}

void test_screen_clip_diagonal(void) {
  int ret = 0;
  screen_t screen;
  screen_set(&screen, 0, 0, 0, 0, 0, 0);
  ext_t u, v, diru, dirv;
  uext_t count;
  if (TEST_PROTECT()) {
    // check null inputs
    ret = screen_clip_diagonal(NULL, &u, &v, diru, dirv, &count);
    TEST_ASSERT_LESS_THAN_INT32_MESSAGE(
        0, ret, "should return negative error code");

    ret = screen_clip_diagonal(&screen, NULL, &v, diru, dirv, &count);
    TEST_ASSERT_LESS_THAN_INT32_MESSAGE(
        0, ret, "should return negative error code");

    ret = screen_clip_diagonal(&screen, &u, NULL, diru, dirv, &count);
    TEST_ASSERT_LESS_THAN_INT32_MESSAGE(
        0, ret, "should return negative error code");

    ret = screen_clip_diagonal(&screen, &u, &v, diru, dirv, NULL);
    TEST_ASSERT_LESS_THAN_INT32_MESSAGE(
        0, ret, "should return negative error code");

    // 3x3 screen
    ret = screen_set(&screen, 0, 0, 2, 2, 0, 0);
    TEST_ASSERT_EQUAL_INT(0, ret);

    // test lines which should not be clipped
    u = 0;
    v = 0;
    diru = 1;
    dirv = 1;
    count = 3;
    ret = screen_clip_diagonal(&screen, &u, &v, diru, dirv, &count);
    TEST_ASSERT_EQUAL_INT(0, ret);
    TEST_ASSERT_EQUAL_INT(0, u);
    TEST_ASSERT_EQUAL_INT(0, v);
    TEST_ASSERT_EQUAL_INT(3, count);

    u = 2;
    v = 0;
    diru = 1;
    dirv = 1;
    count = 1;
    ret = screen_clip_diagonal(&screen, &u, &v, diru, dirv, &count);
    TEST_ASSERT_EQUAL_INT(0, ret);
    TEST_ASSERT_EQUAL_INT(2, u);
    TEST_ASSERT_EQUAL_INT(0, v);
    TEST_ASSERT_EQUAL_INT(1, count);

    u = 0;
    v = 2;
    diru = -1;
    dirv = 1;
    count = 1;
    ret = screen_clip_diagonal(&screen, &u, &v, diru, dirv, &count);
    TEST_ASSERT_EQUAL_INT(0, ret);
    TEST_ASSERT_EQUAL_INT(0, u);
    TEST_ASSERT_EQUAL_INT(2, v);
    TEST_ASSERT_EQUAL_INT(1, count);

    // test lines which should be clipped
    u = -1;
    v = -1;
    diru = 1;
    dirv = 1;
    count = 3;
    ret = screen_clip_diagonal(&screen, &u, &v, diru, dirv, &count);
    TEST_ASSERT_EQUAL_INT(0, ret);
    TEST_ASSERT_EQUAL_INT(0, u);
    TEST_ASSERT_EQUAL_INT(0, v);
    TEST_ASSERT_EQUAL_INT(2, count);

    u = -0;
    v = -2;
    diru = 1;
    dirv = 1;
    count = 3;
    ret = screen_clip_diagonal(&screen, &u, &v, diru, dirv, &count);
    TEST_ASSERT_EQUAL_INT(0, ret);
    TEST_ASSERT_EQUAL_INT(2, u);
    TEST_ASSERT_EQUAL_INT(0, v);
    TEST_ASSERT_EQUAL_INT(1, count);

    u = 5;
    v = -3;
    diru = -1;
    dirv = 1;
    count = 5;
    ret = screen_clip_diagonal(&screen, &u, &v, diru, dirv, &count);
    TEST_ASSERT_EQUAL_INT(0, ret);
    TEST_ASSERT_EQUAL_INT(2, u);
    TEST_ASSERT_EQUAL_INT(0, v);
    TEST_ASSERT_EQUAL_INT(2, count);

    // test lines which have no pixels to draw
    u = 2;
    v = -1;
    diru = 1;
    dirv = 1;
    count = 1;
    ret = screen_clip_diagonal(&screen, &u, &v, diru, dirv, &count);
    TEST_ASSERT_GREATER_THAN_INT32(0, ret);

    u = 1;
    v = -2;
    diru = 1;
    dirv = 1;
    count = 1;
    ret = screen_clip_diagonal(&screen, &u, &v, diru, dirv, &count);
    TEST_ASSERT_GREATER_THAN_INT32(0, ret);

    u = 3;
    v = -1;
    diru = 1;
    dirv = 1;
    count = 3;
    ret = screen_clip_diagonal(&screen, &u, &v, diru, dirv, &count);
    TEST_ASSERT_GREATER_THAN_INT32(0, ret);

    u = -1;
    v = -1;
    diru = -1;
    dirv = -1;
    count = 0;
    ret = screen_clip_diagonal(&screen, &u, &v, diru, dirv, &count);
    TEST_ASSERT_GREATER_THAN_INT32(0, ret);

  } else {
    // this area for cleanup of dynamically allocated items
  }
}

void test_screen_clip_line(void) {
  int ret = 0;
  screen_t screen;
  screen_set(&screen, 0, 0, 0, 0, 0, 0);
  ext_t u0, v0, u1, v1;
  uext_t count;
  if (TEST_PROTECT()) {
    // check null inputs
    ret = screen_clip_line(NULL, &u0, &v0, &u1, &v1);
    TEST_ASSERT_LESS_THAN_INT32_MESSAGE(
        0, ret, "should return negative error code");

    ret = screen_clip_line(&screen, NULL, &v0, &u1, &v1);
    TEST_ASSERT_LESS_THAN_INT32_MESSAGE(
        0, ret, "should return negative error code");

    ret = screen_clip_line(&screen, &u0, NULL, &u1, &v1);
    TEST_ASSERT_LESS_THAN_INT32_MESSAGE(
        0, ret, "should return negative error code");

    ret = screen_clip_line(&screen, &u0, &v0, NULL, &v1);
    TEST_ASSERT_LESS_THAN_INT32_MESSAGE(
        0, ret, "should return negative error code");

    ret = screen_clip_line(&screen, &u0, &v0, &u1, NULL);
    TEST_ASSERT_LESS_THAN_INT32_MESSAGE(
        0, ret, "should return negative error code");

    // 8x8 screen
    ret = screen_set(&screen, 0, 0, 7, 7, 0, 0);
    TEST_ASSERT_EQUAL_INT(0, ret);

    // this is a test case encountered in real life
    u0 = 1;
    v0 = 1;
    u1 = 0;
    v1 = 6;
    ret = screen_clip_line(&screen, &u0, &v0, &u1, &v1);
    TEST_ASSERT_EQUAL_INT(0, ret);
    TEST_ASSERT_EQUAL_INT(1, u0);
    TEST_ASSERT_EQUAL_INT(1, v0);
    TEST_ASSERT_EQUAL_INT(0, u1);
    TEST_ASSERT_EQUAL_INT(6, v1);
  }

  // this area for cleanup of dynamically allocated items
}

// not needed when using generate_test_runner.rb
int main(void) {
  UNITY_BEGIN();
  RUN_TEST(test_utils_new_screen);
  RUN_TEST(test_screen_normalize);
  RUN_TEST(test_screen_intersect);
  RUN_TEST(test_screen_clip_hline);
  RUN_TEST(test_screen_clip_vline);
  RUN_TEST(test_screen_clip_diagonal);
  RUN_TEST(test_screen_clip_line);
  return UNITY_END();
}
