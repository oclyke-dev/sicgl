#include "tests/blenders.h"

#include "sicgl/blend.h"
#include "sicgl/blenders.h"
#include "tests/utilities.h"
#include "utils.h"

DEFINE_REFERENCED_BLENDER_TEST(blend_normal, blend_normal, "solid_blend_normal.png", "gradient_blend_normal.png")
DEFINE_REFERENCED_BLENDER_TEST(blend_forget, blend_forget, "solid_blend_forget.png", "gradient_blend_forget.png")
DEFINE_REFERENCED_BLENDER_TEST(blend_multiply, blend_multiply, "solid_blend_multiply.png", "gradient_blend_multiply.png")
DEFINE_REFERENCED_BLENDER_TEST(blend_screen, blend_screen, "solid_blend_screen.png", "gradient_blend_screen.png")
DEFINE_REFERENCED_BLENDER_TEST(blend_overlay, blend_overlay, "solid_blend_overlay.png", "gradient_blend_overlay.png")
DEFINE_REFERENCED_BLENDER_TEST(blend_darken, blend_darken, "solid_blend_darken.png", "gradient_blend_darken.png")
DEFINE_REFERENCED_BLENDER_TEST(blend_lighten, blend_lighten, "solid_blend_lighten.png", "gradient_blend_lighten.png")
DEFINE_REFERENCED_BLENDER_TEST(blend_color_dodge, blend_color_dodge, "solid_blend_color_dodge.png", "gradient_blend_color_dodge.png")
DEFINE_REFERENCED_BLENDER_TEST(blend_color_burn, blend_color_burn, "solid_blend_color_burn.png", "gradient_blend_color_burn.png")
DEFINE_REFERENCED_BLENDER_TEST(blend_hard_light, blend_hard_light, "solid_blend_hard_light.png", "gradient_blend_hard_light.png")
DEFINE_REFERENCED_BLENDER_TEST(blend_soft_light, blend_soft_light, "solid_blend_soft_light.png", "gradient_blend_soft_light.png")
DEFINE_REFERENCED_BLENDER_TEST(blend_difference, blend_difference, "solid_blend_difference.png", "gradient_blend_difference.png")
DEFINE_REFERENCED_BLENDER_TEST(blend_exclusion, blend_exclusion, "solid_blend_exclusion.png", "gradient_blend_exclusion.png")
