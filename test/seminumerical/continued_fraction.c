#include <stdlib.h>
#include <assert.h>
#include "continued_fraction.h"

void test_simple_cont_fraction(void)
{
	int cases[][2] = {
	    {20, 13},
	    {-20, 13},
	    {99, 70},
	};
	cont_fract expected[] = {
	    {(int[]){1,1,1,1}, (int[]){1,1,1,6}, 4},
	    {(int[]){1,1,1}, (int[]){-2,2,6}, 3},
	    {(int[]){1,1,1,1,1,1}, (int[]){1,2,2,2,2,2}, 6},
	};
	unsigned i = 0, j = 0;
	unsigned ncases = sizeof expected / sizeof expected[0];

	for (i = 0; i < ncases; ++i) {
		cont_fract expect = expected[i];
		cont_fract res = simple_cont_fraction(cases[i][0], (unsigned)cases[i][1]);

		assert(res.len == expect.len);
		for (j = 0; j < res.len; ++j) {
			assert(res.partial_numers[j] == expect.partial_numers[j]);
			assert(res.partial_denoms[j] == expect.partial_denoms[j]);
		}
	}
}

int main(void)
{
	test_simple_cont_fraction();
	return EXIT_SUCCESS;
}
