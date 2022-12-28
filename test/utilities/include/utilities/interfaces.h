#pragma once

#include <stdlib.h>

#include "sicgl_specific.h"

static inline specific_interface_t* new_specific_interface(void) {
  return calloc(1, sizeof(specific_interface_t));
}
