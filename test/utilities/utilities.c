#include "test_utils.h"



/**
 * @brief Convert a libgd truecolor to png_pixel_t
 * 
 * @param truecolor 
 * @return png_pixel_t 
 */
png_pixel_t png_color_from_truecolor(int truecolor) {
  png_pixel_t pixel;
  pixel.r = gdTrueColorGetRed(truecolor);
  pixel.g = gdTrueColorGetGreen(truecolor);
  pixel.b = gdTrueColorGetBlue(truecolor);
  pixel.a = PNG_ALPHA_FROM_TRUECOLOR_ALPHA(gdTrueColorGetAlpha(truecolor));
  return pixel;
}

/**
 * @brief Convert a png pixel to libgd truecolor.
 * Note: conversion this way is lossy due to truecolor
 * limits on the alpha
 * 
 * @param pixel 
 * @return png_pixel_t 
 */
int truecolor_from_png_pixel(png_pixel_t pixel) {
  uint8_t alpha = (pixel.a == 0) ? 0 : ((pixel.a - 1) / 2);
  return gdTrueColorAlpha(
    pixel.r,
    pixel.g,
    pixel.b,
    alpha
  );
}
