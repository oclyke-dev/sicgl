#include "sicgl/compositors.h"
#include "tests/utilities.h"
#include "utils.h"

DEFINE_REFERENCED_COMPOSITOR_TEST(
    channelwise_min, compositor_channelwise_min, "solid_channelwise_min.png",
    "gradient_channelwise_min.png")
DEFINE_REFERENCED_COMPOSITOR_TEST(
    channelwise_max, compositor_channelwise_max, "solid_channelwise_max.png",
    "gradient_channelwise_max.png")

DEFINE_REFERENCED_COMPOSITOR_TEST(
    channelwise_sum, compositor_channelwise_sum, "solid_channelwise_sum.png",
    "gradient_channelwise_sum.png")
DEFINE_REFERENCED_COMPOSITOR_TEST(
    channelwise_diff, compositor_channelwise_diff, "solid_channelwise_diff.png",
    "gradient_channelwise_diff.png")
DEFINE_REFERENCED_COMPOSITOR_TEST(
    channelwise_diff_reverse, compositor_channelwise_diff_reverse,
    "solid_channelwise_diff_reverse.png",
    "gradient_channelwise_diff_reverse.png")
DEFINE_REFERENCED_COMPOSITOR_TEST(
    channelwise_multiply, compositor_channelwise_multiply,
    "solid_channelwise_multiply.png", "gradient_channelwise_multiply.png")
DEFINE_UNREFERENCED_COMPOSITOR_TEST(
    channelwise_divide, compositor_channelwise_divide)
DEFINE_UNREFERENCED_COMPOSITOR_TEST(
    channelwise_divide_reverse, compositor_channelwise_divide_reverse)

DEFINE_REFERENCED_COMPOSITOR_TEST(
    channelwise_sum_clamped, compositor_channelwise_sum_clamped,
    "solid_channelwise_sum_clamped.png", "gradient_channelwise_sum_clamped.png")
DEFINE_REFERENCED_COMPOSITOR_TEST(
    channelwise_diff_clamped, compositor_channelwise_diff_clamped,
    "solid_channelwise_diff_clamped.png",
    "gradient_channelwise_diff_clamped.png")
DEFINE_REFERENCED_COMPOSITOR_TEST(
    channelwise_diff_reverse_clamped,
    compositor_channelwise_diff_reverse_clamped,
    "solid_channelwise_diff_reverse_clamped.png",
    "gradient_channelwise_diff_reverse_clamped.png")
DEFINE_REFERENCED_COMPOSITOR_TEST(
    channelwise_multiply_clamped, compositor_channelwise_multiply_clamped,
    "solid_channelwise_multiply_clamped.png",
    "gradient_channelwise_multiply_clamped.png")
DEFINE_REFERENCED_COMPOSITOR_TEST(
    channelwise_divide_clamped, compositor_channelwise_divide_clamped,
    "solid_channelwise_divide_clamped.png",
    "gradient_channelwise_divide_clamped.png")
DEFINE_REFERENCED_COMPOSITOR_TEST(
    channelwise_divide_reverse_clamped,
    compositor_channelwise_divide_reverse_clamped,
    "solid_channelwise_divide_reverse_clamped.png",
    "gradient_channelwise_divide_reverse_clamped.png")
