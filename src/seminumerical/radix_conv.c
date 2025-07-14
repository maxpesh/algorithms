#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <stddef.h>
#include <stdint.h>
#include <float.h>
#include "div_with_rem.h"

#define BUF_SIZE 200

static signed char buf[BUF_SIZE];

/*
 * Converts an integer number from one radix to another.
 * The resulting number in the target radix is returned as an array of signed chars,
 * where each element represents a digit that can be positive or negative.
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

 * Parameters:
 * <n> - number to convert
 * <r> - destination radix
 * <len>:out - # of digits in the converted number
 */
signed char *radix_convi(int n, unsigned char r, unsigned *len)
{
	signed char *ds = buf;
	unsigned i = 0, j = 0;

	*len = 0;
	do {
		div_t dt;
		if (n >= 0)
			dt = regular_div_with_rem(n, r);
		else
			dt = div_with_neg_rem(n, r);
		*ds++ = (signed char)dt.rem;
		++*len;
		n = dt.quot;
	} while (n != 0);
	/* reverse */
	for (i = 0, j = *len-1; i < j; ++i, --j) {
		signed char t = buf[i];
		buf[i] = buf[j];
		buf[j] = t;
	}
	return buf;
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
 * Converts a rational number from one radix to another.
 * The resulting number in the target radix is returned as an array of signed chars,
 * where each element represents a digit that can be positive or negative.
 * For example if n = -1.5 and r = 2 the resulting array would be: {-1,-1}
 *                                                                  -- --
 *                                                                 int fract
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
 *
 * Parameters:
 * <n> - number to convert
 * <r> - destination radix
 * <len>:out - # of digits in the converted number
 */
signed char *radix_convf(double n, unsigned char r, unsigned *len)
{
	int int_part;
	double fr_part;
	signed char *ds = buf;
	unsigned ipart_len = 0;

	*len = 0;
	/* converting integer part */
	if (isnan(n) || PRECISION(INT_MAX) < log2(fabs(n))
	    || (n != 0.0F && fabs(n) < DBL_MIN)) {
		return NULL;
	} else {
		int_part = (int)n;
	}
	ds = radix_convi(int_part, r, len);
	/* converting fractional part */
	ipart_len = *len;
	ds = ds + ipart_len;
	fr_part = n - int_part;
	do {
		double prod = fr_part * r;
		int ipart = (int)prod;
		*ds++ = (signed char)ipart;
		++*len;
		fr_part = prod - ipart;
	} while (fr_part != 0);
	return buf;
}
