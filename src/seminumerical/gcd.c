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

#include <assert.h>

static void test_gcd(unsigned (*gcdp)(int, int))
{
	int args[][2] = {
	    {15,10}, {15,-10}, {-15,10}, {-15,-10},
	    {10,15}, {10,-15}, {-10,15}, {-10,15},
	    {4,2}, {4,-2}, {-4,2}, {-4,-2},
	    {2,4}, {2,-4}, {-2,4}, {-2,-4},
	    {13,8}, {13,-8}, {-13,8}, {-13,-8},
	    {0,1729}, {0, -1729}, {1729,0}, {-1729,0},
	};
	unsigned expect[] = {
	    5, 5, 5, 5,
	    5, 5, 5, 5,
	    2, 2, 2, 2,
	    2, 2, 2, 2,
	    1, 1, 1, 1,
	    1729, 1729, 1729, 1729,
	};
	size_t i = 0;

	for (i = 0; i < sizeof args / sizeof args[0]; ++i) {
		assert(gcdp(args[i][0], args[i][1]) == expect[i]);
	}
}

int main(void)
{
	test_gcd(gcd_mod_op);
	test_gcd(gcd_euclid);
	return EXIT_SUCCESS;
}
