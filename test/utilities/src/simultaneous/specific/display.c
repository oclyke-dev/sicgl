#include "utilities/simultaneous/specific/display.h"

#include <errno.h>

int simultaneous_specific_display_line(
    gdImage* image, specific_interface_t* interface,
    color_sequence_t* color_sequence, ext_t u0, ext_t v0, ext_t u1, ext_t v1) {
  int ret = 0;
  color_t color = color_sequence_get_color(color_sequence);
  gdImageLine(image, u0, v0, u1, v1, *(int*)color);
  ret = sicgl_specific_display_line(interface, color_sequence, u0, v0, u1, v1);
out:
  return ret;
}

int simultaneous_specific_display_rectangle(
    gdImage* image, specific_interface_t* interface,
    color_sequence_t* color_sequence, ext_t u0, ext_t v0, ext_t u1, ext_t v1) {
  int ret = 0;
  color_t color = color_sequence_get_color(color_sequence);
  gdImageRectangle(image, u0, v0, u1, v1, *(int*)color);
  ret = sicgl_specific_display_rectangle(interface, color_sequence, u0, v0, u1, v1);
out:
  return ret;
}

int simultaneous_specific_display_circle(
    gdImage* image, specific_interface_t* interface,
    color_sequence_t* color_sequence, ext_t u0, ext_t v0, ext_t diameter) {
  int ret = 0;
  color_t color = color_sequence_get_color(color_sequence);
  gdImageEllipse(image, u0, v0, diameter, diameter, *(int*)color);
  ret = sicgl_specific_display_circle(interface, color_sequence, u0, v0, diameter);
  return ret;
}

int simultaneous_specific_display_ellipse(
    gdImage* image, specific_interface_t* interface,
    color_sequence_t* color_sequence, ext_t u0, ext_t v0, ext_t major,
    ext_t minor) {
  return -EINVAL;
}
