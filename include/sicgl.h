#pragma once

#include <errno.h>
#ifdef SICGL_DEBUG_PRINTF
#include <stdio.h>
#endif  // SICGL_DEBUG_PRINTF

#include "sicgl/generic.h"
#include "sicgl/specific.h"
#include "sicgl/transformations.h"
#include "sicgl/types.h"

// a note about types:
// sicgl uses several distinct types each with their own purpose:
// - color_t: abstraction of color information
// - ext_t: signed coordinates within global pixel space
// - ext_t: unsigned distances within global pixel space
// - screen_t: virtual definition of a 2D rectilinear screen, this is
//     common between all sicgl functions and not dependent on interface
// - *interface_t: abstraction which allows sicgl to place colors at
//     given locations

/**
 * @brief The sicgl API
 *
 * sicgl assumes integer-byte widths for color types in preference of
 * speed over memory footprint. for detail see README.md
 *
 */

int sicgl_line(
    specific_interface_t* interface, screen_t* screen, color_t color, ext_t u0,
    ext_t v0, ext_t u1, ext_t v1);
int sicgl_rectangle(
    specific_interface_t* interface, screen_t* screen, color_t color, ext_t u0,
    ext_t v0, ext_t u1, ext_t v1);
int sicgl_circle(
    specific_interface_t* interface, screen_t* screen, color_t color, ext_t u0,
    ext_t v0, ext_t u1, ext_t v1);
int sicgl_ellipse(
    specific_interface_t* interface, screen_t* screen, color_t color, ext_t u0,
    ext_t v0, ext_t u1, ext_t v1);
