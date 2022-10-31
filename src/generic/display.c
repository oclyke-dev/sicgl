#include <errno.h>
#include <stddef.h>

#include "sicgl/debug.h"
#include "sicgl/private/generic_direct.h"
#include "sicgl_generic.h"

/**
 * @brief Display-relative drawing functions.
 * Coordinates are taken in display frame.
 * As interfaces define their own display this means passing coordinates along
 * with no translation.
 *
 */

static int generic_display_pixel(
    generic_interface_t* interface, color_t color, ext_t u0, ext_t v0) {
  int ret = screen_clip_pixel(&interface->screen, u0, v0);
  if (0 == ret) {
    generic_pixel(interface, color, u0, v0);
  } else if (ret > 0) {
    ret = 0;
    goto out;
  }

out:
  return ret;
}

static int generic_display_hline(
    generic_interface_t* interface, color_t color, ext_t u0, ext_t v,
    ext_t u1) {
  int ret = screen_clip_hline(&interface->screen, &u0, &v, &u1);
  if (0 == ret) {
    generic_hline(interface, color, u0, v, u1);
  } else if (ret > 0) {
    ret = 0;
    goto out;
  }

out:
  return ret;
}

static int generic_display_vline(
    generic_interface_t* interface, color_t color, ext_t u, ext_t v0,
    ext_t v1) {
  int ret = screen_clip_vline(&interface->screen, &u, &v0, &v1);
  if (0 == ret) {
    generic_vline(interface, color, u, v0, v1);
  } else if (ret > 0) {
    ret = 0;
    goto out;
  }

out:
  return ret;
}

static int generic_display_diagonal(
    generic_interface_t* interface, color_t color, ext_t u0, ext_t v0,
    ext_t diru, ext_t dirv, uext_t count) {
  int ret =
      screen_clip_diagonal(&interface->screen, &u0, &v0, diru, dirv, &count);
  if (0 == ret) {
    generic_diagonal(interface, color, u0, v0, diru, dirv, count);
  } else if (ret > 0) {
    ret = 0;
    goto out;
  }

out:
  return ret;
}

static int generic_display_circle_eight(
    generic_interface_t* interface, color_t color, ext_t u0, ext_t v0, ext_t du,
    ext_t dv) {
  int ret = 0;
  generic_display_pixel(interface, color, u0 + du, v0 + dv);
  generic_display_pixel(interface, color, u0 - du, v0 + dv);
  generic_display_pixel(interface, color, u0 + du, v0 - dv);
  generic_display_pixel(interface, color, u0 - du, v0 - dv);
  generic_display_pixel(interface, color, u0 + dv, v0 + du);
  generic_display_pixel(interface, color, u0 - dv, v0 + du);
  generic_display_pixel(interface, color, u0 + dv, v0 - du);
  generic_display_pixel(interface, color, u0 - dv, v0 - du);
  return ret;
}

/**
 * @brief
 *
 * @param interface
 * @param color
 * @param u0
 * @param v0
 * @return int
 */
int sicgl_generic_display_pixel(
    generic_interface_t* interface, color_t color, ext_t u0, ext_t v0) {
  int ret = 0;
  ret = generic_display_pixel(interface, color, u0, v0);
out:
  return ret;
}

/**
 * @brief
 *
 * @param interface
 * @param color
 * @param u0
 * @param v0
 * @param u1
 * @param v1
 * @return int
 */
