#include "gd.h"
#include "sicgl.h"
#include "utilities/interfaces.h"

static void libgd_pixel(void* arg, color_t color, uext_t u, uext_t v);
static void libgd_hline(
    void* arg, color_t color, uext_t u0, uext_t v, uext_t u1);
static void libgd_vline(
    void* arg, color_t color, uext_t u, uext_t v0, uext_t v1);

/**
 * @brief Create a generic interface which draws to libgd images based on
 * prototype.
 *
 * @param image
 * @param prototype
 * @return generic_interface_t*
 */
generic_interface_t* new_libgd_generic_interface_partial(
    gdImage* image, generic_interface_t prototype) {
  generic_interface_t* interface = NULL;

  // ensure an image is provided
  if (NULL == image) {
    goto out;
  }

  // create the interface structure
  interface = new_generic_interface();
  if (NULL == interface) {
    goto out;
  }

  // set the image as the argument
  interface->arg = image;

  // configure the interface as desired
  if (NULL != prototype.pixel) {
    interface->pixel = libgd_pixel;
  }
  if (NULL != prototype.hline) {
    interface->hline = libgd_hline;
  }
  if (NULL != prototype.vline) {
    interface->vline = libgd_vline;
  }

out:
  return interface;
}

/**
 * @brief Create a fully-featured generic interface which draws to libgd images.
 *
 * @param png
 * @return generic_interface_t*
 */
generic_interface_t* new_libgd_generic_interface_full(gdImage* image) {
  // create full prototype
  generic_interface_t prototype;
  memset(&prototype, 0x01, sizeof(prototype));

  // use prototype to get full interface
  generic_interface_t* interface =
      new_libgd_generic_interface_partial(image, prototype);

out:
  return interface;
}

/**
 * @brief Create a specific interface which draws to libgd images.
 *
 * @param image
 * @return specific_interface_t*
 */
specific_interface_t* new_libgd_specific_interface(
    gdImage* image, uint8_t* scratch, size_t scratch_length) {
  specific_interface_t* interface = NULL;

  if (NULL == image) {
    goto out;
  }

  // allocate
  interface = malloc(sizeof(specific_interface_t));
  if (NULL == interface) {
    goto out;
  }

  // set attributes
  interface->bpp = sizeof(int);
  interface->memory = (uint8_t*)image->tpixels;
  interface->scratch = scratch;
  interface->scratch_length = scratch_length;

out:
  return interface;
}

static void libgd_pixel(void* arg, color_t color, uext_t u, uext_t v) {
  gdImage* image = (gdImage*)arg;
  gdImageSetPixel(image, u, v, *((int*)color));
}
static void libgd_hline(
    void* arg, color_t color, uext_t u0, uext_t v, uext_t u1) {
  gdImage* image = (gdImage*)arg;
  gdImageLine(image, u0, v, u1, v, *((int*)color));
}
static void libgd_vline(
    void* arg, color_t color, uext_t u, uext_t v0, uext_t v1) {
  gdImage* image = (gdImage*)arg;
  gdImageLine(image, u, v0, u, v1, *((int*)color));
}
