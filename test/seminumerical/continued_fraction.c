#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include "continued_fraction.h"

static void test_run(int (*cases)[2], cont_fract *expected, unsigned ncases,
		     cont_fract (*cont_fractp)(int, unsigned))
{
	unsigned i = 0, j = 0;

	for (i = 0; i < ncases; ++i) {
		cont_fract expect = expected[i];
		cont_fract res = cont_fractp(cases[i][0], (unsigned)cases[i][1]);

		assert(res.len == expect.len);
		for (j = 0; j < res.len; ++j) {
			assert(res.partial_numers[j] == expect.partial_numers[j]);
			assert(res.partial_denoms[j] == expect.partial_denoms[j]);
			assert(fabs(res.convergents[j] - expect.convergents[j]) < 0.000001);
		}
	}
}

static void test_simple_cont_fraction(void)
{
	int cases[][2] = {
	    {20,13},
	    {-20,13},
	    {99,70},
	    {13,8}, /* worst case: a = F7, b = F6 */
	    {8,2}, {8,-2}, {-8,2}, {-8,-2}, /* best cases: b|a */
	};
	cont_fract expected[] = {
	    {(int[]){1,1,1,1}, (int[]){1,1,1,6},
	     (double[]){1.0, 2.0, 3.0/2, 20.0/13}, 4},
	    {(int[]){1,1,1}, (int[]){-2,2,6},
	     (double[]){-2, -3.0/2, -20.0/13}, 3},
	    {(int[]){1,1,1,1,1,1}, (int[]){1,2,2,2,2,2},
	     (double[]){1, 3.0/2, 7.0/5, 17.0/12, 41.0/29, 99.0/70}, 6},
	    {(int[]){1,1,1,1,1}, (int[]){1,1,1,1,2},
	     (double[]){1, 2, 3.0/2, 5.0/3, 13.0/8}, 5},
	    {(int[]){1}, (int[]){4}, (double[]){4}, 1},
	    {(int[]){1}, (int[]){-4}, (double[]){-4}, 1},
	    {(int[]){1}, (int[]){-4}, (double[]){-4}, 1},
	    {(int[]){1}, (int[]){4}, (double[]){4}, 1},
	};
	unsigned ncases = sizeof expected / sizeof expected[0];

	test_run(cases, expected, ncases, simple_cont_fraction);
}

static void test_simple_cont_fraction_with_minuses(void)
{
	int cases[][2] = {
	    {20,13},
	    {-20,13},
	    {99,70},
	    {5,4}, /* worst case: b = a - 1 */
	    {8,2}, {8,-2}, {-8,2}, {-8,-2}, /* best cases: b|a */
	};
	cont_fract expected[] = {
	    {(int[]){1,1,1,1,1,1,1}, (int[]){2,3,2,2,2,2,2},
	     (double[]){2, 5.0/3, 8.0/5, 11.0/7, 14.0/9, 17.0/11, 20.0/13}, 7},
	    {(int[]){1,1,1}, (int[]){-1,2,7},
	     (double[]){-1, -3.0/2, -20.0/13}, 3},
	    {(int[]){1,1,1,1,1,1}, (int[]){2,2,4,2,4,2},
	     (double[]){2, 3.0/2, 10.0/7, 17.0/12, 58.0/41, 99.0/70}, 6},
	    {(int[]){1,1,1,1}, (int[]){2,2,2,2},
	     (double[]){2, 3.0/2, 4.0/3, 5.0/4}, 4},
	    {(int[]){1}, (int[]){4}, (double[]){4}, 1},
	    {(int[]){1}, (int[]){-4}, (double[]){-4}, 1},
	    {(int[]){1}, (int[]){-4}, (double[]){-4}, 1},
	    {(int[]){1}, (int[]){4}, (double[]){4}, 1},
	};
	unsigned ncases = sizeof expected / sizeof expected[0];

	test_run(cases, expected, ncases, simple_cont_fraction_with_minuses);
}

int main(void)
{
	test_simple_cont_fraction();
	test_simple_cont_fraction_with_minuses();
	return EXIT_SUCCESS;
}
