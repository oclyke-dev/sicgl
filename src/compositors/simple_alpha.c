#include "sicgl/compositors.h"
#include "sicgl/unity_color.h"

void compositor_alpha_simple(
    color_t* source, color_t* destination, size_t width, void* args) {
  unity_color_t Cs, Cd;
  for (size_t idx = 0; idx < width; idx++) {
    // get unity colors
    unity_color_from(source[idx], &Cs);
    unity_color_from(destination[idx], &Cd);

    // premultiply colors
    unity_color_premultiply(&Cs);
    unity_color_premultiply(&Cd);

    // compute helpful values
    double one_minus_alpha_source = (1.0 - Cs.alpha);
    double alpha_out = Cs.alpha + Cd.alpha * one_minus_alpha_source;

    // scale the destination color by its strength
    unity_color_scale(&Cd, one_minus_alpha_source);

    // add the source colors to the destination colors, and
    Cd.red = Cs.red + Cd.red;
    Cd.green = Cs.green + Cd.green;
    Cd.blue = Cs.blue + Cd.blue;

    // un-premultiply according to the output intensity to arrive back at full
    // scale colors
    unity_color_un_premultiply_alpha(&Cd, alpha_out);

    // set the output alpha value
    Cd.alpha = alpha_out;

    // set the destination color
    destination[idx] = color_from_unity_color(Cd);
  }
}
