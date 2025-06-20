#include <stdlib.h>
#include <math.h>
#include <errno.h>
#include <err.h>
#include <limits.h>

/*
 * ∀a∈ℤ,b∈ℕ ∃!q,r∈ℤ: a=b×q+r; 0≤r<b;
 * q=⌊a/b⌋, r=b×{a/b} 
 */
div_t regular_div_with_rem(int a, unsigned b)
{
	div_t dt;
	int bs;

	if (b > INT_MAX)
		errx(EXIT_FAILURE, "The denominator (%u) is out of range. "
		    "Should be [0;%d]", b, INT_MAX);
	bs = (int)b;
	dt.quot = (int)floor((double)a / bs);
	dt.rem = a - bs * dt.quot;
	return dt;
}
