#include "range.h"
#include "sicgl.h"
#include "unity.h"

void test_iterator_bare_range(void) {
  const int32_t min = -69;
  const int32_t max =
      421;  // think of python range(min, max)... max is not inclusive
  const int32_t expected_steps = max - min;
  range_t range;
  range_init(&range, min, max);
  iter_t iter = range_get_iter(&range);

  // run through iterator
  size_t count = 0;
  for (iter.first(iter.args); !iter.done(iter.args); iter.next(iter.args)) {
    count++;
    // printf("bare range %d\n", range.val);
  }

  // assertions
  TEST_ASSERT_EQUAL_INT(expected_steps, count);  // proper number of steps
  TEST_ASSERT_EQUAL_INT(max, range.val);         // proper ending value
}
