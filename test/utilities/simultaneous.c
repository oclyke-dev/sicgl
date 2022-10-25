#include "utilities/simultaneous.h"

int simultaneous_specific_display_pixel(
    gdImage* image, specific_interface_t* interface, color_sequence_t* sequence,
    ext_t u0, ext_t v0) {
  int ret = 0;
  color_t color = color_sequence_get_color(sequence);
  gdImageSetPixel(image, u0, v0, *(int*)color);
  sicgl_specific_pixel(interface, sequence, u0, v0);
out:
  return ret;
}

int simultaneous_specific_display_hline(
    gdImage* image, specific_interface_t* interface, color_sequence_t* sequence,
    ext_t u0, ext_t v0, ext_t u1, ext_t v1) {
  int ret = 0;
  color_t color = color_sequence_get_color(sequence);
  gdImageLine(image, u0, v0, u1, v1, *(int*)color);
  sicgl_specific_hline(interface, sequence, u0, v0, u1);
out:
  return ret;
}

int simultaneous_specific_display_vline(
    gdImage* image, specific_interface_t* interface, color_sequence_t* sequence,
    ext_t u0, ext_t v0, ext_t u1, ext_t v1) {
  int ret = 0;
  color_t color = color_sequence_get_color(sequence);
  gdImageLine(image, u0, v0, u1, v1, *(int*)color);
  sicgl_specific_vline(interface, sequence, u0, v0, v1);
out:
  return ret;
}

int simultaneous_specific_display_region(
    gdImage* image, specific_interface_t* interface, color_sequence_t* sequence,
    ext_t u0, ext_t v0, ext_t u1, ext_t v1) {
  int ret = 0;
  color_t color = color_sequence_get_color(sequence);
  gdImageFilledRectangle(image, u0, v0, u1, v1, *(int*)color);
  sicgl_specific_region(interface, sequence, u0, v0, u1, v1);
out:
  return ret;
}
