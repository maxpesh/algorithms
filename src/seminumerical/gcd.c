/*
 * r0 = a = q1 * b + r2; 0 ≤ r2 ≤ b
 * r1 = b = q2 * r2 + r3; 0 ≤ r3 ≤ r2
 * r2 = q3 * r3 + r4; 0 ≤ r4 ≤ r3
 *    . . .
 * rn-2 = qn-1 * rn-1 + rn; 0 ≤ rn ≤ rn-1
 * rn-1 = qn * rn + 0
 *
 * (a,b) = (b,r2) = (r2,r3) = ... = (rn-1,rn) = (rn,0) = rn
 *
 * Complexity:
 *  - best case: Θ(1), if b|a
 *  - worst case: O(5v); v - # of digits in min(a,b)
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
