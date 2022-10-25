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

// not needed when using generate_test_runner.rb
int main(void) {
  UNITY_BEGIN();
  RUN_TEST(test_utils_new_screen);
  RUN_TEST(test_screen_normalize);
  RUN_TEST(test_screen_intersect);
  return UNITY_END();
}
