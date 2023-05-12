#include "tests/alpha.h"
#include "tests/utilities.h"
#include "utils.h"

DEFINE_UNREFERENCED_COMPOSITOR_TEST(channelwise_min, compositor_channelwise_min)
DEFINE_UNREFERENCED_COMPOSITOR_TEST(channelwise_max, compositor_channelwise_max)

DEFINE_UNREFERENCED_COMPOSITOR_TEST(channelwise_sum, compositor_channelwise_sum)
DEFINE_UNREFERENCED_COMPOSITOR_TEST(
    channelwise_diff, compositor_channelwise_diff)
DEFINE_UNREFERENCED_COMPOSITOR_TEST(
    channelwise_diff_reverse, compositor_channelwise_diff_reverse)
DEFINE_UNREFERENCED_COMPOSITOR_TEST(
    channelwise_multiply, compositor_channelwise_multiply)
DEFINE_UNREFERENCED_COMPOSITOR_TEST(
    channelwise_divide, compositor_channelwise_divide)
DEFINE_UNREFERENCED_COMPOSITOR_TEST(
    channelwise_divide_reverse, compositor_channelwise_divide_reverse)

DEFINE_UNREFERENCED_COMPOSITOR_TEST(
    channelwise_sum_clamped, compositor_channelwise_sum_clamped)
DEFINE_UNREFERENCED_COMPOSITOR_TEST(
    channelwise_diff_clamped, compositor_channelwise_diff_clamped)
DEFINE_UNREFERENCED_COMPOSITOR_TEST(
    channelwise_diff_reverse_clamped,
    compositor_channelwise_diff_reverse_clamped)
DEFINE_UNREFERENCED_COMPOSITOR_TEST(
    channelwise_multiply_clamped, compositor_channelwise_multiply_clamped)
DEFINE_UNREFERENCED_COMPOSITOR_TEST(
    channelwise_divide_clamped, compositor_channelwise_divide_clamped)
DEFINE_UNREFERENCED_COMPOSITOR_TEST(
    channelwise_divide_reverse_clamped,
    compositor_channelwise_divide_reverse_clamped)
