#pragma once

#include "sicgl/interface.h"
#include "sicgl/screen.h"

#ifdef __cplusplus
extern "C" {
#endif

int sicgl_blit(interface_t* interface, screen_t* screen, color_t* sprite);

#ifdef __cplusplus
}
#endif
