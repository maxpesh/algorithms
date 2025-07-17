/*
 * ∀a,b∈ℤ
 * If b = 0, then (a,b) = |a|
 * Otherwise, the algorithm proceeds as follows:
 * r_0 = a, r_1 = b
 * r_0 = q_1 * r_1 + r_2; 0 ≤ r_2 ≤ r_1
 * r_1 = q_2 * r_2 + r_3; 0 ≤ r_3 ≤ r_2
 * r_2 = q_3 * r_3 + r_4; 0 ≤ r_4 ≤ r_3
 *               . . .
 * r_n-2 = q_n-1 * r_n-1 + r_n; 0 ≤ r_n ≤ r_n-1
 * r_n-1 = q_n * r_n + 0
 *
 * (a,b) = (b,r_2) = (r_2,r_3) = ... = (r_n-1,r_n) = (r_n,0) = r_n
 *
 * Complexity:
 * - best case: Θ(1), if b|a
 * - worst case: O(5v); v - # of digits in min(a,b).
 */

#include "div_with_rem.h"

unsigned gcd_mod_op(int a, int b)
{
	int r;

	while (b != 0) {
		r = a % b;
		a = b;
		b = r;
	}
	return (unsigned)abs(a);
}

unsigned gcd_euclidian_div(int a, int b)
{
	int r;

	while (b != 0) {
		r = euclidian_div(a, b).rem;
		a = b;
		b = r;
	}
	return (unsigned)abs(a);
}

unsigned gcd_div_away_from_zero(int a, int b)
{
	int r;

	while (b != 0) {
		r = div_away_from_zero(a, b).rem;
		a = b;
		b = r;
	}
	return (unsigned)abs(a);
}

unsigned gcd_truncated_div(int a, int b)
{
	int r;

	while (b != 0) {
		r = truncated_div(a, b).rem;
		a = b;
		b = r;
	}
	return (unsigned)abs(a);
}

unsigned gcd_floor_div(int a, int b)
{
	int r;

	while (b != 0) {
		r = floor_div(a, b).rem;
		a = b;
		b = r;
	}
	return (unsigned)abs(a);
}

/*
 * Fastest to converge, because 0 ≤ ri+1 ≤ ri / 2
 */
unsigned gcd_div_nearest_int(int a, int b)
{
	int r;

	while (b != 0) {
		r = div_nearest_int(a, b).rem;
		a = b;
		b = r;
	}
	return (unsigned)abs(a);
}
