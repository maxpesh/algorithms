#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <assert.h>
#include "radix_conv.h"

static void test_radix_convi(void)
{
	int cases[][2] = {
	    {109,10}, {-109,10},
	    {109,2}, {-109,2},
	    {109,36}, {-109,36},
	    {0,10}, {0,2}, {0,36},
	    {INT_MAX,10}, {INT_MIN,10},
	    /* {INT_MAX,2}, {INT_MIN,2}, */
	    {INT_MAX,36}, {INT_MIN,36},
	};
	digits expected[] = {
	    {(signed char[]){1,0,9}, 3}, {(signed char[]){-1,0,-9}, 3},
	    {(signed char[]){1,1,0,1,1,0,1}, 7},
	    {(signed char[]){-1,-1,0,-1,-1,0,-1}, 7},
	    {(signed char[]){3,1}, 2}, {(signed char[]){-3,-1}, 2},
	    {(signed char[]){0}, 1}, {(signed char[]){0}, 1},
	    {(signed char[]){0}, 1},
	    {(signed char[]){2,1,4,7,4,8,3,6,4,7}, 10},
	    {(signed char[]){-2,-1,-4,-7,-4,-8,-3,-6,-4,-8}, 10},
	    {(signed char[]){35,18,20,0,35,19}, 6},
	    {(signed char[]){-35,-18,-20,0,-35,-20}, 6},
	};
	unsigned ncases = sizeof cases / sizeof cases[0];
	unsigned i = 0;

	for (i = 0; i < ncases; ++i) {
		unsigned j = 0;
		digits d = radix_convi(cases[i][0], (unsigned char)cases[i][1]);

		assert(d.len == expected[i].len);
		for (j = 0; j < d.len; ++j)
			assert(d.digits[j] == expected[i].digits[j]);
	}
}

static void test_radix_convf(void)
{
	/* {number, base} */
	double cases[][2] = {
	    {109.703125,10}, {-109.703125,10},
	    {109.703125,2}, {-109.703125,2},
	    {1.5,2}, {-1.5,2},
	};
	rational_digits expected[] = {
	    {(signed char[]){1,0,9}, (signed char[]){7,0,3,1,2,5}, 3, 6},
	    {(signed char[]){-1,0,-9}, (signed char[]){-7,0,-3,-1,-2,-5}, 3, 6},
	    {(signed char[]){1,1,0,1,1,0,1}, (signed char[]){1,0,1,1,0,1}, 7, 6},
	    {(signed char[]){-1,-1,0,-1,-1,0,-1}, (signed char[]){-1,0,-1,-1,0,-1}, 7, 6},
	    {(signed char[]){1}, (signed char[]){1}, 1, 1},
	    {(signed char[]){-1}, (signed char[]){-1}, 1, 1},
	};
	unsigned ncases = sizeof cases / sizeof cases[0];
	unsigned i = 0;

	for (i = 0; i < ncases; ++i) {
		unsigned j = 0;
		rational_digits rd = radix_convf(cases[i][0], (unsigned char)cases[i][1]);
		
		assert(rd.int_part_len == expected[i].int_part_len);
		assert(rd.fract_part_len == expected[i].fract_part_len);
		for (j = 0; j < rd.int_part_len; ++j)
			assert(rd.int_part[j] == expected[i].int_part[j]);
		for (j = 0; j < rd.fract_part_len; ++j)
			assert(rd.fract_part[j] == expected[i].fract_part[j]);
	}
}


int main(void)
{
	test_radix_convi();
	test_radix_convf();
	return EXIT_SUCCESS;
}
