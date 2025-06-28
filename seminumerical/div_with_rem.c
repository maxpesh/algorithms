#include <stdlib.h>
#include <math.h>

/*
 * ∀a∈ℤ,b∈ℕ ∃!q,r∈ℤ: a=b×q+r; 0≤r<b
 * q=⌊a/b⌋, r=b×{a/b} 
 *
 * Contract: b∈(0,INT_MAX]
 */
div_t regular_div_with_rem(int a, unsigned b)
{
	div_t dt;
	int bs;

	bs = (int)b;
	dt = div(a, bs);
	if (dt.rem < 0) {
		--dt.quot;
		dt.rem += bs;
	}
	return dt;
}

/*
 * ∀a,b∈ℤ ∃!q,r∈ℤ: a=b×q+r; 0≤r<|b|
 * ⎧q=⌊a/b⌋, r=b×{a/b}; b>0
 * ⎨
 * ⎩q=⌈a/b⌉; b<0
 *
 * Contract: b!=0
 */
div_t euclidian_div(int a, int b)
{
	div_t dt = div(a, b);

	if (dt.rem < 0) {
		if (b > 0) {
			--dt.quot;
			dt.rem += b;
		} else {
			++dt.quot;
			dt.rem -= b;
		}
	}
	return dt;
}

/*
 * ∀a∈ℤ,b∈ℕ ∃!q,r∈ℤ: a=b×q-r; 0≤r<b
 * q=⌈a/b⌉
 *
 * Contract: b∈(0,INT_MAX]
 */
div_t div_with_neg_rem(int a, unsigned b)
{
	div_t dt;
	int bs;

	bs = (int)b;
	dt = div(a, bs);
	if (dt.rem > 0) {
		++dt.quot;
		dt.rem -= bs;
	}
	return dt;
}

/*
 * ∀a,b∈ℤ ∃!q,r∈ℤ: a=b×q-r; 0≤r<|b|
 * ⎧q=⌈a/b⌉; b>0
 * ⎨
 * ⎩q=⌊a/b⌋, r=b×{a/b}; b<0
 *
 * Contract: b!=0
 */
div_t div_away_from_zero(int a, int b)
{
	div_t dt = div(a, b);

	if (dt.rem > 0) {
		if (b > 0) {
			++dt.quot;
			dt.rem -= b;
		} else {
			--dt.quot;
			dt.rem += b;
		}
	}
	return dt;
}	

/*
 * ∀a,b∈ℤ ∃!q,r∈ℤ: a=b×q+r
 * q=⌊a/b⌉=⌈a/b-0.5⌉
 * ⎧r∈[-(b-1)/2,(b-1)/2], b-odd
 * ⎨
 * ⎩r∈(-b/2,b/2], b-even
 *
 * Contract b!=0
 */
div_t div_nearest_int(int a, int b)
{
	div_t dt = div(a, b);
	double fp;

	fp = (double)a / b - floor((double)a / b);
	if (fp > 0.5) { /* don't account for rounding error */
		if (dt.rem != 0 && (a > 0 == b > 0)) {
			++dt.quot;
			dt.rem -= b;
		}
	} else {
		if (dt.rem != 0 && (a > 0 != b > 0)) {
			--dt.quot;
			dt.rem += b;
		}
	}
	return dt;
}

/*
 * ∀a,b∈ℤ ∃!q,r∈ℤ: a=b×q+r; |r|<|b|
 * ⎧q=⌊a/b⌋, r=b×{a/b}; a and b have the same sign
 * ⎨
 * ⎩q=⌈a/b⌉; otherwise
 *
 * Contract b!=0
 */
div_t truncated_div(int a, int b)
{
	div_t dt = div(a, b);

	return dt;
}

/*
 * ∀a,b∈ℤ ∃!q,r∈ℤ: a=b×q+r; |r|<|b|
 * q=⌊a/b⌋, r=b×{a/b}
 *
 * Contract b!=0
 */
div_t floor_div(int a, int b)
{
	div_t dt = div(a, b);

	if (dt.rem != 0 && (a > 0 != b > 0)) {
		--dt.quot;
		dt.rem += b;
	}
	return dt;
}


/********************TESTS********************/
#include <assert.h>
#include <limits.h>

