#include <stdlib.h>
#include <math.h>
#include <errno.h>
#include <err.h>

/*
 * a = b × q + r    a,q ∈ ℤ, b ∈ ℕ, 0 ≤ r < b;
 * q = ⌊a/b⌋
 * r = b × {a/b} 
 */
div_t euclid_div(int a, int b)
{
	div_t dt;

	if (b <= 0)
		errx(EINVAL, "The denominator should be >= 0, but was: %d", b);
	dt.quot = (int)floor((double)a / b);
	dt.rem = a - b * dt.quot;
	return dt;
}
