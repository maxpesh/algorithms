#include <stdlib.h>
#include <err.h>

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

#include <assert.h>

static void test_gcd(unsigned (*gcdp)(int, int))
{
	int args[][2] = {
	    {15,10}, {15,-10}, {-15,10}, {-15,-10},
	    {10,15}, {10,-15}, {-10,15}, {-10,15},
	    {13,8}, {13,-8}, {-13,8}, {-13,-8},
	    {0,1729}, {1729,0}
	};
	unsigned expect[] = {
	    5, 5, 5, 5,
	    5, 5, 5, 5,
	    1, 1, 1, 1,
	    1729, 1729
	};
	size_t i = 0;

	for (i = 0; i < sizeof args / sizeof args[0]; ++i) {
		assert(gcdp(args[i][0], args[i][1]) == expect[i]);
	}
}

int main(void)
{
	test_gcd(gcd_mod_op);
	return EXIT_SUCCESS;
}
