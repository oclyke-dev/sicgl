#pragma once

#include "sicgl/color_sequence.h"
#include "sicgl/debug.h"

color_sequence_t* new_color_sequence(
    color_sequence_type_e type, size_t bpp, uint8_t* buffer, size_t length);
int release_color_sequence(color_sequence_t* color_sequence);

int show_color_sequence(color_sequence_t* color_sequence);
