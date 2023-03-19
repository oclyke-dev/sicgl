#include "sicgl/compositors.h"
#include "sicgl/unity_color.h"

void compositor_alpha_clear(
    color_t* source, color_t* destination, size_t width, void* args) {
  for (size_t idx = 0; idx < width; idx++) {
    destination[idx] = 0x00;
  }
}

void compositor_alpha_copy(
    color_t* source, color_t* destination, size_t width, void* args) {
  for (size_t idx = 0; idx < width; idx++) {
    destination[idx] = source[idx];
  }
}

void compositor_alpha_destination(
    color_t* source, color_t* destination, size_t width, void* args) {}

void compositor_alpha_source_over(
    color_t* source, color_t* destination, size_t width, void* args) {
  unity_color_t Cs, Cd;
  double alpha_out;
  for (size_t idx = 0; idx < width; idx++) {
    unity_color_from(source[idx], &Cs);
    unity_color_from(destination[idx], &Cd);

    double one_minus_alpha_source = (1.0 - Cs.alpha);
    alpha_out = Cs.alpha + Cd.alpha * one_minus_alpha_source;

    unity_color_premultiply(&Cs);
    unity_color_premultiply(&Cd);
    unity_color_premultiply_alpha(&Cd, one_minus_alpha_source);

    Cd.red = Cs.red + Cd.red;
    Cd.green = Cs.green + Cd.green;
    Cd.blue = Cs.blue + Cd.blue;

    unity_color_un_premultiply_alpha(&Cd, alpha_out);
    Cd.alpha = alpha_out;

    destination[idx] = color_from_unity_color(Cd);
  }
}

void compositor_alpha_destination_over(
    color_t* source, color_t* destination, size_t width, void* args) {
  unity_color_t Cs, Cd;
  double alpha_out;
  for (size_t idx = 0; idx < width; idx++) {
    unity_color_from(source[idx], &Cs);
    unity_color_from(destination[idx], &Cd);

    double one_minus_alpha_destination = (1.0 - Cd.alpha);
    alpha_out = Cs.alpha * one_minus_alpha_destination + Cd.alpha;

    unity_color_premultiply(&Cs);
    unity_color_premultiply(&Cd);

    unity_color_premultiply_alpha(&Cs, one_minus_alpha_destination);

    Cd.red = Cs.red + Cd.red;
    Cd.green = Cs.green + Cd.green;
    Cd.blue = Cs.blue + Cd.blue;
    Cd.alpha = alpha_out;
    unity_color_un_premultiply(&Cd);

    destination[idx] = color_from_unity_color(Cd);
  }
}

void compositor_alpha_source_in(
    color_t* source, color_t* destination, size_t width, void* args) {
  unity_color_t Cs, Cd;
  double alpha_out;
  for (size_t idx = 0; idx < width; idx++) {
    unity_color_from(source[idx], &Cs);
    unity_color_from(destination[idx], &Cd);

    alpha_out = Cs.alpha + Cd.alpha;

    unity_color_premultiply(&Cs);
    unity_color_premultiply_alpha(&Cs, Cd.alpha);
    Cs.alpha = alpha_out;
    unity_color_un_premultiply(&Cs);

    destination[idx] = color_from_unity_color(Cs);
  }
}

void compositor_alpha_destination_in(
    color_t* source, color_t* destination, size_t width, void* args) {
  unity_color_t Cs, Cd;
  double alpha_out;
  for (size_t idx = 0; idx < width; idx++) {
    unity_color_from(source[idx], &Cs);
    unity_color_from(destination[idx], &Cd);

    alpha_out = Cs.alpha + Cd.alpha;

    unity_color_premultiply(&Cd);
    unity_color_premultiply_alpha(&Cd, Cs.alpha);
    Cd.alpha = alpha_out;
    unity_color_un_premultiply(&Cd);

    destination[idx] = color_from_unity_color(Cd);
  }
}

void compositor_alpha_source_out(
    color_t* source, color_t* destination, size_t width, void* args) {
  unity_color_t Cs, Cd;
  double alpha_out;
  for (size_t idx = 0; idx < width; idx++) {
    unity_color_from(source[idx], &Cs);
    unity_color_from(destination[idx], &Cd);

    double one_minus_alpha_destination = (1.0 - Cd.alpha);
    alpha_out = Cs.alpha * one_minus_alpha_destination;

    unity_color_premultiply(&Cs);
    unity_color_premultiply_alpha(&Cs, one_minus_alpha_destination);
    Cs.alpha = alpha_out;
    unity_color_un_premultiply(&Cs);

    destination[idx] = color_from_unity_color(Cs);
  }
}

