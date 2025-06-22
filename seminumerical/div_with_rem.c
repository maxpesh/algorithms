#include <stdlib.h>
#include <math.h>
#include <errno.h>
#include <err.h>
#include <limits.h>

/*
 * ∀a∈ℤ,b∈ℕ ∃!q,r∈ℤ: a=b×q+r; 0≤r<b
 * q=⌊a/b⌋, r=b×{a/b} 
 */
div_t regular_div_with_rem(int a, unsigned b)
{
	div_t dt;
	int bs;

	if (b == 0 || b > INT_MAX)
		errx(EXIT_FAILURE, "The denominator (%u) is out of range. "
		    "Should be (0,%d]", b, INT_MAX);
	bs = (int)b;
	dt.quot = (int)floor((double)a / bs);
	dt.rem = a - bs * dt.quot;
	return dt;
}

/*
 * ∀a,b∈ℤ ∃!q,r∈ℤ: a=b×q+r; 0≤r<|b|
 * ⎧q=⌊a/b⌋, r=b×{a/b}; b>0
 * ⎨
 * ⎩q=⌈a/b⌉; b<0
 */
div_t euclidian_div(int a, int b)
{
	div_t dt;

	if (b == 0)
		errx(EXIT_FAILURE, "The denominator can't be 0");
	else if (b > 0)
		dt.quot = (int)floor((double)a / b);
	else
		dt.quot = (int)ceil((double)a / b);
	dt.rem = a - b * dt.quot;
	return dt;
}

/*
 * ∀a∈ℤ,b∈ℕ ∃!q,r∈ℤ: a=b×q-r; 0≤r<b
 * q=⌈a/b⌉
 */
div_t div_with_neg_rem(int a, unsigned b)
{
	div_t dt;
	int bs;

	if (b == 0 || b > INT_MAX)
		errx(EXIT_FAILURE, "The denominator (%u) is out of range. "
		    "Should be (0,%d]", b, INT_MAX);
	bs = (int)b;
	dt.quot = (int)ceil((double)a / bs);
	dt.rem = a - bs * dt.quot;
	return dt;
}

/*
 * ∀a,b∈ℤ ∃!q,r∈ℤ: a=b×q-r; 0≤r<|b|
 * ⎧q=⌈a/b⌉; b>0
 * ⎨
 * ⎩q=⌊a/b⌋, r=b×{a/b}; b<0
 */
div_t div_away_from_zero(int a, int b)
{
	div_t dt;

	if (b == 0)
		errx(EXIT_FAILURE, "The denominator can't be 0");
	else if (b > 0)
		dt.quot = (int)ceil((double)a / b);
	else
		dt.quot = (int)floor((double)a / b);
	dt.rem = a - b * dt.quot;
	return dt;
}	

/*
 * ∀a,b∈ℤ ∃!q,r∈ℤ: a=b×q+r
 * q=⌊a/b⌉=⌈a/b-0.5⌉
 * ⎧r∈[-(b-1)/2,(b-1)/2], b-odd
 * ⎨
 * ⎩r∈(-b/2,b/2], b-even
 */
div_t div_nearest_int(int a, int b)
{
	div_t dt;

	if (b == 0)
		errx(EXIT_FAILURE, "The denominator can't be 0");
	dt.quot = (int)ceil(((double)a / b) - 0.5);
	dt.rem = a - b * dt.quot;
	return dt;
}

/********************TESTS********************/
#include <assert.h>

static void test_div(div_t (*divp)(int, int),size_t args_len, int (*args)[2],
    int (*expect)[2])
{
	div_t dt;
	size_t i = 0;

	for (i = 0; i < args_len; ++i) {
		dt = divp(args[i][0], args[i][1]);
		assert(dt.quot == expect[i][0] && dt.rem == expect[i][1]);
	}
}

static void test_regular_div_with_rem(void)
{
	int args[][2] = {{8,3}, {-8,3}, {1,2}, {-1,2}, {0,5},};
	int expect[][2] = {{2,2}, {-3,1}, {0,1}, {-1,1}, {0,0},};
	div_t (*divp)(int, int) = (div_t (*)(int, int))regular_div_with_rem;

	test_div(divp, sizeof args / sizeof args[0], args, expect);
}

static void test_euclidian_div(void)
{
	int args[][2] = {
	    {8,3}, {8,-3}, {-8,3}, {-8,-3},
	    {1,2}, {1,-2}, {-1,2}, {-1,-2},
	    {0,5},
	};
	int expect[][2] = {
	    {2,2}, {-2,2}, {-3,1}, {3,1},
	    {0,1}, {0,1}, {-1,1}, {1,1},
	    {0,0},
	};

	test_div(euclidian_div, sizeof args / sizeof args[0], args, expect);
}

static void test_div_with_neg_rem(void)
{
	int args[][2] = {{8,3}, {-8,3}, {1,2}, {-1,2}, {0,5},};
	int expect[][2] = {{3,-1}, {-2,-2}, {1,-1}, {0,-1}, {0,0},};
	div_t (*divp)(int, int) = (div_t (*)(int, int))div_with_neg_rem;

	test_div(divp, sizeof args / sizeof args[0], args, expect);
}

static void test_div_away_from_zero(void)
{
	int args[][2] = {
	    {8,3}, {8,-3}, {-8,3}, {-8,-3},
	    {1,2}, {1,-2}, {-1,2}, {-1,-2},
	    {0,5},
	};
	int expect[][2] = {
	    {3,-1}, {-3,-1}, {-2,-2}, {2,-2},
	    {1,-1}, {-1,-1}, {0,-1}, {0,-1},
	    {0,0},
	};

	test_div(div_away_from_zero, sizeof args / sizeof args[0], args, expect);
}

static void test_div_nearest_int(void)
{
	int args[][2] = {
	    {8,3}, {8,-3}, {-8,3}, {-8,-3},
	    {1,2}, {1,-2}, {-1,2}, {-1,-2},
	    {0,5},
	};
	int expect[][2] = {
	    {3,-1}, {-3,-1}, {-3,1}, {3,1},
	    {0,1}, {-1,-1}, {-1,1}, {0,-1},
	    {0,0},
	};

	test_div(div_nearest_int, sizeof args / sizeof args[0], args, expect);
}

int main(void)
{
	test_regular_div_with_rem();
	test_euclidian_div();
	test_div_with_neg_rem();
	test_div_away_from_zero();
	test_div_nearest_int();
	return EXIT_SUCCESS;
}