int sicgl_generic_display_line(
    generic_interface_t* interface, color_t color, ext_t u0, ext_t v0, ext_t u1,
    ext_t v1) {
  int ret = 0;
  screen_t* screen = &interface->screen;

  if (NULL == interface) {
    ret = -EINVAL;
    goto out;
  }

  // handle simple cases
  if ((u0 == u1) && (v0 == v1)) {
    ret = generic_display_pixel(interface, color, u0, v0);
    if (0 != ret) {
      goto out;
    }
    goto out;
  }
  if (v0 == v1) {
    ret = generic_display_hline(interface, color, u0, v0, u1);
    if (0 != ret) {
      goto out;
    }
    goto out;
  }
  if (u0 == u1) {
    ret = generic_display_vline(interface, color, u0, v0, v1);
    if (0 != ret) {
      goto out;
    }
    goto out;
  }

  // get dimensions for clipping
  ext_t su0 = interface->screen.u0;
  ext_t sv0 = interface->screen.v0;
  ext_t su1 = interface->screen.u1;
  ext_t sv1 = interface->screen.v1;

  // standardize vertical direction for consistency
  ext_t tmp;
  if (v1 < v0) {
    tmp = v0;
    v0 = v1;
    v1 = tmp;
    tmp = u0;
    u0 = u1;
    u1 = tmp;
  }

  // clip the line to the display screen
  ret = screen_clip_line(screen, &u0, &v0, &u1, &v1);
  if (ret > 0) {
    ret = 0;
    goto out;
  } else if (ret < 0) {
    goto out;
  }

  // check for diagonal
  ext_t signu, signv;   // direction in u and v axes
  uext_t absdu, absdv;  // absolute value of distance in u and v axes
  if ((u1 > u0)) {
    signu = 1;
    absdu = (u1 - u0);
  } else {
    signu = -1;
    absdu = (u0 - u1);
  }
  if ((v1 > v0)) {
    signv = 1;
    absdv = (v1 - v0);
  } else {
    signv = -1;
    absdv = (v0 - v1);
  }
  if (absdu == absdv) {
    uext_t num_pixels = absdu + 1;
    // use the direct interface here because clipping was already computed
    generic_diagonal(
        interface, color, u0, v0, signu, signv, num_pixels);
    goto out;
  }

  // prepare working coordinates
  ext_t u = u0;
  ext_t v = v0;

  // draw a run-sliced line
  uext_t min_run, run_len;
  ext_t accumulator, remainder, reset, drun;
  uext_t len0, len1;
  unsigned int runs = 0;
  if (absdu >= absdv) {
    // u is longer
    min_run = absdu / absdv;
    remainder = 2 * (absdu % absdv);
    reset = 2 * absdv;
    accumulator = (remainder / 2) - reset;
    len0 = (min_run / 2) + 1;
    len1 = len0;
    if ((remainder == 0) && ((min_run & 0x01) == 0)) {
      len0--;  // when min_run is even and the slope is an integer the extra
               // pixel will be placed at the end
    }
    if ((min_run & 0x01) != 0) {
      accumulator += (reset / 2);
    }
    // prepare first partial run
    drun = signu * len0;
    while (runs < absdv) {
      generic_hrun(interface, color, u, v, drun);
      runs++;
      u += drun;
      v++;

      // compute next slice
      run_len = min_run;
      accumulator += remainder;
      if (accumulator > 0) {
        run_len++;
        accumulator -= reset; /* reset the error term */
      }
      drun = signu * run_len;
    }
    // draw the final run
    drun = signu * len1;
    generic_hrun(interface, color, u, v, drun);
  } else {
    // v is longer
    min_run = absdv / absdu;
    remainder = 2 * (absdv % absdu);
    reset = 2 * absdu;
    accumulator = (remainder / 2) - reset;
    len0 = (min_run / 2) + 1;
    len1 = len0;
    if ((remainder == 0) && ((min_run & 0x01) == 0)) {
      len0--;  // when min_run is even and the slope is an integer the extra
               // pixel will be placed at the end
    }
    if ((min_run & 0x01) != 0) {
      accumulator += (reset / 2);
    }
    // prepare first partial run
    drun = signv * len0;
    while (runs < absdu) {
      generic_vrun(interface, color, u, v, drun);
      runs++;
      v += drun;
      u += signu;

      // compute next slice
      run_len = min_run;
      accumulator += remainder;
      if (accumulator > 0) {
        run_len++;
        accumulator -= reset; /* reset the error term */
      }
      drun = signv * run_len;
    }
    // draw the final run
    drun = signv * len1;
    generic_vrun(interface, color, u, v, drun);
  }

out:
  return ret;
}

/**
 * @brief
 *
 * @param interface
 * @param color
 * @param u0
 * @param v0
 * @param u1
 * @param v1
 * @return int
 */
