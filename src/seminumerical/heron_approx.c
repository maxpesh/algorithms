/*
 * Heron's algorithm for approximating sqrt(a).
 *
 * Given a∈ℝ let x0 be any positive initial estimate:
 * xn+1 = (xn + a/xn)/2, until |xn+1-xn|<ε; ε∈ℝ- desired accuracy
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
