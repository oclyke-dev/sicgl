#include "sicgl.h"
#include "unity.h"

#include "range.h"

void test_iterator_bare_range(void) {
  const int32_t min = -69;
  const int32_t max = 421; // think of python range(min, max)... max is not inclusive
  const int32_t expected_steps = max - min;
  range_t range;
  range_init(&range, min, max);

  // create iterator based on the range type
  iter_t iter;
  iter.first = range_first;
  iter.next = range_next;
  iter.done = range_done;
  iter.args = (void*)&range;

  // run through iterator
  size_t count = 0;
  for (range_t* s = (range_t*)iter.first(&range); !iter.done(s); s = (range_t*)iter.next(s)) {
    // printf("val: %d\n", s->val);
    count++;
  }

  // assertions
  TEST_ASSERT_EQUAL_INT(expected_steps, count); // proper number of steps
  TEST_ASSERT_EQUAL_INT(max, range.val); // proper ending value
}
