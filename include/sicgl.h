#pragma once

#include "sicgl/types.h"
#include "sicgl/generic.h"
#include "sicgl/specific.h"

// a note about types:
// sicgl uses several distinct types each with their own purpose:
// - color_t: abstraction of color information
// - ext_t: signed coordinates within global pixel space
// - ext_t: unsigned distances within global pixel space
// - screen_t: virtual definition of a 2D rectilinear screen, this is
//     common between all sicgl functions and not dependent on interface
// - *interface_t: abstraction which allows sicgl to place colors at
//     given locations

// a note about interfaces:
// there are two types of interface
// - generic: the generic interface makes no assumptions and uses
//     function pointers to give the user total flexibility
// - specifig: the specific interface requires the user to declare a
//     fixed byte width for color information and manages memory
//     internally to increase performance.

// a note about APIs:
// there are several APIs available, each with its own intended purpose:
//
// low-level (no screen, coordinates are interface-relative (local), inputs not verified)
// - sicgl_*_generic: perform direct operations upon a generic interface
// - sicgl_*_specific: perform direct operations upon a specific interface
//
// per-screen (screen offset and dimensions are considered - coordinates are global)
// - sicgl_*_screen_generic: operate on single screen, generic interface
// - sicgl_*_screen_specific: operate on single screen, specific interface
//
// global (multiple screens)
// this is not currently implemented - it could be a feature but it is not
// terribly hard for a user to implement themselves


// // draw iterator through interface
// void sicgl_draw(interface_t* interface, iter_t* iter);