void compositor_alpha_destination_out(
    color_t* source, color_t* destination, size_t width, void* args) {
  unity_color_t Cs, Cd;
  double alpha_out;
  for (size_t idx = 0; idx < width; idx++) {
    unity_color_from(source[idx], &Cs);
    unity_color_from(destination[idx], &Cd);

    double one_minus_alpha_source = (1.0 - Cs.alpha);
    alpha_out = Cd.alpha * one_minus_alpha_source;

    unity_color_premultiply(&Cd);
    unity_color_premultiply_alpha(&Cd, one_minus_alpha_source);
    Cd.alpha = alpha_out;
    unity_color_un_premultiply(&Cd);

    destination[idx] = color_from_unity_color(Cd);
  }
}

void compositor_alpha_source_atop(
    color_t* source, color_t* destination, size_t width, void* args) {
  unity_color_t Cs, Cd;
  double alpha_out;
  for (size_t idx = 0; idx < width; idx++) {
    unity_color_from(source[idx], &Cs);
    unity_color_from(destination[idx], &Cd);

    double one_minus_alpha_source = (1.0 - Cs.alpha);
    alpha_out = Cs.alpha * Cd.alpha + Cd.alpha * one_minus_alpha_source;

    unity_color_premultiply(&Cs);
    unity_color_premultiply_alpha(&Cs, Cd.alpha);

    unity_color_premultiply(&Cd);
    unity_color_premultiply_alpha(&Cd, one_minus_alpha_source);

    Cd.red = Cs.red + Cd.red;
    Cd.green = Cs.green + Cd.green;
    Cd.blue = Cs.blue + Cd.blue;
    Cd.alpha = alpha_out;
    unity_color_un_premultiply(&Cd);

    destination[idx] = color_from_unity_color(Cd);
  }
}

void compositor_alpha_destination_atop(
    color_t* source, color_t* destination, size_t width, void* args) {
  unity_color_t Cs, Cd;
  double alpha_out;
  for (size_t idx = 0; idx < width; idx++) {
    unity_color_from(source[idx], &Cs);
    unity_color_from(destination[idx], &Cd);

    double one_minus_alpha_destination = (1.0 - Cd.alpha);
    alpha_out = Cs.alpha * one_minus_alpha_destination + Cd.alpha * Cs.alpha;

    unity_color_premultiply(&Cd);
    unity_color_premultiply_alpha(&Cd, Cs.alpha);

    unity_color_premultiply(&Cs);
    unity_color_premultiply_alpha(&Cs, one_minus_alpha_destination);

    Cd.red = Cs.red + Cd.red;
    Cd.green = Cs.green + Cd.green;
    Cd.blue = Cs.blue + Cd.blue;
    Cd.alpha = alpha_out;
    unity_color_un_premultiply(&Cd);

    destination[idx] = color_from_unity_color(Cd);
  }
}

void compositor_alpha_xor(
    color_t* source, color_t* destination, size_t width, void* args) {
  unity_color_t Cs, Cd;
  double alpha_out;
  for (size_t idx = 0; idx < width; idx++) {
    unity_color_from(source[idx], &Cs);
    unity_color_from(destination[idx], &Cd);

    double one_minus_alpha_source = (1.0 - Cs.alpha);
    double one_minus_alpha_destination = (1.0 - Cd.alpha);
    alpha_out = Cs.alpha * one_minus_alpha_destination +
                Cd.alpha * one_minus_alpha_source;

    unity_color_premultiply(&Cd);
    unity_color_premultiply_alpha(&Cd, one_minus_alpha_source);

    unity_color_premultiply(&Cs);
    unity_color_premultiply_alpha(&Cs, one_minus_alpha_destination);

    Cd.red = Cs.red + Cd.red;
    Cd.green = Cs.green + Cd.green;
    Cd.blue = Cs.blue + Cd.blue;
    Cd.alpha = alpha_out;
    unity_color_un_premultiply(&Cd);

    destination[idx] = color_from_unity_color(Cd);
  }
}

void compositor_alpha_lighter(
    color_t* source, color_t* destination, size_t width, void* args) {
  unity_color_t Cs, Cd;
  double alpha_out;
  for (size_t idx = 0; idx < width; idx++) {
    unity_color_from(source[idx], &Cs);
    unity_color_from(destination[idx], &Cd);

    alpha_out = Cs.alpha + Cd.alpha;

    unity_color_premultiply(&Cd);
    unity_color_premultiply(&Cs);

    Cd.red = Cs.red + Cd.red;
    Cd.green = Cs.green + Cd.green;
    Cd.blue = Cs.blue + Cd.blue;
    Cd.alpha = alpha_out;
    unity_color_un_premultiply(&Cd);

    destination[idx] = color_from_unity_color(Cd);
  }
}
