#include <stdlib.h>
#include <err.h>
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

unsigned gcd_euclid(int a, int b)
{
	int r;

	while (b != 0) {
		r = euclidian_div(a, b).rem;
		a = b;
		b = r;
	}
	return (unsigned)abs(a);
}
