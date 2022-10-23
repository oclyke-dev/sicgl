#include "sicgl.h"

int sicgl_hline(
  specific_interface_t* interface, screen_t* screen, color_t color,
  ext_t u0, ext_t v0, ext_t u1
) {
  int ret = -EINPROGRESS;

out:
  return ret;
}

int sicgl_vline(
  specific_interface_t* interface, screen_t* screen, color_t color,
  ext_t u0, ext_t v0, ext_t u1
) {
  int ret = -EINPROGRESS;

out:
  return ret;
}

int sicgl_line(
  specific_interface_t* interface, screen_t* screen, color_t color,
  ext_t u0, ext_t v0,
  ext_t u1, ext_t v1
) {
  int ret = 0;

  if (NULL == interface) {
    ret = -EINVAL;
    goto out;
  }

  // apply transformation
  ret = transform_global_to_screen(&interface->display, &u0, &v0);
  if (0 != ret) {
    goto out;
  }
  ret = transform_global_to_screen(&interface->display, &u1, &v1);
  if (0 != ret) {
    goto out;
  }

  // // apply bounding
  // todo: actually apply smart bounding based on screen

  // handle simple cases
  if ((u0 == u1) && (v0 == v1)) {
    sicgl_specific_pixel(interface, color, u0, v0);
  }
  if (v0 == v1) {
    sicgl_specific_hline(interface, color, u0, v0, u1);
    goto out;
  }
  if (u0 == u1) {
    sicgl_specific_vline(interface, color, u0, v0, v1);
    goto out;
  }

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
    sicgl_specific_diagonal(interface, color, u0, v0, signu, signv, absdu + 1);
    goto out;
  }

  // prepare working coordinates
  ext_t u = u0;
  ext_t v = v0;

  // draw a run-sliced line
  uext_t min_run, run_len;
  ext_t accumulator, remainder, reset;
  uext_t len0, len1;
  if (absdu >= absdv) {
    // u is longer
    min_run = absdu / absdv;
    remainder = 2 * (absdu % absdv);
    reset = 2 * absdu;
    accumulator = (remainder / 2) - reset;
    len0 = (min_run / 2) + 1;
    len1 = len0;
    if ((remainder == 0) && ((min_run & 0x01) == 0)) {
      len0--; // when min_run is even and the slope is an integer the extra pixel will be placed at the end
    }
    // prepare first partial run
    ext_t unext = u + signu * len0;
    do {
      sicgl_specific_hline(interface, color, u, v, unext - 1);
      run_len = min_run;
      if ((accumulator += remainder) > 0) {
        run_len++;
        accumulator -= reset;
      }
      u = unext;
      unext = u + signu * run_len;
      v++;
    } while (v < v1);
    // draw the final run
    unext = u + signu * len1;
    sicgl_specific_hline(interface, color, u, v, unext);
  } else {
    // v is longer
    min_run = absdv / absdu;
    remainder = 2 * (absdv % absdu);
    reset = 2 * absdv;
    accumulator = (remainder / 2) - reset;
    len0 = (min_run / 2) + 1;
    len1 = len0;
    if ((remainder == 0) && ((min_run & 0x01) == 0)) {
      len0--; // when min_run is even and the slope is an integer the extra pixel will be placed at the end
    }
    // prepare first partial run
    ext_t vnext = v + signv * len0;
    do {
      sicgl_specific_vline(interface, color, u, v, vnext - 1);
      run_len = min_run;
      if ((accumulator += remainder) > 0) {
        run_len++;
        accumulator -= reset;
      }
      v = vnext;
      vnext = v + signv * run_len;
      u++;
    } while (v < v1);
    // draw the final run
    vnext = u + signv * len1;
    sicgl_specific_vline(interface, color, u, v, vnext);
  }

out:
  return ret;
}