void test_div(int (*args)[2], size_t args_len, div_t (*divp)(int, int),
    div_t(*expect_divp)(int, int))
{
	div_t dt;
	div_t expect_dt;
	size_t i = 0;

	for (i = 0; i < args_len; ++i) {
		dt = divp(args[i][0], args[i][1]);
		expect_dt = expect_divp((int)args[i][0], (int)args[i][1]);
		assert(dt.quot == expect_dt.quot && dt.rem == expect_dt.rem);
	}
}

void test_udiv(int (*args)[2], size_t args_len, div_t (*divp)(int, unsigned),
    div_t(*expect_divp)(int, unsigned))
{
	test_div(args, args_len,
	    (div_t (*)(int, int))divp, (div_t (*)(int, int))expect_divp);
}

div_t test_regular_div_with_rem(int a, unsigned int b)
{
	div_t dt;
	int bs;

	bs = (int)b;
	dt.quot = (int)floor((double)a / bs);
	dt.rem = (int)(a - (long)bs * dt.quot);
	return dt;
}

div_t test_euclidian_div(int a, int b)
{
	div_t dt;

	if (b > 0)
		dt.quot = (int)floor((double)a / b);
	else
		dt.quot = (int)ceil((double)a / b);
	dt.rem = (int)(a - (long)b * dt.quot);
	return dt;
}

div_t test_div_with_neg_rem(int a, unsigned int b)
{
	div_t dt;
	int bs;

	bs = (int)b;
	dt.quot = (int)ceil((double)a / bs);
	dt.rem = (int)(a - (long)bs * dt.quot);
	return dt;
}

div_t test_div_away_from_zero(int a, int b)
{
	div_t dt;

	if (b > 0)
		dt.quot = (int)ceil((double)a / b);
	else
		dt.quot = (int)floor((double)a / b);
	dt.rem = (int)(a - (long)b * dt.quot);
	return dt;
}

div_t test_div_nearest_int(int a, int b)
{
	div_t dt;

	dt.quot = (int)ceil(((double)a / b) - 0.5);
	dt.rem = (int)(a - (long)b * dt.quot);
	return dt;
}

div_t test_truncated_div(int a, int b)
{
	div_t dt;

	if ((a > 0) == (b > 0)) /* dividend and divisor have the same sign*/
		dt.quot = (int)floor((double)a / b);
	else
		dt.quot = (int)ceil((double)a / b);
	dt.rem = (int)(a - (long)b * dt.quot);
	return dt;
}

div_t test_floor_div(int a, int b)
{
	div_t dt;

	dt.quot = (int)floor((double)a / b);
	dt.rem = (int)(a - (long)b * dt.quot);
	return dt;
}

int main(void)
{
	int uargs[][2] = {
	    {8,3}, {-8,3},
	    {1,2}, {-1,2},
	    {INT_MAX,1}, {INT_MIN,1},
	    {INT_MAX,2}, {INT_MIN,2},
	    {1,INT_MAX}, {-1,INT_MAX},
	    {INT_MIN,INT_MAX},
	    {0,1729}, {0,INT_MAX},
        };
	size_t uargs_len = sizeof uargs / sizeof uargs[0];
	int args[][2] = {
	    {8,3}, {8,-3}, {-8,3}, {-8,-3},
	    {1,2}, {1,-2}, {-1,2}, {-1,-2},
	    {INT_MAX,1}, {INT_MAX,-1},
	    {INT_MIN,1},
	    {INT_MAX,2}, {INT_MAX,-2},
	    {INT_MIN,2}, {INT_MIN,-2},
	    {1,INT_MAX}, {-1,INT_MAX},
	    {1, INT_MIN}, {-1, INT_MIN},
	    {INT_MIN,INT_MAX}, {INT_MAX, INT_MIN},
	    {0,1729}, {0, INT_MIN}, {0,INT_MAX},
        };
	size_t args_len = sizeof args / sizeof args[0];

	test_udiv(uargs, uargs_len, regular_div_with_rem, test_regular_div_with_rem);
	test_div(args, args_len, euclidian_div, test_euclidian_div);
	test_udiv(uargs, uargs_len, div_with_neg_rem, test_div_with_neg_rem);
	test_div(args, args_len, div_away_from_zero, test_div_away_from_zero);
	test_div(args, args_len, div_nearest_int, test_div_nearest_int);
	test_div(args, args_len, truncated_div, test_truncated_div);
	test_div(args, args_len, floor_div, test_floor_div);
	return EXIT_SUCCESS;
}
