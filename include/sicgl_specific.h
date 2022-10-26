#pragma once

#include "sicgl/color_sequence.h"
#include "sicgl/debug.h"
#include "sicgl/display.h"
#include "sicgl/extent.h"
#include "sicgl/screen.h"
#include "sicgl/specific.h"

// write direct-to-display
int sicgl_specific_display_line(
    specific_interface_t* interface, color_sequence_t sequence, ext_t u0,
    ext_t v0, ext_t u1, ext_t v1);
int sicgl_specific_display_rectangle(
    specific_interface_t* interface, color_sequence_t sequence, ext_t u0,
    ext_t v0, ext_t u1, ext_t v1);
int sicgl_specific_display_circle(
    specific_interface_t* interface, color_sequence_t sequence, ext_t u0,
    ext_t v0, ext_t u1, ext_t v1);
int sicgl_specific_display_ellipse(
    specific_interface_t* interface, color_sequence_t sequence, ext_t u0,
    ext_t v0, ext_t u1, ext_t v1);

// write through virtual screens
int sicgl_specific_screen_line(
    specific_interface_t* interface, screen_t* screen,
    color_sequence_t sequence, ext_t u0, ext_t v0, ext_t u1, ext_t v1);
int sicgl_specific_screen_rectangle(
    specific_interface_t* interface, screen_t* screen,
    color_sequence_t sequence, ext_t u0, ext_t v0, ext_t u1, ext_t v1);
int sicgl_specific_screen_circle(
    specific_interface_t* interface, screen_t* screen,
    color_sequence_t sequence, ext_t u0, ext_t v0, ext_t u1, ext_t v1);
int sicgl_specific_screen_ellipse(
    specific_interface_t* interface, screen_t* screen,
    color_sequence_t sequence, ext_t u0, ext_t v0, ext_t u1, ext_t v1);

// write in global coordinates through an optional screen
int sicgl_specific_global_line(
    specific_interface_t* interface, screen_t* screen,
    color_sequence_t sequence, ext_t u0, ext_t v0, ext_t u1, ext_t v1);
int sicgl_specific_global_rectangle(
    specific_interface_t* interface, screen_t* screen,
    color_sequence_t sequence, ext_t u0, ext_t v0, ext_t u1, ext_t v1);
int sicgl_specific_global_circle(
    specific_interface_t* interface, screen_t* screen,
    color_sequence_t sequence, ext_t u0, ext_t v0, ext_t u1, ext_t v1);
int sicgl_specific_global_ellipse(
    specific_interface_t* interface, screen_t* screen,
    color_sequence_t sequence, ext_t u0, ext_t v0, ext_t u1, ext_t v1);
