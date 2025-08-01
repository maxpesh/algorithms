#include <stdlib.h>
#include <assert.h>
#include "gcd.h"

static void test_gcd(unsigned (*gcdp)(int, int))
{
	int args[][2] = {
	    {15,10}, {-15,10},
	    {10,15}, {-10,15},
	    {4,2}, {-4,2},
	    {2,4}, {-2,4},
	    {13,8}, {-13,8},
	    {0,1729}, {1729,0},
	};
	unsigned expect[] = {
	    5, 5,
	    5, 5,
	    2, 2,
	    2, 2,
	    1, 1,
	    1729, 1729,
	};
	size_t i = 0;

	for (i = 0; i < sizeof args / sizeof args[0]; ++i) {
		assert(gcdp(args[i][0], args[i][1]) == expect[i]);
	}
}

static void test_gcdn()
{
	int *args[] = {
	    (int[]){10,6,15,24}, (int[]){-10,6,-15,-24},
	};
	unsigned expect[] = {
	    1, 1,
	};
	size_t i = 0;

	for (i = 0; i < sizeof args / sizeof args[0]; ++i) {
		assert(gcdn(args[i], 4) == expect[i]);
	}
}

int main(void)
{
	test_gcd(gcd_regular);
	test_gcd(gcd_with_neg_rem);
	test_gcdn();
	return EXIT_SUCCESS;
}
