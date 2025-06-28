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
