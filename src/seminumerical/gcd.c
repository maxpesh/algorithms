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
