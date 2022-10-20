#include "utilities/image.h"
#include "utilities/png.h"

int image_to_file(gdImage* image, char const* path) {
  int ret = 0;

  // check input
  if (NULL == image) {
    ret = -1;
    goto out;
  }

  // make png from image
  png_t* png = new_png_from_image(image);
  if (NULL == png) {
    ret = -1;
    goto out;
  }
  if (0 != ret) {
    goto cleanup_png;
  }

  // store png to file
  ret = png_to_file(png, path);

cleanup_png:
  release_png(png);
out:
  return ret;
}
