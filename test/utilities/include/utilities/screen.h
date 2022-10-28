#pragma once

#include "sicgl/screen.h"

screen_t* new_screen(
    ext_t u0, ext_t v0, ext_t u1, ext_t v1, ext_t lu, ext_t lv);
int release_screen(screen_t* screen);

int show_screen(screen_t* screen);
