#include "gd.h"
#include "sicgl.h"
#include "test_utils.h"

/**
 * @brief Apply transformation to coordinates for use in libgd.
 *
 */
static int apply_screen_transformation(
    screen_t* screen, int* x0, int* y0, int* x1, int* y1) {
  int ret = 0;
  ret = transform_screen_to_global(screen, x0, y0);
  if (0 != ret) {
    goto out;
  }
  ret = transform_screen_to_global(screen, x1, y1);
  if (0 != ret) {
    goto out;
  }
out:
  return ret;
}

/**
 * @brief
 *
 * @param reference
 * @param image
 * @param width
 * @param height
 * @param u0
 * @param v0
 * @param u1
 * @param v1
 * @param color
 * @return int
 */
int simultaneous_line(
    gdImage** reference, gdImage** image, uext_t width, uext_t height,
    screen_t* screen, ext_t u0, ext_t v0, ext_t u1, ext_t v1, int color) {
  int ret = 0;
  uint8_t buffer[width];

  // check inputs
  if ((NULL == image) || (NULL == reference) || (NULL == screen)) {
    ret = -EINVAL;
    goto out;
  }

  // create image for libgd
  *reference = gdImageCreateTrueColor(width, height);
  if (NULL == *reference) {
    ret = -ENOMEM;
    goto out;
  }

  // // create coordinates for libgd
  // int x0 = u0;
  // int y0 = v0;
  // int x1 = u1;
  // int y1 = v1;
  // if (NULL != screen) {
  //   ret = apply_screen_transformation(screen, &x0, &y0, &x1, &y1);
  //   if (0 != ret) {
  //     goto out;
  //   }
  // }

  // create interface(s)
  specific_interface_t* specific =
      new_libgd_specific_interface(screen, buffer, width);
  if (NULL == specific) {
    printf("failed to create specific interface\n");
    ret = -EINVAL;
    goto out;
  }

  // draw to each interface
  sicgl_line(specific, screen, &color, u0, v0, u1, v1);
  gdImageLine(*reference, u0, v0, u1, v1, color);

  // convert image to gd
  *image = new_image_from_libgd_specific_interface(specific);
  if (NULL == *image) {
    printf("failed to make image from libgd interface\n");
    ret = -ENOMEM;
    goto cleanup;
  }

cleanup:
  release_libgd_specific_interface(specific);
out:
  return ret;
}
