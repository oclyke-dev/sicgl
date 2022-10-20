#pragma once

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

#include "sicgl.h"

#include "utilities/bytes.h"

#include "utilities/interfaces.h"

generic_interface_t* new_bytes_generic_interface_partial(bytes_t* bytes, generic_interface_t prototype);
generic_interface_t* new_bytes_generic_interface_full(bytes_t* bytes);
specific_interface_t* new_bytes_specific_interface(bytes_t* bytes, uint8_t* scratch, size_t scratch_length);
