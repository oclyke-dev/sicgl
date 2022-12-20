#include "utilities/interface_libgd.h"

#include <errno.h>
#include <stdbool.h>

#include "gd.h"
#include "utilities/conversion.h"
#include "utilities/interfaces.h"
#include "utilities/screen.h"

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

  // create the screen definition from image
  int ret = screen_set_extent(&interface->screen, image->sx, image->sy, 0, 0);
  if (0 != ret) {
    release_libgd_generic_interface(interface);
    interface = NULL;
    goto out;
  }
  ret = screen_normalize(&interface->screen);
  if (0 != ret) {
    release_libgd_generic_interface(interface);
    interface = NULL;
    goto out;
  }

out:
  return interface;
}

/**
 * @brief Create a fully-featured generic interface which draws to libgd images.
 *
 * @param image
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
 * @brief Create a naive generic interface which draws to libgd images using
 * only a pixel definition.
 *
 * @param image
 * @return generic_interface_t*
 */
generic_interface_t* new_libgd_generic_interface_naive(gdImage* image) {
  // create prototype w/ only pixel
  generic_interface_t prototype;
  memset(&prototype, 0x00, sizeof(prototype));
  prototype.pixel = (void*)true;

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
    screen_t* screen, color_t* scratch, size_t scratch_length) {
  specific_interface_t* interface = NULL;

  if (NULL == screen) {
    goto out;
  }

  // allocate
  interface = malloc(sizeof(specific_interface_t));
  if (NULL == interface) {
    goto out;
  }
  // memset(interface, 0x00, sizeof(*interface));

  // allocate memory
  // (the gdImage tpixels memory is not necessarily contiguous --
  // it is formed by many individual calls to malloc -- therefore
  // we must allocate our own contiguous memory to operate on)
  int bpp = bytes_per_pixel();
  interface->length = screen->width * screen->height;
  interface->memory = calloc(interface->length, bpp);
  if (NULL == interface->memory) {
    free(interface);
    interface = NULL;
    goto out;
  }

  // set attributes
  interface->screen = *screen;
  interface->scratch = scratch;
  interface->scratch_length = scratch_length;

  // normalize the screen
  int ret = screen_normalize(&interface->screen);
  if (0 != ret) {
    release_libgd_specific_interface(interface);
    interface = NULL;
    goto out;
  }

out:
  return interface;
}

int release_libgd_generic_interface(generic_interface_t* interface) {
  int ret = 0;
  free(interface);
out:
  return ret;
}

int release_libgd_specific_interface(specific_interface_t* interface) {
  int ret = 0;
  free(interface);
out:
  return ret;
}

/**
 * @brief Show the contents of a libgd specific interface interface memory.
 *
 * @param interface
 * @return int
 */
int libgd_specific_interface_show_memory(specific_interface_t* interface) {
  int ret = 0;
  if (NULL == interface) {
    ret = -EINVAL;
    goto out;
  }
  if (NULL == interface->memory) {
    ret = -ENOMEM;
    goto out;
  }

  // show memory
  size_t pixels = interface->length;
  uext_t width = interface->screen.width;
  for (size_t idx = 0; idx < pixels; idx++) {
    if ((idx % width) == 0) {
      printf("\n%08x: ", (uint32_t)idx);
    }
    printf("%08x ", interface->memory[idx]);
  }
  printf("\n");

out:
  return ret;
}

/**
 * @brief Create a new PNG from a libgd specific interface.
 *
 * @param interface
 * @return png_t*
 */
png_t* new_png_from_libgd_specific_interface(specific_interface_t* interface) {
  png_t* png = NULL;

  if (NULL == interface) {
    goto out;
  }

  uext_t width = interface->screen.width;
  uext_t height = interface->screen.height;
  png = new_png(width, height);
  if (NULL == png) {
    goto out;
  }

  // convert memory
  size_t pixels = interface->length;
  for (size_t idx = 0; idx < pixels; idx++) {
    png->pixels[idx] = png_color_from_truecolor(interface->memory[idx]);
  }

out:
  return png;
}

// generic interface functions
static void libgd_pixel(void* arg, color_t color, uext_t u, uext_t v) {
  gdImage* image = (gdImage*)arg;
  gdImageSetPixel(image, u, v, (int)color);
}
static void libgd_hline(
    void* arg, color_t color, uext_t u0, uext_t v, uext_t u1) {
  gdImage* image = (gdImage*)arg;
  gdImageLine(image, u0, v, u1, v, (int)color);
}
static void libgd_vline(
    void* arg, color_t color, uext_t u, uext_t v0, uext_t v1) {
  gdImage* image = (gdImage*)arg;
  gdImageLine(image, u, v0, u, v1, (int)color);
}
