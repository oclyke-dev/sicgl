#pragma once

#include <stdbool.h>

#include "sicgl/color_sequence.h"
#include "sicgl/interface.h"
#include "sicgl/screen.h"

#ifdef __cplusplus
extern "C" {
#endif

int sicgl_scalar_field(
    interface_t* interface, screen_t* field, double* scalars, double offset,
    color_sequence_t* sequence, sequence_map_fn map);

#ifdef __cplusplus
}
#endif
