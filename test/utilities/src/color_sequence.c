#include "sicgl/color_sequence.h"

#include "utils.h"

color_sequence_t* new_color_sequence(
    color_sequence_type_e type, size_t bpp, uint8_t* buffer, size_t length) {
  color_sequence_t* color_sequence =
      (color_sequence_t*)malloc(sizeof(color_sequence_t));
  if (color_sequence == NULL) {
    goto out;
  }

  // zero the color_sequence
  // (yes, calloc could do the same but this is more
  // explicit and the anticipated performance penalties
  // are small enough to be of no concern)
  memset(color_sequence, 0U, sizeof(*color_sequence));

  // set the properties
  int ret = color_sequence_set(color_sequence, type, bpp, buffer, length);
  if (0 != ret) {
    release_color_sequence(color_sequence);
    color_sequence = NULL;
    goto out;
  }

out:
  return color_sequence;
}

int release_color_sequence(color_sequence_t* color_sequence) {
  int ret = 0;
  free(color_sequence);
out:
  return ret;
}

/**
 * @brief Print color_sequence information.
 *
 * @param color_sequence
 * @return int
 */
int show_color_sequence(color_sequence_t* color_sequence) {
  int ret = 0;
  if (NULL == color_sequence) {
    ret = -ENOMEM;
    goto out;
  }

  printf("color_sequence:\n");
  printf("\ttype: %d\n", color_sequence->type);
  printf("\tbpp: %lu\n", color_sequence->bpp);
  printf("\tlength (bytes): %lu\n", color_sequence->length);
  printf("\tbuffer address: 0x%016lx\n", (long)color_sequence->buffer);

out:
  return ret;
}
