#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include "heron_approx.h"

int main(void)
{
	for (unsigned n = 1; n < 10; n++) {
		double expected = sqrt((double)n);
		double approx = heron_approx(n);
		assert(fabs(approx - expected) < 1E-3);
	}
	return EXIT_SUCCESS;
}
