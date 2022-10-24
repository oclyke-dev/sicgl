#pragma once

#include "sicgl.h"
#include "utilities/interfaces.h"
#include "utilities/png.h"

generic_interface_t* new_png_generic_interface_partial(
    png_t* png, generic_interface_t prototype);
generic_interface_t* new_png_generic_interface_full(png_t* png);
specific_interface_t* new_png_specific_interface(
    png_t* png, screen_t* screen, uint8_t* scratch, size_t scratch_length);

int release_png_generic_interface(generic_interface_t* interface);
int release_png_specific_interface(specific_interface_t* interface);
