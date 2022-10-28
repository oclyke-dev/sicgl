#include <errno.h>

#include "sicgl/color_sequence.h"
#include "sicgl/debug.h"

int color_sequence_set(
    color_sequence_t* sequence, color_sequence_type_e type, size_t bpp,
    uint8_t* buffer, size_t length) {
  int ret = 0;
  if (NULL == sequence) {
    ret = -ENOMEM;
    goto out;
  }
  if (NULL == buffer) {
    ret = -ENOMEM;
    goto out;
  }

  // apply public properties
  sequence->type = type;
  sequence->bpp = bpp;
  sequence->buffer = buffer;
  sequence->length = length;

out:
  return ret;
}
