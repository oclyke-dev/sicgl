#pragma once

#include "sicgl.h"

screen_t* new_screen(uext_t width, uext_t height, ext_t u0, ext_t v0);

int release_screen(screen_t* screen);
