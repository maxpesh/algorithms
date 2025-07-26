#include <math.h>
#include "continued_fraction.h"
#include "div_with_rem.h"

#define MAX_LEN 20
static int numers_buf[MAX_LEN];
static int denoms_buf[MAX_LEN];

cont_fract simple_cont_fraction(int p, unsigned q)
{
	cont_fract cf = {NULL, NULL, 0};
	unsigned r;

	if (q == 0)
		return cf;
	cf.partial_numers = numers_buf;
	cf.partial_denoms = denoms_buf;
	while (q != 0 && cf.len < MAX_LEN) {
		div_t dt = regular_div_with_rem(p, q);
		cf.partial_numers[cf.len] = 1;
		cf.partial_denoms[cf.len++] = dt.quot;
		r = (unsigned)dt.rem;
		p = (int)q;
		q = r;
	}
	return cf;
}

/*
convergents regular_convergents(double d)
{
	convergents c = {a, 0};
	int q = (int)floor(d);
	double r = d - q;

	while (r != 0 && c.len < MAX_LEN) {
		d = 1 / r;
		q = (int)floor(d);
		c.partial_denoms[c.len++] = q;
		r = d - q;
	}
	return c;
}
*/
