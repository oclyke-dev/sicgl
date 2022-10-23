#pragma once

#include "gd.h"
#include "utilities/png.h"
#include "utilities/interfaces.h"

// color conversions
png_pixel_t png_color_from_truecolor(int truecolor);
int truecolor_from_png_pixel(png_pixel_t pixel);

// image conversion / creation
png_t* new_png_from_image(gdImage* image);
gdImage* new_image_from_libgd_specific_interface(specific_interface_t* interface);
