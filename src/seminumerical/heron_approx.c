/*
 * Given a∈ℝ let x0 be any positive initial estimate:
 * x_n+1 = (x_n + a / x_n) / 2, until |x_n + 1 - x_n| < ε; ε∈ℝ- desired accuracy
 */

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
