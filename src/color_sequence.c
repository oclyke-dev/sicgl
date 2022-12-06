#include "sicgl/color_sequence.h"

#include <errno.h>

#include "sicgl/debug.h"
#include "sicgl/private/interpolation.h"

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

int color_sequence_get_color_linear(
    color_sequence_t* sequence, double phase, color_t* color) {
  int ret = 0;
  if (NULL == sequence) {
    ret = -ENOMEM;
    goto out;
  }
  if (NULL == color) {
    goto out;
  }

  // linear interpolation of the color sequence
  ret = interpolate_color_linear(
      sequence->colors, sequence->length, phase, color);
  if (0 != ret) {
    goto out;
  }

out:
  return ret;
}
int color_sequence_get_color_circular(
    color_sequence_t* sequence, double phase, color_t* color) {
  int ret = 0;
  if (NULL == sequence) {
    ret = -ENOMEM;
    goto out;
  }
  if (NULL == color) {
    goto out;
  }

  // circular interpolation of the color sequence
  ret = interpolate_color_circular(
      sequence->colors, sequence->length, phase, color);
  if (0 != ret) {
    goto out;
  }

out:
  return ret;
}
