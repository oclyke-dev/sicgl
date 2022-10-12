#include "range.h"

#include "sicgl.h"
#include "unity.h"

static void range_count_cb(void* arg) {
  size_t* pcount = (size_t*)arg;
  (*pcount)++;
  // printf("range for each count: %d\n", *pcount);
}

void test_iterator_range(void) {
  const int32_t min = -69;
  const int32_t max =
      421;  // think of python range(min, max)... max is not inclusive
  const int32_t expected_steps = max - min;
  range_t range;
  range_init(&range, min, max);
  iter_t iter = range_get_iter(&range);

  size_t count = 0;

  // run through iterator
  iter_foreach(iter, range_count_cb, &count);

  // assertions
  TEST_ASSERT_EQUAL_INT(expected_steps, count);  // proper number of steps
  TEST_ASSERT_EQUAL_INT(max, range.val);         // proper ending value
}
