#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <assert.h>
#include "radix_conv.h"

static void test_radix_convi(void)
{
	int test_cases[][2] = {
	    {109,10}, {-109,10},
	    {109,2}, {-109,2},
	    {109,36}, {-109,36},
	    {0,10}, {0,2}, {0,36},
	    {INT_MAX,10}, {INT_MIN,10},
	    /* {INT_MAX,2}, {INT_MIN,2}, */
	    {INT_MAX,36}, {INT_MIN,36},
	};
	char *expected[] = {
	    "1,0,9", "-1,0,-9",
	    "1,1,0,1,1,0,1", "-1,-1,0,-1,-1,0,-1",
	    "3,1", "-3,-1",
	    "0", "0", "0",
	    "2,1,4,7,4,8,3,6,4,7", "-2,-1,-4,-7,-4,-8,-3,-6,-4,-8",
	    "35,18,20,0,35,19", "-35,-18,-20,0,-35,-20",
	};
	unsigned nc = sizeof test_cases / sizeof *test_cases;
	unsigned i = 0;

	for (i = 0; i < nc; ++i) {
		unsigned j = 0, len = 0;
		signed char *digs = radix_convi(test_cases[i][0],
		    (unsigned char)test_cases[i][1], &len);
		char *s = strdup(expected[i]);

		for (j = 0; (s = strtok(s, ",")) != NULL; ++j) {
			assert(j < len);
			assert(atoi(s) == digs[j]);
			s = NULL;
		}
	}
}

static void test_radix_convf(void)
{
	/* {number, base} */
	double test_cases[][2] = {
	    {109.703125,10}, {-109.703125,10},
	    {109.703125,2}, {-109.703125,2},
	    {1.5,2}, {-1.5,2},
	};
	char *expected[][2] = {
	    {"1,0,9","7,0,3,1,2,5"}, {"-1,0,-9", "-7,0,-3,-1,-2,-5"},
	    {"1,1,0,1,1,0,1", "1,0,1,1,0,1"}, {"-1,-1,0,-1,-1,0,-1", "-1,0,-1,-1,0,-1"},
	    {"1", "1"}, {"-1", "-1"},
	};
	unsigned ncases = sizeof test_cases / sizeof *test_cases;
	unsigned i = 0;

	for (i = 0; i < ncases; ++i) {
		double n = test_cases[i][0];
		unsigned char r = (unsigned char)test_cases[i][1];
		unsigned int_len, fract_len;
		fixed_point res;
		char *digstr;
		unsigned j = 0;

		res = radix_convf(n, r, &int_len, &fract_len);

		digstr = strdup(expected[i][0]);
		for (j = 0; (digstr = strtok(digstr, ",")) != NULL; ++j) {
			assert(j < int_len);
			assert(atoi(digstr) == res.int_part[j]);
			digstr = NULL;
		}
		digstr = strdup(expected[i][1]);
		for (j = 0; (digstr = strtok(digstr, ",")) != NULL; ++j) {
			assert(j < fract_len);
			assert(atoi(digstr) == res.fract_part[j]);
			digstr = NULL;
		}
	}
}


int main(void)
{
	test_radix_convi();
	test_radix_convf();
	return EXIT_SUCCESS;
}
