#include "utilities/interface_png.h"
#include "utilities/interfaces.h"

// fwd declarations of interface functions
static void png_pixel(void* arg, color_t color, uext_t u, uext_t v);
static void png_hline(void* arg, color_t color, uext_t u0, uext_t v, uext_t u1);
static void png_vline(void* arg, color_t color, uext_t u, uext_t v0, uext_t v1);

/**
 * @brief Create a generic interface from prototype.
 * Non-null fields in the prototpye will be replaced
 * with the appropriate interface function.
 *
 * @param png
 * @param prototype
 * @return generic_interface_t*
 */
generic_interface_t* new_png_generic_interface_partial(
    png_t* png, generic_interface_t prototype) {
  generic_interface_t* interface = NULL;

  // ensure an image is provided
  if (NULL == png) {
    goto out;
  }

  // create the interface structure
  interface = new_generic_interface();
  if (NULL == interface) {
    goto out;
  }

  // set the image as the argument
  interface->arg = png;

  // configure the interface as desired
  if (NULL != prototype.pixel) {
    interface->pixel = png_pixel;
  }
  if (NULL != prototype.hline) {
    interface->hline = png_hline;
  }
  if (NULL != prototype.vline) {
    interface->vline = png_vline;
  }
  // if (NULL != prototype.region) { interface->region = png_region; }

out:
  return interface;
}

/**
 * @brief Create a fully-featured generic interface which draws to PNGs.
 *
 * @param png
 * @return generic_interface_t*
 */
generic_interface_t* new_png_generic_interface_full(png_t* png) {
  // create full prototype
  generic_interface_t prototype;
  memset(&prototype, 0x01, sizeof(prototype));

  // use prototype to get full interface
  generic_interface_t* interface =
      new_png_generic_interface_partial(png, prototype);

out:
  return interface;
}

/**
 * @brief
 *
 * @param png
 * @return specific_interface_t*
 */
specific_interface_t* new_png_specific_interface(
  png_t* png,
  screen_t* screen,
  uint8_t* scratch,
  size_t scratch_length
) {
  specific_interface_t* interface = NULL;

  if (NULL == png) {
    goto out;
  }
  if (NULL == screen) {
    goto out;
  }

  // allocate
  interface = malloc(sizeof(specific_interface_t));
  if (NULL == interface) {
    goto out;
  }

  // set attributes
  interface->display = *screen;
  interface->bpp = sizeof(png_pixel_t);
  interface->memory = (uint8_t*)png->pixels;
  interface->length = png_length_bytes(png);
  interface->scratch = scratch;
  interface->scratch_length = scratch_length;

out:
  return interface;
}

int release_png_generic_interface(generic_interface_t* interface) {
  int ret = 0;
  free(interface);
out:
  return ret;
}

int release_png_specific_interface(specific_interface_t* interface) {
  int ret = 0;
  free(interface);
out:
  return ret;
}

static void png_pixel(void* arg, color_t color, uext_t u, uext_t v) {
  png_t* png = (png_t*)arg;
  png_pixel_t* bm_color = (png_pixel_t*)color;

  size_t offset = png->width * v + u;

  // // ensure we are within bounds
  // if (offset >= png->num_pix) {
  //   return;
  // }

  // set color in memory at the location
  png->pixels[offset] = *bm_color;
}

static void png_hline(
    void* arg, color_t color, uext_t u0, uext_t v, uext_t u1) {
  png_t* png = (png_t*)arg;
  png_pixel_t* bm_color = (png_pixel_t*)color;
  // assume that coordinates are in-bounds for the png

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
  png_pixel_t* px = &png->pixels[png->width * v + u0];
  *px = *bm_color;

  // set remaining pixels
  for (size_t idx = 0; idx < distance; idx++) {
    px += increment;
    *px = *bm_color;
  }
}

static void png_vline(
    void* arg, color_t color, uext_t u, uext_t v0, uext_t v1) {
  png_t* png = (png_t*)arg;
  png_pixel_t* bm_color = (png_pixel_t*)color;
  // assume that coordinates are in-bounds for the png

  int increment;
  size_t distance;
  if (v0 < v1) {
    increment = png->width;
    distance = v1 - v0;
  } else {
    increment = -png->width;
    distance = v0 - v1;
  }

  // set first pixel
  png_pixel_t* px = &png->pixels[png->width * v0 + u];
  *px = *bm_color;

  // set remaining pixels
  for (size_t idx = 0; idx < distance; idx++) {
    px += increment;
    *px = *bm_color;
  }
}
