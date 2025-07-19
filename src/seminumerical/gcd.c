#include "div_with_rem.h"

/*
 * ∀a∈ℤ,b∈ℕ
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
 * -best case: Θ(1), if b|a
 * -worst case: O(5v); v - # of digits in min(a,b).
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
