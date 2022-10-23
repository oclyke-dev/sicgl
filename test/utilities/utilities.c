#include "gd.h"
#include "test_utils.h"

#include <stdio.h>

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
