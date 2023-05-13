#include "utilities/png.h"

#include <stdlib.h>

#include "gd.h"
#include "spng.h"
#include "utils.h"

png_pixel_t png_color(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
  png_pixel_t pixel;
  pixel.r = r;
  pixel.g = g;
  pixel.b = b;
  pixel.a = a;
  return pixel;
}

png_pixel_t png_color_random() {
  uint8_t r = rand() % 255;
  uint8_t g = rand() % 255;
  uint8_t b = rand() % 255;
  uint8_t a = 255;
  return png_color(r, g, b, a);
}

/**
 * @brief Allocate and initialize a new PNG type.
 *
 * @param width
 * @param height
 * @return png_t*
 */
png_t* new_png(uext_t width, uext_t height) {
  png_t* png = malloc(sizeof(png_t) + sizeof(png_pixel_t) * width * height);
  if (png == NULL) {
    goto out;
  }

  // set the attributes
  png->width = width;
  png->height = height;

out:
  return png;
}

/**
 * @brief Clean up an allocated PNG.
 *
 * @param png
 */
void release_png(png_t* png) { free(png); }

/**
 * @brief Compares png_t structs for equality.
 *
 * @param png1
 * @param png2
 * @param equal_out
 * @return int
 */
int png_compare(png_t* png1, png_t* png2) {
  int diff = 0;

  // check input existence
  if ((NULL == png1) || (NULL == png2)) {
    diff = 1;
    goto out;
  }

  // compare sizes
  if ((png1->width != png2->width) || (png1->height != png2->height)) {
    diff = 2;
    goto out;
  }

  // compare pixel by pixel
  for (size_t idy = 0; idy < png1->width; idy++) {
    for (size_t idx = 0; idx < png1->width; idx++) {
      size_t pos = idy * idx;
      if ((png1->pixels[pos].r != png2->pixels[pos].r) ||
          (png1->pixels[pos].g != png2->pixels[pos].g) ||
          (png1->pixels[pos].b != png2->pixels[pos].b) ||
          (png1->pixels[pos].a != png2->pixels[pos].a)) {
        diff = 30;
        printf("mismatch detected at pixel position %ld (%ld, %ld).\n", pos, idx, idy);
        printf("png1 color: (%u, %u, %u, %u).\n", png1->pixels[pos].r, png1->pixels[pos].g, png1->pixels[pos].b, png1->pixels[pos].a);
        printf("png2 color: (%u, %u, %u, %u).\n", png2->pixels[pos].r, png2->pixels[pos].g, png2->pixels[pos].b, png2->pixels[pos].a);
        
        goto out;
      }
    }
  }

out:
  return diff;
}

/**
 * @brief Write out a png image to a file.
 *
 * @param png
 * @param path
 * @return int
 */
int png_to_file(png_t const* png, char const* path) {
  int ret = 0;
  FILE* fp = NULL;
  spng_ctx* ctx = NULL;
  struct spng_ihdr ihdr;

  // check input pngs
  if (NULL == png) {
    ret = -ENOMEM;
    goto out;
  }

  /* set png header */
  memset(&ihdr, 0U, sizeof(ihdr));
  ihdr.width = png->width;
  ihdr.height = png->height;
  ihdr.bit_depth = 8;
  ihdr.color_type = SPNG_COLOR_TYPE_TRUECOLOR_ALPHA;

  // get spng context
  ctx = spng_ctx_new(SPNG_CTX_ENCODER);
  if (NULL == ctx) {
    ret = -ENOMEM;
    goto out;
  }

  // open file
  fp = fopen(path, "w");
  if (fp == NULL) {
    ret = -EEXIST;
    goto cleanup_ctx;
  };

  // set the file in the png context
  ret = spng_set_png_file(ctx, fp);
  if (0 != ret) {
    printf("failed to set png file (code %d)", ret);
    goto cleanup_file;
  }
  ret = spng_set_ihdr(ctx, &ihdr);
  if (0 != ret) {
    printf("failed to set ihdr (code %d)", ret);
    goto cleanup_file;
  }

  /* encode png data */
  ret = spng_encode_image(
      ctx, &png->pixels, sizeof(png_pixel_t) * png->width * png->height,
      SPNG_FMT_PNG, SPNG_ENCODE_FINALIZE);
  if (0 != ret) {
    printf("FAILED to encode png: '%s'\n", spng_strerror(ret));
  }

cleanup_file:
  fclose(fp);
cleanup_ctx:
  spng_ctx_free(ctx);
out:
  return ret;
}

/**
 * @brief Read file into a png image.
 *
 * Returns a new png structure, ownership is transferred out.
 *
 * @param path filepath to read
 * @param png_out
 * @return int
 */
int png_from_file(char const* path, png_t** png_out) {
  int ret = 0;
  FILE* fp = NULL;
  spng_ctx* ctx = NULL;
  size_t out_size = 0;
  unsigned char* in_data = NULL;
  struct spng_ihdr ihdr;

  // check inputs
  if (NULL == path) {
    ret = -ENOMEM;
    goto out;
  }

  if (NULL == png_out) {
    ret = -ENOMEM;
    goto out;
  }

  // open file
  fp = fopen(path, "rb");
  if (fp == NULL) {
    ret = -EEXIST;
    goto out;
  };

  // Read the file contents
  fseek(fp, 0, SEEK_END);
  size_t file_size = ftell(fp);
  fseek(fp, 0, SEEK_SET);

  // allocate memory to store the file contents in memory
  in_data = malloc(file_size);
  if (!in_data) {
    fclose(fp);
    ret = -ENOMEM;
    goto cleanup_indata;
  }

  // read file contents into memory
  int size_read = fread(in_data, 1, file_size, fp);
  if (size_read != file_size) {
    fclose(fp);
    ret = -ENFILE;
    goto cleanup_indata;
  }

  // close the file
  ret = fclose(fp);
  if (0 != ret) {
    goto cleanup_indata;
  }

  // get spng context
  ctx = spng_ctx_new(0);
  if (NULL == ctx) {
    ret = -ENOMEM;
    goto cleanup_indata;
  }

  // set the input PNG data
  ret = spng_set_png_buffer(ctx, in_data, file_size);
  if (0 != ret) {
    goto cleanup_ctx_indata;
  }

  // get ihdr PNG image information
  ret = spng_get_ihdr(ctx, &ihdr);
  if (0 != ret) {
    goto cleanup_ctx_indata;
  }

  // calculate output image size
  ret = spng_decoded_image_size(ctx, SPNG_FMT_RGBA8, &out_size);
  if (0 != ret) {
    goto cleanup_ctx_indata;
  }

  // create the new png structure
  // ownership of this memory is transferred out
  png_t* png = new_png(ihdr.width, ihdr.height);
  if (NULL == png) {
    ret = -ENOMEM;
    goto cleanup_ctx_indata;
  }

  // pass out the allocated png structure
  *png_out = png;

  // decode the PNG image into the structure memory
  ret = spng_decode_image(
      ctx, png->pixels, sizeof(png_pixel_t) * png->width * png->height,
      SPNG_FMT_RGBA8, 0);
  if (0 != ret) {
    ret = -1;
    goto cleanup_ctx_indata;
  }

cleanup_ctx_indata:
  spng_ctx_free(ctx);
cleanup_indata:
  free(in_data);
out:
  return ret;
}
