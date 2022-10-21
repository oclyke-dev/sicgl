#include "utilities/interface_bytes.h"

// sicgl generic interface functions
static void bytes_pixel(void* arg, color_t color, uext_t u, uext_t v);
static void bytes_hline(
    void* arg, color_t color, uext_t u0, uext_t v, uext_t u1);
static void bytes_vline(
    void* arg, color_t color, uext_t u, uext_t v0, uext_t v1);
static void bytes_region(
    void* arg, color_t color, uext_t u0, uext_t v0, uext_t u1, uext_t v1);

generic_interface_t* new_bytes_generic_interface_partial(
    bytes_t* bytes, generic_interface_t prototype) {
  generic_interface_t* interface = NULL;

  // ensure an image is provided
  if (NULL == bytes) {
    goto out;
  }

  // create the interface structure
  interface = new_generic_interface();
  if (NULL == interface) {
    goto out;
  }

  // set the image as the argument
  interface->arg = bytes;

  // configure the interface as desired
  if (NULL != prototype.pixel) {
    interface->pixel = bytes_pixel;
  }
  if (NULL != prototype.hline) {
    interface->hline = bytes_hline;
  }
  if (NULL != prototype.vline) {
    interface->vline = bytes_vline;
  }
  if (NULL != prototype.region) {
    interface->region = bytes_region;
  }

out:
  return interface;
}

/**
 * @brief Create a fully-featured generic interface which draws to bytes_t
 * images.
 *
 * @param png
 * @return generic_interface_t*
 */
generic_interface_t* new_bytes_generic_interface_full(bytes_t* bytes) {
  // create full prototype
  generic_interface_t prototype;
  prototype.pixel = (void*)true;
  prototype.hline = (void*)true;
  prototype.vline = (void*)true;
  prototype.region = (void*)true;

  // use prototype to get full interface
  generic_interface_t* interface =
      new_bytes_generic_interface_partial(bytes, prototype);

out:
  return interface;
}

specific_interface_t* new_bytes_specific_interface(
    bytes_t* bytes, uint8_t* scratch, size_t scratch_length) {
  specific_interface_t* interface = NULL;
  if (NULL == bytes) {
    goto out;
  }

  interface = new_specific_interface();
  if (NULL == interface) {
    goto out;
  }

  // create easy defaults
  interface->bpp = bytes_bpp(*bytes);
  interface->memory = bytes->memory;
  interface->length = bytes_length_bytes(bytes);
  interface->scratch = scratch;
  interface->scratch_length = scratch_length;

out:
  return interface;
}

// offset within array for (u, v)
static inline size_t bytes_position(bytes_t* bytes, uext_t u, uext_t v) {
  return (bytes->width * v + u);
}

// sicgl generic interface functions
static void bytes_pixel(void* arg, color_t color, uext_t u, uext_t v) {
  bytes_t* bytes = (bytes_t*)arg;
  uint8_t* c = (uint8_t*)color;
  bytes->memory[bytes_position(bytes, u, v)] = *c;
}

static void bytes_hline(
    void* arg, color_t color, uext_t u0, uext_t v, uext_t u1) {
  bytes_t* bytes = (bytes_t*)arg;
  uint8_t* c = (uint8_t*)color;

  int increment;
  uext_t distance;
  size_t offset;
  if (u0 < u1) {
    increment = 1;
    distance = u1 - u0 + 1;
    offset = bytes_position(bytes, u0, v);
  } else {
    increment = -1;
    distance = u0 - u1 + 1;
    offset = bytes_position(bytes, u1, v);
  }

  for (uext_t idu = 0; idu < distance; idu++) {
    bytes->memory[offset + idu] = *c;
  }
}

static void bytes_vline(
    void* arg, color_t color, uext_t u, uext_t v0, uext_t v1) {
  bytes_t* bytes = (bytes_t*)arg;
  uint8_t* c = (uint8_t*)color;
  size_t width = bytes->width;

  uext_t distance;
  size_t offset;
  if (v0 < v1) {
    distance = v1 - v0 + 1;
    offset = bytes_position(bytes, u, v0);
  } else {
    distance = v0 - v1 + 1;
    offset = bytes_position(bytes, u, v1);
  }

  for (uext_t idv = 0; idv < distance; idv++) {
    bytes->memory[offset + (idv * width)] = *c;
  }
}

static inline void bytes_region(
    void* arg, color_t color, uext_t u0, uext_t v0, uext_t u1, uext_t v1) {
  bytes_t* bytes = (bytes_t*)arg;
  uint8_t* c = (uint8_t*)color;
  size_t width = bytes->width;

  uext_t distance;
  uext_t voffset;
  if (v0 < v1) {
    distance = v1 - v0 + 1;
    voffset = v0;
  } else {
    distance = v0 - v1 + 1;
    voffset = v1;
  }

  for (uext_t idv = 0; idv < distance; idv++) {
    bytes_hline(arg, color, u0, voffset + idv, u1);
  }
}
