#pragma once

#include <stdbool.h>
#include <stdint.h>

#include "sicgl/iterator.h"

typedef struct _range_t {
  int32_t min;
  int32_t max;
  int32_t val;
} range_t;

static inline void* range_first(void* args) {
  range_t* range = (range_t*)args;
  (void)range;
  return args;
}
static inline void* range_next(void* args) {
  range_t* range = (range_t*)args;
  range->val++;
  return args;
}
static inline bool range_done(void* args) {
  range_t* range = (range_t*)args;
  return range->val >= range->max;
}
static inline void range_init(range_t* range, int32_t min, int32_t max) {
  range->min = min;
  range->max = max;
  range->val = min;
}

static inline iter_t range_get_iter(range_t* range) {
  iter_t iter;
  iter.first = range_first;
  iter.next = range_next;
  iter.done = range_done;
  iter.args = range;
  return iter;
}
