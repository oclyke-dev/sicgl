#pragma once

#include "utilities/png.h"

// color conversions
png_pixel_t png_color_from_truecolor(int truecolor);
int truecolor_from_png_pixel(png_pixel_t pixel);

// image conversion / creation
png_t* new_png_from_image(gdImage* image);
