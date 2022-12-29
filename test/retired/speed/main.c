#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "gd.h"
#include "spng.h"
#include "utils.h"

#define TRANSPARENT (127)
#define OPAQUE (0)

void setUp(void) {
  // set stuff up here
}

void tearDown(void) {
  // clean stuff up here
}

int main() {
  clock_t start, end;
  double cpu_time_used;
  double time_taken_generic_full;
  double time_taken_generic_naive;
  double time_taken_specific_fast;
  double time_taken_specific_regular;

  // define number of tests
  size_t num_tests = 1000;

  // define size of image
  uext_t width = 512;
  uext_t height = 512;
  display_t* display = new_screen(width, height, 0, 0);

  // size of the rectangle to draw
  uext_t u0 = 15;
  uext_t v0 = 30;
  uext_t u1 = 215;
  uext_t v1 = 230;

  // use this color
  int color = truecolor_random_color();

  // make images
  gdImagePtr image = gdImageCreateTrueColor(width, height);

  // make scratch space for fast specific interface
  size_t scratch_bytes = sizeof(int) * width;
  uint8_t* scratch = malloc(scratch_bytes);
  if (NULL == scratch) {
    printf(
        "WARNING: scratch could not be allocated, fast specific interface will "
        "be identical to regular specific\n");
  }

  // run test of generic_full interface
  generic_interface_t* generic_full = new_libgd_generic_interface_full(image);
  start = clock();
  for (size_t idx = 0; idx < num_tests; idx++) {
    generic_region(generic_full, &color, u0, v0, u1, v1);
  }
  end = clock();  // in clock cycles
  release_libgd_generic_interface(generic_full);
  time_taken_generic_full = ((double)(end - start)) / CLOCKS_PER_SEC;
  printf("generic_full interface took %f seconds.\n", time_taken_generic_full);

  // run test of generic_naive interface
  generic_interface_t naive_prototype = {.pixel = (void*)true};
  generic_interface_t* generic_naive =
      new_libgd_generic_interface_partial(image, naive_prototype);
  start = clock();
  for (size_t idx = 0; idx < num_tests; idx++) {
    generic_region(generic_naive, &color, u0, v0, u1, v1);
  }
  end = clock();  // in clock cycles
  release_libgd_generic_interface(generic_naive);
  time_taken_generic_naive = ((double)(end - start)) / CLOCKS_PER_SEC;
  printf(
      "generic_naive interface took %f seconds.\n", time_taken_generic_naive);

  // run test of specific_regular interface
  interface_t* specific_regular =
      new_libgd_specific_interface(display, NULL, 0);
  start = clock();
  for (size_t idx = 0; idx < num_tests; idx++) {
    specific_region(specific_regular, &color, u0, v0, u1, v1);
  }
  end = clock();  // in clock cycles
  release_libgd_specific_interface(specific_regular);
  time_taken_specific_regular = ((double)(end - start)) / CLOCKS_PER_SEC;
  printf(
      "specific_regular interface took %f seconds.\n",
      time_taken_specific_regular);

  // run test of specific_fast interface
  interface_t* specific_fast =
      new_libgd_specific_interface(screen, scratch, scratch_bytes);
  start = clock();
  for (size_t idx = 0; idx < num_tests; idx++) {
    specific_region(specific_fast, &color, u0, v0, u1, v1);
  }
  end = clock();  // in clock cycles
  release_libgd_specific_interface(specific_fast);
  time_taken_specific_regular = ((double)(end - start)) / CLOCKS_PER_SEC;
  printf(
      "specific_fast interface took %f seconds.\n",
      time_taken_specific_regular);

  // clean up
  release_screen(screen);

  return 0;
}
