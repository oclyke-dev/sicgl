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

static int specific_display_hline(specific_interface_t* interface, color_sequence_t* color_sequence, ext_t u0, ext_t v, ext_t u1) {
	int ret = screen_clip_hline(&interface->screen, &u0, &v, &u1);
	if (0 == ret) {
		sicgl_specific_hline(interface, color_sequence, u0, v, u1);
	} else if (ret > 0) {
		ret = 0;
		goto out;
	}

out:
	return ret;
}

static int specific_display_vline(specific_interface_t* interface, color_sequence_t* color_sequence, ext_t u, ext_t v0, ext_t v1) {
	int ret = screen_clip_vline(&interface->screen, &u, &v0, &v1);
	if (0 == ret) {
		sicgl_specific_vline(interface, color_sequence, u, v0, v1);
	} else if (ret > 0) {
		ret = 0;
		goto out;
	}

out:
	return ret;
}

static int specific_display_diagonal(specific_interface_t* interface, color_sequence_t* color_sequence, ext_t u0, ext_t v0, ext_t diru, ext_t dirv, uext_t count) {
	int ret = screen_clip_diagonal(&interface->screen, &u0, &v0, diru, dirv, &count);
	if (0 == ret) {
		sicgl_specific_diagonal(interface, color_sequence, u0, v0, diru, dirv, count);
	} else if (ret > 0) {
		ret = 0;
		goto out;
	}

out:
	return ret;
}

/**
 * @brief 
 * 
 * @param interface 
 * @param color_sequence 
 * @param u0 
 * @param v0 
 * @param u1 
 * @param v1 
 * @return int 
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
		ret = screen_clip_pixel(screen, u0, v0);
		if (ret == 0) {
			sicgl_specific_pixel(interface, color_sequence, u0, v0);
			goto out;
		} else if (ret > 0) {
			ret = 0;
			goto out;
		}
		goto out;
  }
  if (v0 == v1) {
		ret = screen_clip_hline(screen, &u0, &v0, &u1);
		if (0 == ret) {
			sicgl_specific_hline(interface, color_sequence, u0, v0, u1);
			goto out;
		} else if (ret > 0) {
			ret = 0;
			goto out;
		}
		goto out;
  }
  if (u0 == u1) {
		ret = screen_clip_vline(screen, &u0, &v0, &v1);
		if (0 == ret) {
			sicgl_specific_vline(interface, color_sequence, u0, v0, v1);
			goto out;
		} else if (ret > 0) {
			ret = 0;
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
    ret = specific_display_diagonal(interface, color_sequence, u0, v0, signu, signv, num_pixels);
    if (0 != ret) {
      goto out;
    }
    goto out;
  }

	// clip the line
	ret = screen_clip_line(screen, &u0, &v0, &u1, &v1);
	if (ret > 0) {
		ret = 0;
		goto out;
	} else if (ret < 0) {
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

	ret = specific_display_hline(interface, color_sequence, u0, v0, u1);
	if (0 != ret) {
		goto out;
	}

	ret = specific_display_hline(interface, color_sequence, u0, v1, u1);
	if (0 != ret) {
		goto out;
	}

	ret = specific_display_vline(interface, color_sequence, u0, v0, v1);
	if (0 != ret) {
		goto out;
	}

	ret = specific_display_vline(interface, color_sequence, u1, v0, v1);
	if (0 != ret) {
		goto out;
	}

out:
  return ret;
}
