#pragma once

#include "gd.h"
#include "sicgl.h"
#include "utilities/interfaces.h"

generic_interface_t* new_libgd_generic_interface_partial(
    gdImage* image, generic_interface_t prototype);
generic_interface_t* new_libgd_generic_interface_full(gdImage* image);
specific_interface_t* new_libgd_specific_interface(
    gdImage* image, uint8_t* scratch, size_t scratch_length);
