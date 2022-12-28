#pragma once

#include "gd.h"
#include "sicgl_specific.h"
#include "utilities/png.h"

specific_interface_t* new_libgd_specific_interface(
    screen_t* screen, color_t* scratch, size_t scratch_length);

int release_libgd_specific_interface(specific_interface_t* interface);

int libgd_specific_interface_show_memory(specific_interface_t* interface);
png_t* new_png_from_libgd_specific_interface(specific_interface_t* interface);
