#include "utilities/conversion.h"

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
  return gdTrueColorAlpha(pixel.r, pixel.g, pixel.b, alpha);
}

/**
 * @brief Tool to store a LIBGD image as a PNG file.
 *
 * @param image
 * @param path
 * @return int
 */
png_t* new_png_from_image(gdImage* image) {
  png_t* png = NULL;

  // check input
  if (NULL == image) {
    goto out;
  }

  // make png from image
  size_t width = image->sx;
  size_t height = image->sy;
  png = new_png(width, height);
  if (NULL == png) {
    goto out;
  }

  // loop over image and fill png
  for (size_t v = 0; v < height; v++) {
    for (size_t u = 0; u < width; u++) {
      png->pixels[v * width + u] =
          png_color_from_truecolor(gdImageGetTrueColorPixel(image, u, v));
    }
  }

out:
  return png;
}

/**
 * @brief
 *
 * @param interface
 * @param image
 * @return gdImage*
 */
gdImage* new_image_from_libgd_specific_interface(interface_t* interface) {
  gdImage* image = NULL;

  if (NULL == interface) {
    goto out;
  }
  if (NULL == interface->screen) {
    goto out;
  }

  // prepare image
  uext_t width = interface->screen->width;
  uext_t height = interface->screen->height;
  image = gdImageCreateTrueColor(width, height);
  if (NULL == image) {
    goto out;
  }

  // convert memory
  for (size_t v = 0; v < height; v++) {
    for (size_t u = 0; u < width; u++) {
      color_t color = interface->memory[v * width + u];
      gdImageSetPixel(image, u, v, color);
    }
  }

out:
  return image;
}
