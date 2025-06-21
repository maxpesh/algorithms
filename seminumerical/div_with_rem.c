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

	if (b == 0 || b > INT_MAX)
		errx(EXIT_FAILURE, "The denominator (%u) is out of range. "
		    "Should be (0;%d]", b, INT_MAX);
	bs = (int)b;
	dt.quot = (int)floor((double)a / bs);
	dt.rem = a - bs * dt.quot;
	return dt;
}

/********************TESTS********************/
#include <assert.h>

static void test_regular_div_with_rem(void)
{
	div_t dt;

	dt = regular_div_with_rem(8, 3);
	assert(dt.quot == 2);
	assert(dt.rem == 2);
	dt = regular_div_with_rem(-8, 3);
	assert(dt.quot == -3);
	assert(dt.rem == 1);
	dt = regular_div_with_rem(1, 2);
	assert(dt.quot == 0);
	assert(dt.rem == 1);
	dt = regular_div_with_rem(-1, 2);
	assert(dt.quot == -1);
	assert(dt.rem == 1);
	dt = regular_div_with_rem(0, 5);
	assert(dt.quot == 0);
	assert(dt.rem == 0);

}

int main(void)
{
	test_regular_div_with_rem();
	return EXIT_SUCCESS;
}
