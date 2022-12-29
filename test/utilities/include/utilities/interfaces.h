#pragma once

#include <stdlib.h>

#include "sicgl.h"

static inline interface_t* new_specific_interface(void) {
  return calloc(1, sizeof(interface_t));
}
