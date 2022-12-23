#pragma once

#include "sicgl/screen.h"
#include "sicgl/specific/interface.h"

int sicgl_specific_blit(
    specific_interface_t* interface, screen_t* screen, color_t* sprite);
