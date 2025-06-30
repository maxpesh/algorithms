#include <stdlib.h>
#include <math.h>

static double const eps = 1E-24;

double heron_approx(unsigned a)
{
	double x = a;

	for (;;) {
		double xn = (x + a / x) / 2;
		if (fabs(xn - x) < eps)
			break;
		else
			x = xn;
	}
	return x;
}
