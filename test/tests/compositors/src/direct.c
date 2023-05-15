#include "sicgl/compositors.h"
#include "tests/utilities.h"
#include "utils.h"

DEFINE_REFERENCED_COMPOSITOR_TEST(
    direct_set, compositor_direct_set, "solid_direct_set.png",
    "gradient_direct_set.png")
DEFINE_REFERENCED_COMPOSITOR_TEST(
    direct_clear, compositor_direct_clear, "solid_direct_clear.png",
    "gradient_direct_clear.png")
DEFINE_REFERENCED_COMPOSITOR_TEST(
    direct_none, compositor_direct_none, "solid_direct_none.png",
    "gradient_direct_none.png")
