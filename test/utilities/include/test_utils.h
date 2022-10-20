#pragma once

// unity provides unit test framework
#include "unity.h"

// include additional apis
#include "utilities/png.h"
#include "utilities/image.h"
#include "utilities/screen.h"

// include interface definitions
#include "utilities/interfaces.h"
#include "utilities/interface_bytes.h"
#include "utilities/interface_libgd.h"
#include "utilities/interface_png.h"

// what are common test operations?
// * create images
// * write images to file (preview them)
// * compare images
// * directly compare drawing functions fr sicgl to the equivalent from libgd

// from this point out we will standardize around using the libgd image definition for storage

// color conversions
png_pixel_t png_color_from_truecolor(int truecolor);
int truecolor_from_png_pixel(png_pixel_t pixel);
