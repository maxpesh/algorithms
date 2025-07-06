#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <assert.h>
#include "radix_conv.h"

int main(void)
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
		signed char *digs = radix_conv(test_cases[i][0],
		    (unsigned)test_cases[i][1], &len);
		char *s = strdup(expected[i]);

		for (j = 0; j < len; ++j) {
			s = strtok(s, ",");
			assert(atoi(s) == digs[j]);
			s = NULL;
		}
	}
	return EXIT_SUCCESS;
}
