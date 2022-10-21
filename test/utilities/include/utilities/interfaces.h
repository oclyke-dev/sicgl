#pragma once

#include <stdlib.h>

#include "sicgl.h"

static inline generic_interface_t* new_generic_interface(void) {
  return calloc(1, sizeof(generic_interface_t));
}

static inline specific_interface_t* new_specific_interface(void) {
  return calloc(1, sizeof(specific_interface_t));
}
