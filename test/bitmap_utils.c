#include "bitmap_utils.h"

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
  bitmap_pixel_t* px = &bitmap->pixels[offset];
  px->r = bm_color->r;
  px->g = bm_color->g;
  px->b = bm_color->b;
  px->a = bm_color->a;
}
