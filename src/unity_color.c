#include "sicgl/unity_color.h"

#include <errno.h>

#include "sicgl/color.h"

static inline double clamp_double_positive_unity(double val) {
  if (val < 0.0f) {
    return 0.0f;
  } else if (val > 1.0f) {
    return 1.0f;
  } else {
    return val;
  }
}

int unity_color_from(color_t color, unity_color_t* unity) {
  int ret = 0;

  if (NULL == unity) {
    ret = -ENOMEM;
    goto out;
  }

  ret = color_components_unity_double(
      color, &unity->red, &unity->green, &unity->blue, &unity->alpha);

out:
  return ret;
}

color_t color_from_unity_color(unity_color_t unity) {
  return color_from_channels(
      color_channel_from_unity_double(unity.red),
      color_channel_from_unity_double(unity.green),
      color_channel_from_unity_double(unity.blue),
      color_channel_from_unity_double(unity.alpha));
}

int unity_color_clamp(unity_color_t* unity) {
  int ret = 0;

  if (NULL == unity) {
    ret = -ENOMEM;
    goto out;
  }

  unity->red = clamp_double_positive_unity(unity->red);
  unity->green = clamp_double_positive_unity(unity->green);
  unity->blue = clamp_double_positive_unity(unity->blue);
  unity->alpha = clamp_double_positive_unity(unity->alpha);

out:
  return ret;
}

int unity_color_clamp_alpha(unity_color_t* unity) {
  int ret = 0;

  if (NULL == unity) {
    ret = -ENOMEM;
    goto out;
  }

  unity->alpha = clamp_double_positive_unity(unity->alpha);

out:
  return ret;
}

int unity_color_clamp_color(unity_color_t* unity) {
  int ret = 0;

  if (NULL == unity) {
    ret = -ENOMEM;
    goto out;
  }

  unity->red = clamp_double_positive_unity(unity->red);
  unity->green = clamp_double_positive_unity(unity->green);
  unity->blue = clamp_double_positive_unity(unity->blue);

out:
  return ret;
}

int unity_color_premultiply_alpha(unity_color_t* unity, double alpha) {
  int ret = 0;

  if (NULL == unity) {
    ret = -ENOMEM;
    goto out;
  }

  if (unity_color_is_premultiplied(*unity)) {
    goto out;
  }

  unity->red = unity->red * alpha;
  unity->green = unity->green * alpha;
  unity->blue = unity->blue * alpha;

out:
  return ret;
}

int unity_color_premultiply(unity_color_t* unity) {
  int ret = 0;

  if (NULL == unity) {
    ret = -ENOMEM;
    goto out;
  }

  ret = unity_color_premultiply_alpha(unity, unity->alpha);

out:
  return ret;
}

int unity_color_un_premultiply_alpha(unity_color_t* unity, double alpha) {
  int ret = 0;

  if (NULL == unity) {
    ret = -ENOMEM;
    goto out;
  }

  if (!unity_color_is_premultiplied(*unity)) {
    goto out;
  }

  unity->red = unity->red / alpha;
  unity->green = unity->green / alpha;
  unity->blue = unity->blue / alpha;

out:
  return ret;
}

int unity_color_un_premultiply(unity_color_t* unity) {
  int ret = 0;

  if (NULL == unity) {
    ret = -ENOMEM;
    goto out;
  }

  ret = unity_color_un_premultiply_alpha(unity, unity->alpha);

out:
  return ret;
}
