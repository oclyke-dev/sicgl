#include "sicgl/compositors.h"
#include "tests/utilities.h"
#include "utils.h"

DEFINE_REFERENCED_COMPOSITOR_TEST(
    bitwise_and, compositor_bitwise_and, "solid_bitwise_and.png",
    "gradient_bitwise_and.png")
DEFINE_REFERENCED_COMPOSITOR_TEST(
    bitwise_or, compositor_bitwise_or, "solid_bitwise_or.png",
    "gradient_bitwise_or.png")
DEFINE_REFERENCED_COMPOSITOR_TEST(
    bitwise_xor, compositor_bitwise_xor, "solid_bitwise_xor.png",
    "gradient_bitwise_xor.png")
DEFINE_REFERENCED_COMPOSITOR_TEST(
    bitwise_nand, compositor_bitwise_nand, "solid_bitwise_nand.png",
    "gradient_bitwise_nand.png")
DEFINE_REFERENCED_COMPOSITOR_TEST(
    bitwise_nor, compositor_bitwise_nor, "solid_bitwise_nor.png",
    "gradient_bitwise_nor.png")
DEFINE_REFERENCED_COMPOSITOR_TEST(
    bitwise_xnor, compositor_bitwise_xnor, "solid_bitwise_xnor.png",
    "gradient_bitwise_xnor.png")
