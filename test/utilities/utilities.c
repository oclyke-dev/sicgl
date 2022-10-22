#include "gd.h"
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
  return gdTrueColorAlpha(pixel.r, pixel.g, pixel.b, alpha);
}

int compare_image(gdImage* reference, gdImage* image) {
  if ((NULL == reference) || (NULL == image)) {
    printf("input image invalid\n");
    return -1;
  }

  // compare the lengths of the images
  if ((reference->sx != image->sx) || (reference->sy != image->sy)) {
    printf("image size mismatch\n");
    return -1;
  }

  for (size_t idv = 0; idv < reference->sy; idv++) {
    for (size_t idu = 0; idu < reference->sx; idu++) {
      int ref_pix = gdImageGetTrueColorPixel(reference, idu, idv);
      int test_pix = gdImageGetTrueColorPixel(image, idu, idv);
      if (ref_pix != test_pix) {
        printf(
            "pixel mismatch at (%lu, %lu), reference: 0x%08x, test: 0x%08x\n",
            idu, idv, ref_pix, test_pix);
        return -1;
      }
    }
  }

  return 0;
}
