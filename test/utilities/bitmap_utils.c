#include "utilities/bitmap_utils.h"

#include "spng.h"

void bitmap_to_file(bitmap_t const* bitmap, char const* path) {
  FILE* fp = NULL;
  fp = fopen(path, "w");
  if (fp == NULL) exit(EXIT_FAILURE);

  spng_ctx* ctx = spng_ctx_new(SPNG_CTX_ENCODER);
  spng_set_png_file(ctx, fp);

  /* set png header */
  struct spng_ihdr ihdr = {.width = bitmap->width,
                           .height = bitmap->height,
                           .bit_depth = 8,
                           .color_type = SPNG_COLOR_TYPE_TRUECOLOR_ALPHA};

  spng_set_ihdr(ctx, &ihdr);

  /* encode bitmap data */
  int error =
      spng_encode_image(ctx, &bitmap->pixels,
                        sizeof(bitmap_pixel_t) * bitmap->width * bitmap->height,
                        SPNG_FMT_PNG, SPNG_ENCODE_FINALIZE);
  if (error) {
    printf("spng_encode_image() error: %s\n", spng_strerror(error));
    exit(EXIT_FAILURE);
  }

  /* cleanup */
  spng_ctx_free(ctx);

  fclose(fp);
}

void bmp_pixel(void* arg, color_t color, uext_t u, uext_t v) {
  bitmap_t* bitmap = (bitmap_t*)arg;
  bitmap_pixel_t* bm_color = (bitmap_pixel_t*)color;

  // ensure we are within bounds
  size_t offset = bitmap->width * v + u;
  if (offset >= bitmap->num_pix) {
    return;
  }

  // set color in memory at the location
  bitmap->pixels[offset] = *bm_color;
}

void bmp_hline(void* arg, color_t color, uext_t u0, uext_t v, uext_t u1) {
  bitmap_t* bitmap = (bitmap_t*)arg;
  bitmap_pixel_t* bm_color = (bitmap_pixel_t*)color;
  // assume that coordinates are in-bounds for the bitmap

  int increment;
  size_t distance;
  if (u0 < u1) {
    increment = 1;
    distance = u1 - u0;
  } else {
    increment = -1;
    distance = u0 - u1;
  }

  // set first pixel
  bitmap_pixel_t* px = &bitmap->pixels[bitmap->width * v + u0];
  *px = *bm_color;

  // set remaining pixels
  for (size_t idx = 0; idx < distance; idx++) {
    px += increment;
    *px = *bm_color;
  }
}

void bmp_vline(void* arg, color_t color, uext_t u, uext_t v0, uext_t v1) {
  bitmap_t* bitmap = (bitmap_t*)arg;
  bitmap_pixel_t* bm_color = (bitmap_pixel_t*)color;
  // assume that coordinates are in-bounds for the bitmap

  int increment;
  size_t distance;
  if (v0 < v1) {
    increment = bitmap->width;
    distance = v1 - v0;
  } else {
    increment = -bitmap->width;
    distance = v0 - v1;
  }

  // set first pixel
  bitmap_pixel_t* px = &bitmap->pixels[bitmap->width * v0 + u];
  *px = *bm_color;

  // set remaining pixels
  for (size_t idx = 0; idx < distance; idx++) {
    px += increment;
    *px = *bm_color;
  }
}
