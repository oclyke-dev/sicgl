#pragma once

#include <errno.h>

// unity provides unit test framework
#include "unity.h"

// include additional apis
#include "utilities/image.h"
#include "utilities/png.h"
#include "utilities/screen.h"
#include "utilities/conversion.h"

// include interface definitions
#include "utilities/interface_bytes.h"
#include "utilities/interface_libgd.h"
#include "utilities/interface_png.h"
#include "utilities/interfaces.h"

// what are common test operations?
// * create images
// * write images to file (preview them)
// * compare images
// * directly compare drawing functions fr sicgl to the equivalent from libgd

// from this point out we will standardize around using the libgd image
// definition for storage

// image comparison
int compare_image(gdImage* reference, gdImage* image);

// simultaneous drawing
int simultaneous_line(
  gdImage** reference,
  gdImage** image,
  uext_t width, uext_t height,
  screen_t* screen,
  ext_t u0, ext_t v0,
  ext_t u1, ext_t v1,
  int color
);
