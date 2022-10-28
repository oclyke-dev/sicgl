#include <errno.h>
#include <stddef.h>

#include "sicgl/debug.h"
#include "sicgl/specific.h"
#include "sicgl/screen.h"

/**
 * @brief Display-relative drawing functions.
 * Coordinates are taken in display frame.
 * Entities are clipped to display.
 * As interfaces define their own display this means passing coordinates along
 * with no translation.
 *
 */

int sicgl_specific_display_line(specific_interface_t* interface, color_sequence_t* color_sequence, ext_t u0, ext_t v0, ext_t u1, ext_t v1) {
  int ret = 0;
	screen_t* screen = &interface->screen;

  if (NULL == interface) {
    ret = -EINVAL;
    goto out;
  }

  // handle simple cases
  if ((u0 == u1) && (v0 == v1)) {
		int ret1 = screen_clip_hline(screen, &u0, &v0, &u1);
		int ret2 = screen_clip_vline(screen, &u0, &v0, &v1);
		if (ret1 < 0) {
			ret = ret1;
			goto out;
		}
		if (ret2 < 0) {
			ret = ret2;
			goto out;
		}
		if ((0 == ret1) && (0 == ret2)) {
			sicgl_specific_pixel(interface, color_sequence, u0, v0);
			goto out;
		}
		goto out;
  }
  if (v0 == v1) {
		ret = screen_clip_hline(screen, &u0, &v0, &u1);
		if (0 == ret) {
			sicgl_specific_hline(interface, color_sequence, u0, v0, u1);
			goto out;
		}
		goto out;
  }
  if (u0 == u1) {
		ret = screen_clip_vline(screen, &u0, &v0, &v1);
		if (0 == ret) {
			sicgl_specific_vline(interface, color_sequence, u0, v0, v1);
			goto out;
		}
		goto out;
  }

	// get dimensions for clipping
	uext_t dislay_width = interface->display.width;
	uext_t dislay_height = interface->display.height;

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
		uext_t num_pixels = absdu + 1;
		ret = screen_clip_diagonal(screen, &u0, &v0, signu, signv, &num_pixels);
		if (0 == ret) {
			sicgl_specific_diagonal(interface, color_sequence, u0, v0, signu, signv, num_pixels);
			goto out;
		}
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
      sicgl_specific_hrun(interface, color_sequence, u, v, drun);
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
    sicgl_specific_hrun(interface, color_sequence, u, v, drun);
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
      sicgl_specific_vrun(interface, color_sequence, u, v, drun);
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
    sicgl_specific_hrun(interface, color_sequence, u, v, drun);
  }

out:
  return ret;
}

int sicgl_specific_rectangle(
    specific_interface_t* interface, color_sequence_t* color_sequence,
    uext_t u0, uext_t v0, uext_t u1, uext_t v1) {
	int ret = 0;
	
out:
	return ret;
}


int sicgl_specific_display_rectangle(
    specific_interface_t* interface, color_sequence_t* color_sequence, ext_t u0,
    ext_t v0, ext_t u1, ext_t v1) {
  int ret = 0;
	screen_t* screen = &interface->screen;
	if (0 == screen_clip_hline(screen, &u0, &v0, &u1)) {
		sicgl_specific_hline(interface, color_sequence, u0, v0, u1);
	}
	if (0 == screen_clip_hline(screen, &u0, &v1, &u1)) {
		sicgl_specific_hline(interface, color_sequence, u0, v1, u1);
	}
	if (0 == screen_clip_vline(screen, &u0, &v0, &v1)) {
		sicgl_specific_vline(interface, color_sequence, u0, v0, v1);
	}
	if (0 == screen_clip_vline(screen, &u1, &v0, &v1)) {
		sicgl_specific_vline(interface, color_sequence, u1, v1, v1);
	}
out:
  return ret;
}
