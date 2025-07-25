#include "div_with_rem.h"

/*
 * ∀a∈ℤ,b∈ℕ ∃!q,r∈ℤ: a=b×q+r; 0≤r<b
 * q=⌊a/b⌋, r=b×{a/b} 
 *
 * If b = 0, then (a,b) = |a|
 * Otherwise, the algorithm proceeds as follows:
 * r_0 = a, r_1 = b
 * r_0 = q_1 * r_1 + r_2; 0 < r_2 < r_1
 * r_1 = q_2 * r_2 + r_3; 0 < r_3 < r_2
 *               . . .
 * r_n-2 = q_n-1 * r_n-1 + r_n; 0 < r_n < r_n-1
 * r_n-1 = q_n * r_n + 0
 *
 * (a,b) = (b,r_2) = (r_2,r_3) = ... = (r_n-1,r_n) = (r_n,0) = r_n
 *
 * Complexity:
 * -best case: Θ(1), when b|a
 * -worst case: Θ(5v); v - # of digits in in, b < |a|
 */
unsigned gcd_regular(int a, unsigned b)
{
	unsigned r;

	while (b != 0) {
		r = (unsigned)regular_div_with_rem(a, b).rem;
		a = (int)b;
		b = r;
	}
	return (unsigned)abs(a);
}

/*
 * ∀a∈ℤ,b∈ℕ ∃!q,r∈ℤ: a=b×q-r; 0≤r<b
 * q=⌈a/b⌉
 *
 * If b = 0, then (a,b) = |a|
 * Otherwise, the algorithm proceeds as follows:
 * r_0 = a, r_1 = b
 * r_0 = q_1 * r_1 - r_2; 0 < r_2 < r_1
 * r_1 = q_2 * r_2 - r_3; 0 < r_3 < r_2
 *               . . .
 * r_n-2 = q_n-1 * r_n-1 - r_n; 0 < r_n < r_n-1
 * r_n-1 = q_n * r_n - 0
 *
 * (a,b) = (b,r_2) = (r_2,r_3) = ... = (r_n-1,r_n) = (r_n,0) = r_n
 *
 * Complexity:
 * -best case: Θ(1), when b|a
 * -worst case: Θ(b); b < |a|
 */
unsigned gcd_with_neg_rem(int a, unsigned b)
{
	unsigned r;

	while (b != 0) {
		r = (unsigned)regular_div_with_rem(a, b).rem;
		a = (int)b;
		b = r;
	}
	return (unsigned)abs(a);
}
