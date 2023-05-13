#include "tests/alpha.h"

#include "tests/utilities.h"
#include "utils.h"

DEFINE_REFERENCED_COMPOSITOR_TEST(
    alpha_clear, compositor_alpha_clear, "solid_alpha_clear.png",
    "gradient_alpha_clear.png")
DEFINE_REFERENCED_COMPOSITOR_TEST(
    alpha_copy, compositor_alpha_copy, "solid_alpha_copy.png",
    "gradient_alpha_copy.png")
DEFINE_REFERENCED_COMPOSITOR_TEST(
    alpha_destination, compositor_alpha_destination,
    "solid_alpha_destination.png", "gradient_alpha_destination.png")
DEFINE_REFERENCED_COMPOSITOR_TEST(
    alpha_source_over, compositor_alpha_source_over,
    "solid_alpha_source_over.png", "gradient_alpha_source_over.png")
DEFINE_REFERENCED_COMPOSITOR_TEST(
    alpha_destination_over, compositor_alpha_destination_over,
    "solid_alpha_destination_over.png", "gradient_alpha_destination_over.png")
DEFINE_REFERENCED_COMPOSITOR_TEST(
    alpha_source_in, compositor_alpha_source_in, "solid_alpha_source_in.png",
    "gradient_alpha_source_in.png")
DEFINE_REFERENCED_COMPOSITOR_TEST(
    alpha_destination_in, compositor_alpha_destination_in,
    "solid_alpha_destination_in.png", "gradient_alpha_destination_in.png")
DEFINE_REFERENCED_COMPOSITOR_TEST(
    alpha_source_out, compositor_alpha_source_out, "solid_alpha_source_out.png",
    "gradient_alpha_source_out.png")
DEFINE_REFERENCED_COMPOSITOR_TEST(
    alpha_destination_out, compositor_alpha_destination_out,
    "solid_alpha_destination_out.png", "gradient_alpha_destination_out.png")
DEFINE_UNREFERENCED_COMPOSITOR_TEST(
    alpha_source_atop, compositor_alpha_source_atop)
DEFINE_UNREFERENCED_COMPOSITOR_TEST(
    alpha_destination_atop, compositor_alpha_destination_atop)
DEFINE_UNREFERENCED_COMPOSITOR_TEST(alpha_xor, compositor_alpha_xor)
DEFINE_UNREFERENCED_COMPOSITOR_TEST(alpha_lighter, compositor_alpha_lighter)
