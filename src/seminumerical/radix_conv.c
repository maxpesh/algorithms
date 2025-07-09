/*
 * Converts a number from one radix to another.
 * The resulting number in the target radix is returned as an array of signed chars,
 * where each element represents a digit that can be positive or negative.
 * ∀n∈ℤ,r∈ℕ r > 1
 * n = ±d_n-1 * r^(n-1) ± d_n-2 * r^(n-2) ± ... ± d_1 * r^1 ± d_0 * r^0
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
 * Contract: rd ≥ 2

 * Parameters:
 * <n> - number to convert
 * <rd> - destination radix
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
