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
