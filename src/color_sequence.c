#include "sicgl/color_sequence.h"

#include <errno.h>

#include "sicgl/debug.h"

int color_sequence_initialize(
    color_sequence_t* sequence, color_t* colors, size_t length) {
  int ret = 0;
  if (NULL == sequence) {
    ret = -ENOMEM;
    goto out;
  }
  if (NULL == colors) {
    ret = -ENOMEM;
    goto out;
  }

  // apply public properties
  sequence->colors = colors;
  sequence->length = length;

out:
  return ret;
}

int color_sequence_set_color(
    color_sequence_t* sequence, size_t idx, color_t color) {
  int ret = 0;
  if (idx >= color_sequence_length(sequence)) {
    ret = -ENOMEM;
    goto out;
  }
  sequence->colors[idx] = color;
out:
  return ret;
}

int color_sequence_get_color(
    color_sequence_t* sequence, size_t idx, color_t* color) {
  int ret = 0;
  if (NULL == color) {
    ret = -ENOMEM;
    goto out;
  }
  if (idx >= color_sequence_length(sequence)) {
    ret = -ENOMEM;
    goto out;
  }
  *color = sequence->colors[idx];
out:
  return ret;
}
