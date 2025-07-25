#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <stddef.h>
#include <stdint.h>
#include <float.h>
#include "div_with_rem.h"
#include "radix_conv.h"

#define BUF_SIZE 200

static signed char buf[BUF_SIZE];

/*
 * ∀n∈ℤ,r∈ℕ r > 1
 * n = ±d_n-1 * r^(n-1) ± d_n-2 * r^(n-2) ± ... ± d_1 * r^1 ± d_0 * r^0
 *
 * d = remainder of div(n, r), n = div(n, r)
 * where div(a, b) defined as:
 * ⎧div(a, b) = ⌊a / b⌋; a ≥ 0
 * ⎨
 * ⎩div(a, b) = ⌈a / b⌉; n < 0
 * Calculations are done in the source radix (10).
 *
 * Contract: r ≥ 2
 */
digits radix_convi(int n, unsigned char r)
{
	digits ds = {buf, 0};
	unsigned i = 0, j = 0;

	ds.len = 0;
	do {
		div_t dt;
		if (n >= 0)
			dt = regular_div_with_rem(n, r);
		else
			dt = div_with_neg_rem(n, r);
		ds.digits[i++] = (signed char)dt.rem;
		++ds.len;
		n = dt.quot;
	} while (n != 0);
	/* reverse */
	for (i = 0, j = ds.len-1; i < j; ++i, --j) {
		signed char t = ds.digits[i];
		ds.digits[i] = ds.digits[j];
		ds.digits[j] = t;
	}
	return ds;
}

/* Returns the number of set bits */
static size_t popcount(uintmax_t num) {
  size_t precision = 0;
  while (num != 0) {
    if (num % 2 == 1) {
      precision++;
    }
    num >>= 1;
  }
  return precision;
}
#define PRECISION(umax_value) popcount(umax_value)

/*
 * ∀n∈ℤ,r∈ℕ r > 1
 * n = ±d_n-1 * r^(n-1) ± d_n-2 * r^(n-2) ± ... ± d_1 * r^1 ± d_0 * r^0 ± 
 *     ---------------------------------------------------------------- integer part
 *     ±d_(-1) * r^(-)1 ± d(-2) * r^(-2) ± ...  ± d_(-m) * r^(-m)
 *     ---------------------------------------------------------- fractional part  
 * integer part:
 * d = remainder of div(n, r), n = div(n, r)
 * where div(a, b) defined as:
 * ⎧div(a, b) = ⌊a / b⌋; a ≥ 0
 * ⎨
 * ⎩div(a, b) = ⌈a / b⌉; n < 0
 *
 * fractional part:
 * d = integer part of n * r, n = fractional part of n * r
 *
 * Calculations are done in the source radix (10).
 *
 * Contract: r ≥ 2
 */
rational_digits radix_convf(double n, unsigned char r)
{
	int int_part;
	double fr_part;
	digits ds;
	rational_digits rd = {buf, buf, 0, 0};
	unsigned i = 0;

	rd.int_part_len = 0;
	rd.fract_part_len = 0;
	/* converting integer part */
	if (isnan(n) || PRECISION(INT_MAX) < log2(fabs(n))
	    || (n != 0.0F && fabs(n) < DBL_MIN)) {
		return rd;
	} else {
		int_part = (int)n;
	}
	ds = radix_convi(int_part, r);
	rd.int_part = ds.digits;
	rd.int_part_len = ds.len;
	/*-----converting fractional part-----*/
	rd.fract_part = buf + rd.int_part_len;
	fr_part = n - int_part;
	do {
		double prod = fr_part * r;
		int ipart = (int)prod;
		rd.fract_part[i++] = (signed char)ipart;
		++rd.fract_part_len;
		fr_part = prod - ipart;
	} while (fr_part != 0);
	return rd;
}
