#pragma once

#include "gd.h"
#include "sicgl.h"
#include "utilities/png.h"

interface_t* new_libgd_specific_interface(
    screen_t* screen, color_t* scratch, size_t scratch_length);

int release_libgd_specific_interface(interface_t* interface);

int libgd_specific_interface_show_memory(interface_t* interface);
png_t* new_png_from_libgd_specific_interface(interface_t* interface);
