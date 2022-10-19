#include <stdio.h>
#include <stdlib.h>

#include "gd.h"
#include "spng.h"
#include "test_utils.h"

void setUp(void) {
  // set stuff up here
}

void tearDown(void) {
  // clean stuff up here
}

void test_hline(void) {
  size_t width = 10;
  size_t height = 10;
  int truecolor = truecolor_random_color();

  // create test and reference images
  gdImagePtr ref_im = gdImageCreateTrueColor(width, height);
  gdImagePtr test_im = gdImageCreateTrueColor(width, height);

  // draw to a libgd image using sicgl

  gdImageLine(ref_im, 0, 0, width - 1, height - 1, truecolor);

  // ref_im->tpixels[0] = 1;

  // // compare the memory for the two images
  // const size_t memory_len = sizeof(int) * width * height;
  // TEST_ASSERT_EQUAL_MEMORY(ref_im->tpixels, test_im->tpixels, memory_len);

  // convert the image to a PNG with spong
  bitmap_t* bm = bitmap_new(width, height);
  for (size_t y = 0; y < bm->height; ++y) {
    for (size_t x = 0; x < bm->width; ++x) {
      bitmap_pixel_t* px = &bm->pixels[bm->width * y + x];
      int tc = gdImageTrueColorPixel(test_im, x, y);

      printf("%08x ", tc);

      px->r = gdTrueColorGetRed(tc);
      px->g = gdTrueColorGetGreen(tc);
      px->b = gdTrueColorGetBlue(tc);
      px->a = PNG_ALPHA_FROM_TRUECOLOR_ALPHA(gdTrueColorGetAlpha(tc));
    }

    printf("\n");
  }

  // output the png
  bitmap_to_file(bm, "libgd_parity_test.png");
  bitmap_free(bm);

  // gdImagePtr im;
  // int cor_rad = 60;
  // im = gdImageCreateTrueColor(width, height);
  // im->alphaBlendingFlag = 0;  // turn off alpha blending
  // gdImageFilledRectangle(im, 0, 0, 399, 399,
  //                        gdTrueColorAlpha(0x00, 0x00, 0x00, TRANSPARENT));
  // gdImageFilledRectangle(im, cor_rad, cor_rad, cor_rad * 2, cor_rad * 2,
  //                        gdTrueColorAlpha(0x0F, 0xF0, 0xF0, OPAQUE));
  // gdImageEllipse(im, 2.75 * cor_rad, 3 * cor_rad, 2 * cor_rad, cor_rad,
  //                gdTrueColorAlpha(0xFF, 0x0F, 0xFF, OPAQUE));
  // gdImageFilledArc(im, cor_rad, 399 - cor_rad, cor_rad * 2, cor_rad * 2, 90,
  //                  180, gdTrueColorAlpha(0xFF, 0xFF, 0xFF, OPAQUE), gdPie);

  // // convert the image to a PNG with spong
  // bitmap_t* bm = bitmap_new(width, height);
  // for (size_t y = 0; y < bm->height; ++y) {
  //   for (size_t x = 0; x < bm->width; ++x) {
  //     bitmap_pixel_t* px = &bm->pixels[bm->width * y + x];
  //     int tc = gdImageTrueColorPixel(im, x, y);

  //     px->r = gdTrueColorGetRed(tc);
  //     px->g = gdTrueColorGetGreen(tc);
  //     px->b = gdTrueColorGetBlue(tc);
  //     px->a = PNG_ALPHA_FROM_TRUECOLOR_ALPHA(gdTrueColorGetAlpha(tc));
  //   }
  // }

  // // output the png
  // bitmap_to_file(bm, "libgd_test.png");
  // bitmap_free(bm);

  // gdImageDestroy(im);
  // return 0;
}

int main() {
  UNITY_BEGIN();
  RUN_TEST(test_hline);
  return UNITY_END();
}
