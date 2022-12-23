#include "utils.h"

#define TEST_WIDTH_PIXELS (255)
#define TEST_HEIGHT_PIXELS (255)

// scalar field type definition
typedef double (*scalar_field_fn)(ext_t u, ext_t v);

static void test_specific_field(
    const char* name, scalar_field_fn fn, color_sequence_t* sequence,
    bool discrete, bool circular) {
  uext_t width = TEST_WIDTH_PIXELS;
  uext_t height = TEST_HEIGHT_PIXELS;

  gdImage* image = NULL;
  screen_t* screen = NULL;
  screen_t* scalar_screen = NULL;
  specific_interface_t* interface = NULL;
  png_t* img = NULL;

  TEST_ASSERT_NOT_NULL_MESSAGE(fn, "scalar field function was not provided");

  if (TEST_PROTECT()) {
    // create specific interface
    screen = new_screen_extent(width, height, 0, 0);
    interface = new_libgd_specific_interface(screen, NULL, 0);
    TEST_ASSERT_NOT_NULL_MESSAGE(screen, "could not create screen");
    TEST_ASSERT_NOT_NULL_MESSAGE(interface, "could not create interface");

    // create scalar field
    size_t total_scalars = width * height;
    scalar_screen = new_screen_extent(width, height, 0, 0);
    TEST_ASSERT_NOT_NULL_MESSAGE(
        scalar_screen, "could not create scalar screen");
    double scalars[total_scalars];
    for (size_t idx = 0; idx < total_scalars; idx++) {
      ext_t u = idx % width;
      ext_t v = idx / width;
      scalars[idx] = fn(u, v);
    }

    // apply scalar field with color sequence
    int ret = sicgl_specific_scalar_field(
        interface, scalar_screen, scalars, sequence, discrete, circular);

    // save images to png
    char* disc = (discrete) ? "discrete" : "continuous";
    char* circ = (circular) ? "circular" : "linear";
    int filename_length =
        snprintf(
            NULL, 0, TEST_OUTPUT_DIR "/specific_blit_%s_%s_%s.png", name, disc,
            circ) +
        1;
    char filename[filename_length];
    snprintf(
        filename, filename_length,
        TEST_OUTPUT_DIR "/specific_blit_%s_%s_%s.png", name, disc, circ);
    img = new_png_from_libgd_specific_interface(interface);
    TEST_ASSERT_NOT_NULL_MESSAGE(img, "could not create img png");
    TEST_ASSERT_EQUAL_INT(0, png_to_file(img, filename));
    TEST_ASSERT_EQUAL_INT_MESSAGE(0, ret, "failed to apply scalar field");

  } else {
    release_image(image);
    release_screen(screen);
    release_screen(scalar_screen);
    release_libgd_specific_interface(interface);
    release_color_sequence(sequence);
    release_png(img);
  }
}

// field functions
double ramp(ext_t u, ext_t v) { return ((double)u) / (TEST_WIDTH_PIXELS - 1); }

double mega_ramp(ext_t u, ext_t v) {
  double phase = ((double)u) / (TEST_WIDTH_PIXELS - 1);
  return 10.0f * (phase - 0.5f);
}

double daddio(ext_t u, ext_t v) {
  double pu = ((double)u) / (TEST_WIDTH_PIXELS - 1);
  double pv = ((double)v) / (TEST_HEIGHT_PIXELS - 1);

  double radius = sqrtf(powf(pu - 0.5, 2.0f) + powf(pv - 0.5f, 2.0f));
  double value = (sinf(2 * M_PI * radius) / 2.0f) + 0.5f;

  return value;
}

// a helper to automatically name the inputs
#define TEST_SPECIFIC_FIELD(_func_name, _sequence, _discrete, _circular) \
  do {                                                                   \
    test_specific_field(                                                 \
        #_func_name, _func_name, _sequence, _discrete, _circular);       \
  } while (0);

void test_specific_fields(void) {
  // create color sequence
  size_t max_sequence_length = 32;
  color_t colors[max_sequence_length];
  color_sequence_t* sequence = new_color_sequence(colors, max_sequence_length);

  // case 1
  colors[0] = 0x00000000;
  colors[1] = 0x0000ff00;
  sequence->length = 2;
  TEST_SPECIFIC_FIELD(ramp, sequence, true, false);
  TEST_SPECIFIC_FIELD(ramp, sequence, false, false);
  TEST_SPECIFIC_FIELD(ramp, sequence, true, true);
  TEST_SPECIFIC_FIELD(ramp, sequence, false, true);

  // case 2
  colors[0] = 0x00000000;
  colors[1] = 0x00ff0000;
  sequence->length = 2;
  TEST_SPECIFIC_FIELD(mega_ramp, sequence, true, false);
  TEST_SPECIFIC_FIELD(mega_ramp, sequence, false, false);
  TEST_SPECIFIC_FIELD(mega_ramp, sequence, true, true);
  TEST_SPECIFIC_FIELD(mega_ramp, sequence, false, true);

  // case 2
  colors[0] = 0x00ffff00;
  colors[1] = 0x000000ff;
  colors[2] = 0x00ff0000;
  colors[3] = 0x0000ff00;
  colors[4] = 0x00ff6600;
  colors[5] = 0x00ff00ff;
  sequence->length = 6;
  TEST_SPECIFIC_FIELD(daddio, sequence, true, false);
  TEST_SPECIFIC_FIELD(daddio, sequence, false, false);
  TEST_SPECIFIC_FIELD(daddio, sequence, true, true);
  TEST_SPECIFIC_FIELD(daddio, sequence, false, true);
}
