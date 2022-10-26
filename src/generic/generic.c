#include <errno.h>
#include <stddef.h>

#include "sicgl/naive.h"
#include "sicgl_generic.h"

void sicgl_generic_pixel(
    generic_interface_t* interface, color_t color, uext_t u, uext_t v) {
  // pixel must exist
  interface->pixel(interface->arg, color, u, v);
}

void sicgl_generic_hrun(
    generic_interface_t* interface, color_t color, uext_t u,
    uext_t v, ext_t du) {
	if (du == 0) {
		interface->pixel(interface->arg, color, u, v);
	}
  if (interface->hline) {
    interface->hline(interface->arg, color, u, v, u + du - 1);
  } else {
    naive_hline(interface, color, u, v, u + du - 1);
  }
}

void sicgl_generic_vrun(
    generic_interface_t* interface, color_t color, uext_t u,
    uext_t v, ext_t dv) {
	if (dv == 0) {
		interface->pixel(interface->arg, color, u, v);
	}
  if (interface->hline) {
    interface->vline(interface->arg, color, u, v, v + dv - 1);
  } else {
    naive_vline(interface, color, u, v, v + dv - 1);
  }
}

void sicgl_generic_hline(
    generic_interface_t* interface, color_t color, uext_t u0, uext_t v,
    uext_t u1) {
  if (interface->hline) {
    interface->hline(interface->arg, color, u0, v, u1);
  } else {
    naive_hline(interface, color, u0, v, u1);
  }
}

void sicgl_generic_vline(
    generic_interface_t* interface, color_t color, uext_t u, uext_t v0,
    uext_t v1) {
  if (interface->vline) {
    interface->vline(interface->arg, color, u, v0, v1);
  } else {
    naive_vline(interface, color, u, v0, v1);
  }
}


void sicgl_generic_diagonal(
    generic_interface_t* interface, color_t color, uext_t u0,
    uext_t v0, ext_t diru, ext_t dirv, uext_t count) {
  uext_t u = u0;
	uext_t v = v0;
	int du, dv;

  if (diru > 0) {
    du = 1;
  } else {
    du = -1;
  }
  if (dirv > 0) {
    dv = 1;
  } else {
    dv = -1;
  }

  for (uext_t idx = 0; idx < count; idx++) {
		interface->pixel(interface->arg, color, u, v);
		u += du;
		v += dv;
  }
}

void sicgl_generic_region(
    generic_interface_t* interface, color_t color, uext_t u0, uext_t v0,
    uext_t u1, uext_t v1) {
  if (interface->region) {
    interface->region(interface->arg, color, u0, v0, u1, v1);
  } else {
    naive_region(interface, color, u0, v0, u1, v1);
  }
}

int sicgl_generic_line(generic_interface_t* interface, color_t color, uext_t u0, uext_t v0, uext_t u1, uext_t v1) {
  int ret = 0;

  if (NULL == interface) {
    ret = -EINVAL;
    goto out;
  }

  // handle simple cases
  if ((u0 == u1) && (v0 == v1)) {
    sicgl_generic_pixel(interface, color, u0, v0);
  }
  if (v0 == v1) {
    sicgl_generic_hline(interface, color, u0, v0, u1);
    goto out;
  }
  if (u0 == u1) {
    sicgl_generic_vline(interface, color, u0, v0, v1);
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
    sicgl_generic_diagonal(interface, color, u0, v0, signu, signv, absdu);
    goto out;
  }

  // prepare working coordinates
  ext_t u = u0;
  ext_t v = v0;

  // draw a run-sliced line
  uext_t min_run, run_len;
  ext_t accumulator, remainder, reset, drun;
  uext_t len0, len1;
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
    while (v < v1) {
      sicgl_generic_hrun(interface, color, u, v, drun);
      u += drun;
      v += 1;

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
    sicgl_generic_hrun(interface, color, u, v, drun);
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
    while (v < v1) {
      sicgl_generic_vrun(interface, color, u, v, drun);
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
    sicgl_generic_hrun(interface, color, u, v, drun);
  }

out:
  return ret;
}
