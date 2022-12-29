#pragma once

#include <stdbool.h>

#include "sicgl/color_sequence.h"
#include "sicgl/interface.h"
#include "sicgl/screen.h"

int sicgl_specific_scalar_field(
    interface_t* interface, screen_t* screen, double* scalars,
    color_sequence_t* sequence, bool discrete, bool circular);
