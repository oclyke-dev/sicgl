#pragma once

#include <stdbool.h>

#include "sicgl/color_sequence.h"
#include "sicgl/screen.h"
#include "sicgl/specific/interface.h"

int sicgl_specific_scalar_field(
    specific_interface_t* interface, screen_t* screen, double* scalars,
    color_sequence_t* sequence, bool discrete, bool circular);
