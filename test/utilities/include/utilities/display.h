#pragma once

#include "sicgl/display.h"

display_t* new_display(uext_t width, uext_t height, ext_t lu, ext_t lv);
int release_display(display_t* display);

int show_display(display_t* display);
