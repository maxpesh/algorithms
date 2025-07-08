#include <stdlib.h>
#include <assert.h>
#include "gcd.h"

static void test_gcd(unsigned (*gcdp)(int, int))
{
	int args[][2] = {
	    {15,10}, {15,-10}, {-15,10}, {-15,-10},
	    {10,15}, {10,-15}, {-10,15}, {-10,15},
	    {4,2}, {4,-2}, {-4,2}, {-4,-2},
	    {2,4}, {2,-4}, {-2,4}, {-2,-4},
	    {13,8}, {13,-8}, {-13,8}, {-13,-8},
	    {0,1729}, {0,-1729}, {1729,0}, {-1729,0},
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
	test_gcd(gcd_euclidian_div);
	test_gcd(gcd_div_away_from_zero);
	test_gcd(gcd_truncated_div);
	test_gcd(gcd_floor_div);
	test_gcd(gcd_div_nearest_int);
	return EXIT_SUCCESS;
}
