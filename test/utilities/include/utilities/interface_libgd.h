#pragma once

#include "gd.h"
#include "sicgl_generic.h"
#include "sicgl_specific.h"
#include "utilities/png.h"

generic_interface_t* new_libgd_generic_interface_partial(
    gdImage* image, generic_interface_t prototype);
generic_interface_t* new_libgd_generic_interface_full(gdImage* image);
specific_interface_t* new_libgd_specific_interface(
    display_t* display, uint8_t* scratch, size_t scratch_length);

int release_libgd_generic_interface(generic_interface_t* interface);
int release_libgd_specific_interface(specific_interface_t* interface);

int libgd_specific_interface_show_memory(specific_interface_t* interface);
png_t* new_png_from_libgd_specific_interface(specific_interface_t* interface);
