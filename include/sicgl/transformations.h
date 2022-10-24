#pragma once

#include "sicgl/types.h"

// screen transformations
int transform_screen_to_global(screen_t* screen, ext_t* u, ext_t* v);
int transform_global_to_screen(screen_t* screen, ext_t* u, ext_t* v);
