#pragma once

#include "gd.h"
#include "sicgl_generic.h"
#include "sicgl_specific.h"

// generic, display
int simultaneous_generic_display_pixel(
    gdImage* image, generic_interface_t* interface, color_t color, ext_t u0,
    ext_t v0);
int simultaneous_generic_display_hline(
    gdImage* image, generic_interface_t* interface, color_t color, ext_t u0,
    ext_t v0, ext_t u1, ext_t v1);
int simultaneous_generic_display_vline(
    gdImage* image, generic_interface_t* interface, color_t color, ext_t u0,
    ext_t v0, ext_t u1, ext_t v1);
int simultaneous_generic_display_region(
    gdImage* image, generic_interface_t* interface, color_t color, ext_t u0,
    ext_t v0, ext_t u1, ext_t v1);
int simultaneous_generic_display_line(
    gdImage* image, generic_interface_t* interface, color_t color, ext_t u0,
    ext_t v0, ext_t u1, ext_t v1);
int simultaneous_generic_display_rectangle(
    gdImage* image, generic_interface_t* interface, color_t color, ext_t u0,
    ext_t v0, ext_t u1, ext_t v1);
int simultaneous_generic_display_circle(
    gdImage* image, generic_interface_t* interface, color_t color, ext_t u0,
    ext_t v0, ext_t radius);
int simultaneous_generic_display_ellipse(
    gdImage* image, generic_interface_t* interface, color_t color, ext_t u0,
    ext_t v0, ext_t major, ext_t minor);

// generic, screen
int simultaneous_generic_screen_pixel(
    gdImage* image, generic_interface_t* interface, screen_t* screen,
    color_t color, ext_t u0, ext_t v0);
int simultaneous_generic_screen_hline(
    gdImage* image, generic_interface_t* interface, screen_t* screen,
    color_t color, ext_t u0, ext_t v0, ext_t u1, ext_t v1);
int simultaneous_generic_screen_vline(
    gdImage* image, generic_interface_t* interface, screen_t* screen,
    color_t color, ext_t u0, ext_t v0, ext_t u1, ext_t v1);
int simultaneous_generic_screen_region(
    gdImage* image, generic_interface_t* interface, screen_t* screen,
    color_t color, ext_t u0, ext_t v0, ext_t u1, ext_t v1);
int simultaneous_generic_screen_line(
    gdImage* image, generic_interface_t* interface, screen_t* screen,
    color_t color, ext_t u0, ext_t v0, ext_t u1, ext_t v1);
int simultaneous_generic_screen_rectangle(
    gdImage* image, generic_interface_t* interface, screen_t* screen,
    color_t color, ext_t u0, ext_t v0, ext_t u1, ext_t v1);
int simultaneous_generic_screen_circle(
    gdImage* image, generic_interface_t* interface, screen_t* screen,
    color_t color, ext_t u0, ext_t v0, ext_t radius);
int simultaneous_generic_screen_ellipse(
    gdImage* image, generic_interface_t* interface, screen_t* screen,
    color_t color, ext_t u0, ext_t v0, ext_t major, ext_t minor);

// specific, display
int simultaneous_specific_display_pixel(
    gdImage* image, specific_interface_t* interface, color_sequence_t* sequence,
    ext_t u0, ext_t v0);
int simultaneous_specific_display_hline(
    gdImage* image, specific_interface_t* interface, color_sequence_t* sequence,
    ext_t u0, ext_t v0, ext_t u1, ext_t v1);
int simultaneous_specific_display_vline(
    gdImage* image, specific_interface_t* interface, color_sequence_t* sequence,
    ext_t u0, ext_t v0, ext_t u1, ext_t v1);
int simultaneous_specific_display_region(
    gdImage* image, specific_interface_t* interface, color_sequence_t* sequence,
    ext_t u0, ext_t v0, ext_t u1, ext_t v1);
int simultaneous_specific_display_line(
    gdImage* image, specific_interface_t* interface, color_sequence_t* sequence,
    ext_t u0, ext_t v0, ext_t u1, ext_t v1);
int simultaneous_specific_display_rectangle(
    gdImage* image, specific_interface_t* interface, color_sequence_t* sequence,
    ext_t u0, ext_t v0, ext_t u1, ext_t v1);
int simultaneous_specific_display_circle(
    gdImage* image, specific_interface_t* interface, color_sequence_t* sequence,
    ext_t u0, ext_t v0, ext_t radius);
int simultaneous_specific_display_ellipse(
    gdImage* image, specific_interface_t* interface, color_sequence_t* sequence,
    ext_t u0, ext_t v0, ext_t major, ext_t minor);

// specific, screen
int simultaneous_specific_screen_pixel(
    gdImage* image, specific_interface_t* interface, screen_t* screen,
    color_sequence_t* sequence, ext_t u0, ext_t v0);
int simultaneous_specific_screen_hline(
    gdImage* image, specific_interface_t* interface, screen_t* screen,
    color_sequence_t* sequence, ext_t u0, ext_t v0, ext_t u1, ext_t v1);
int simultaneous_specific_screen_vline(
    gdImage* image, specific_interface_t* interface, screen_t* screen,
    color_sequence_t* sequence, ext_t u0, ext_t v0, ext_t u1, ext_t v1);
int simultaneous_specific_screen_region(
    gdImage* image, specific_interface_t* interface, screen_t* screen,
    color_sequence_t* sequence, ext_t u0, ext_t v0, ext_t u1, ext_t v1);
int simultaneous_specific_screen_line(
    gdImage* image, specific_interface_t* interface, screen_t* screen,
    color_sequence_t* sequence, ext_t u0, ext_t v0, ext_t u1, ext_t v1);
int simultaneous_specific_screen_rectangle(
    gdImage* image, specific_interface_t* interface, screen_t* screen,
    color_sequence_t* sequence, ext_t u0, ext_t v0, ext_t u1, ext_t v1);
int simultaneous_specific_screen_circle(
    gdImage* image, specific_interface_t* interface, screen_t* screen,
    color_sequence_t* sequence, ext_t u0, ext_t v0, ext_t radius);
int simultaneous_specific_screen_ellipse(
    gdImage* image, specific_interface_t* interface, screen_t* screen,
    color_sequence_t* sequence, ext_t u0, ext_t v0, ext_t major, ext_t minor);
