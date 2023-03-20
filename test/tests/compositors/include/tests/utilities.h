#include "globals.h"
#include "sicgl.h"
#include "sicgl/compose.h"
#include "sicgl/compositors.h"
#include "utils.h"

#define DEFINE_COMPOSITOR_TEST(__name, __compositor)                         \
  void test_##__name(void) {                                                 \
    interface_t* interface = NULL;                                           \
    png_t* img = NULL;                                                       \
    if (TEST_PROTECT()) {                                                    \
      interface = new_libgd_interface(screen, NULL, 0);                      \
      TEST_ASSERT_NOT_NULL_MESSAGE(interface, "could not create interface"); \
      sicgl_blit(interface, screen, backdrop_interface->memory);             \
      sicgl_compose(                                                         \
          interface, screen, source_interface->memory, __compositor, NULL);  \
      img = new_png_from_libgd_interface(interface);                         \
      TEST_ASSERT_NOT_NULL_MESSAGE(img, "could not create img png");         \
      TEST_ASSERT_EQUAL_INT(                                                 \
          0, png_to_file(img, TEST_OUTPUT_DIR "/" #__name ".png"));          \
    }                                                                        \
    release_libgd_interface(interface);                                      \
    release_png(img);                                                        \
  }