int sicgl_generic_display_rectangle(
    generic_interface_t* interface, color_t color, ext_t u0, ext_t v0, ext_t u1,
    ext_t v1) {
  int ret = 0;

  ret = generic_display_hline(interface, color, u0, v0, u1);
  if (0 != ret) {
    goto out;
  }

  ret = generic_display_hline(interface, color, u0, v1, u1);
  if (0 != ret) {
    goto out;
  }

  ret = generic_display_vline(interface, color, u0, v0, v1);
  if (0 != ret) {
    goto out;
  }

  ret = generic_display_vline(interface, color, u1, v0, v1);
  if (0 != ret) {
    goto out;
  }

out:
  return ret;
}

/**
 * @brief
 *
 * @param interface
 * @param color
 * @param u0
 * @param v0
 * @param u1
 * @param v1
 * @return int
 */
int sicgl_generic_display_circle_bresenham(
    generic_interface_t* interface, color_t color, ext_t u0, ext_t v0,
    ext_t d) {
  int ret = 0;
  if (NULL == interface) {
    ret = -ENOMEM;
    goto out;
  }

  // bail early if zero diameter
  if (0 == d) {
    goto out;
  }

  // compute radius
  ext_t r = d / 2;

  // draw single pixel for zero radius circles
  if (r == 0) {
    ret = generic_display_pixel(interface, color, u0, v0);
    goto out;
  }

  // prepare state
  ext_t du = 0;
  ext_t dv = r;
  ext_t accumulator = 3 - 2 * r;

  // draw corners
  while (dv >= du) {
    generic_display_circle_eight(interface, color, u0, v0, du, dv);
    du++;
    if (accumulator > 0) {
      dv--;
      accumulator = accumulator + 4 * (du - dv) + 10;
    } else {
      accumulator = accumulator + 4 * du + 6;
    }
  }

out:
  return ret;
}

/**
 * @brief
 *
 * @param interface
 * @param color
 * @param u0
 * @param v0
 * @param d
 * @return int
 */
int sicgl_generic_display_circle_ellipse(
    generic_interface_t* interface, color_t color, ext_t u0, ext_t v0,
    ext_t d) {
  int ret = 0;
  if (NULL == interface) {
    ret = -ENOMEM;
    goto out;
  }

  // bail early if zero diameter
  if (0 == d) {
    goto out;
  }

  // compute radius
  ext_t r = d / 2;

  // draw circle using ellipse
  ret = sicgl_generic_display_ellipse(interface, color, u0, v0, r, r);

out:
  return ret;
}

/**
 * @brief Draw an ellipse on the display.
 *
 * Based on implementation by GD library (https://github.com/libgd/libgd)
 * Please see licenses/DG.md for license acknowledgement.
 *
 * @param interface
 * @param color
 * @param u0
 * @param v0
 * @param semiu
 * @param semiv
 * @return int
 */
int sicgl_generic_display_ellipse(
    generic_interface_t* interface, color_t color, ext_t u0, ext_t v0,
    ext_t semiu, ext_t semiv) {
  int ret = 0;
  ext_t x = 0, mu0 = 0, mu1 = 0, mv0 = 0, mv1 = 0;
  int64_t aq, bq, dx, dy, r, rx, ry, a, b;

  // ensure width and height are positive
  if (semiu < 0) {
    semiu = -semiu;
  }
  if (semiv < 0) {
    semiv = -semiv;
  }

  // compute primary and secondary axis lengths
  a = semiu;
  b = semiv;

  // draw pixels at either end
  generic_display_pixel(interface, color, u0 + a, v0);
  generic_display_pixel(interface, color, u0 - a, v0);

  mu0 = u0 - a;
  mv0 = v0;
  mu1 = u0 + a;
  mv1 = v0;

  aq = a * a;
  bq = b * b;
  dx = aq << 1;
  dy = bq << 1;
  r = a * bq;
  rx = r << 1;
  ry = 0;
  x = a;
  while (x > 0) {
    if (r > 0) {
      mv0++;
      mv1--;
      ry += dx;
      r -= ry;
    }
    if (r <= 0) {
      x--;
      mu0++;
      mu1--;
      rx -= dy;
      r += rx;
    }
    generic_display_pixel(interface, color, mu0, mv0);
    generic_display_pixel(interface, color, mu0, mv1);
    generic_display_pixel(interface, color, mu1, mv0);
    generic_display_pixel(interface, color, mu1, mv1);
  }

out:
  return ret;
}
