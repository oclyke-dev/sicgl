#include "sicgl.h"
#include "gd.h"
#include "test_utils.h"

/**
 * @brief Methods of testing sicgl against libgd using identical inputs.
 * 
 */

static gdImage* new_image(uext_t width, uext_t height) {
  return gdImageCreateTrueColor(width, height);
}

/**
 * @brief Prepare identical images for comparison of sicgl against libgd.
 * 
 * @param reference 
 * @param image 
 * @param width 
 * @param height 
 * @return int 
 */
static int prep_images (
  gdImage** reference,
  gdImage** image,
  uext_t width, uext_t height
) {
  int ret = 0;

  // check outputs
  if ((NULL == reference) || (NULL == image)) {
    ret = -EINVAL;
    goto out;
  }

  // allocate images
  *reference = new_image(width, height);
  *image = new_image(width, height);

  // check allocation
  if ((NULL == *reference) || (NULL == *image)) {
    ret = -ENOMEM;
    goto out;
  }

out:
  return ret;
}

/**
 * @brief Apply transformation to coordinates for use in libgd.
 * 
 */
static int apply_screen_transformation (
  screen_t* screen,
  int* x0, int* y0,
  int* x1, int* y1
) {
  int ret = 0;
  // ret = transform_screen_to_global(screen, x0, y0);
  // if (0 != ret) {
  //   goto out;
  // }
  // ret = transform_screen_to_global(screen, x1, y1);
  // if (0 != ret) {
  //   goto out;
  // }
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
  gdImage** reference,
  gdImage** image,
  uext_t width, uext_t height,
  screen_t* screen,
  ext_t u0, ext_t v0,
  ext_t u1, ext_t v1,
  int color
) {
  int ret = 0;
  // ret = prep_images(reference, image, width, height);
  // if (0 != ret) {
  //   goto out;
  // }

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

  // // // draw to each interface
  // // sicgl_line(screen)


out:
  return ret;
}
