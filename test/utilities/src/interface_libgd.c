#include "utilities/interface_libgd.h"

#include <errno.h>
#include <stdbool.h>

#include "gd.h"
#include "utilities/conversion.h"
#include "utilities/interfaces.h"
#include "utilities/screen.h"

/**
 * @brief Create a specific interface which draws to libgd images.
 *
 * @param image
 * @return interface_t*
 */
interface_t* new_libgd_interface(
    screen_t* screen, color_t* scratch, size_t scratch_length) {
  interface_t* interface = NULL;

  if (NULL == screen) {
    goto out;
  }

  // allocate
  interface = malloc(sizeof(interface_t));
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
  interface->screen = screen;

  // normalize the screen
  int ret = screen_normalize(interface->screen);
  if (0 != ret) {
    release_libgd_interface(interface);
    interface = NULL;
    goto out;
  }

out:
  return interface;
}

int release_libgd_interface(interface_t* interface) {
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
int libgd_interface_show_memory(interface_t* interface) {
  int ret = 0;
  if (NULL == interface) {
    ret = -EINVAL;
    goto out;
  }
  if (NULL == interface->memory) {
    ret = -ENOMEM;
    goto out;
  }
  if (NULL == interface->screen) {
    ret = -ENOMEM;
    goto out;
  }

  // show memory
  size_t pixels = interface->length;
  uext_t width = interface->screen->width;
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
png_t* new_png_from_libgd_interface(interface_t* interface) {
  png_t* png = NULL;

  if (NULL == interface) {
    goto out;
  }
  if (NULL == interface->screen) {
    goto out;
  }

  uext_t width = interface->screen->width;
  uext_t height = interface->screen->height;
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
