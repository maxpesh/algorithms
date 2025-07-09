/*
 * Converts a number from one radix to another.
 * The resulting number is returned as array of signed chars, where each element
 * represents a digit (can be negative) in the resulting number:
 * n∈ℤ,r∈ℕ n = ±dn-1 * r^n-1 ± dn-2 * r^n-2 ± ... ± d1 * r^1 ± d0 * r^0
 *
 * Computations are done in the source radix (10).
 */

#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include "div_with_rem.h"

#define BUF_SIZE (sizeof(int) * CHAR_BIT)

static signed char buf[BUF_SIZE];

/*
 * ⎧d=n%rd,n=⌊n/rd⌋; n≥0
 * ⎨
 * ⎩d=n-rd*⌈n/rd⌉,n=⌈n/rd⌉; n<0
 * Calculations are done in the source radix (10).
 *
 * <n> - number to convert
 * <rd> - target radix
 * <len>:out - # of digits in the converted number
 */
signed char *radix_conv(int n, unsigned rd, unsigned *len)
{
	signed char *ds = buf;
	unsigned i = 0, j = 0;

	*len = 0;
	do {
		div_t dt;
		if (n >= 0)
			dt = regular_div_with_rem(n, rd);
		else
			dt = div_with_neg_rem(n, rd);
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
