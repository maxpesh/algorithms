#include <math.h>
#include "continued_fraction.h"
#include "div_with_rem.h"

#define MAX_LEN 20
static int numers_buf[MAX_LEN];
static int denoms_buf[MAX_LEN];
static double convergents_buf[MAX_LEN];

/*
 * ∀a∈ℤ,b∈ℕ ∃!q,r∈ℤ: a=b×q+r; 0≤r<b
 * q=⌊a/b⌋, r=b×{a/b} 
 *
 * r_0 = a, r_1 = b
 * r_0 = q_1 * r_1 + r_2; 0 < r_2 < r_1
 * r_1 = q_2 * r_2 + r_3; 0 < r_3 < r_2
 *               . . .
 * r_n-2 = q_n-1 * r_n-1 + r_n; 0 < r_n < r_n-1
 * r_n-1 = q_n * r_n + 0
 *
 * Simple continued fraction:
 * a / b = [q_1;q_2,...q_n] = q_1 + _____________1_____________
 *                                  q_2 + ___________1_________
 *                                        q_3 + _______1_______
 *                                              q_4 + ...
 *                                                        + _1_
 *                                                          q_n
 * Convergents:
 * [a_0;a_1,...,a_i] = p_i / q_i
 * p_n = [a_0,a_1,...,a_n] = a_n * p_n-1 + p_n-2
 * q_n = [a_1,a_2,...,a_n] = a_n * q_n-1 + q_n-2
 */
cont_fract simple_cont_fraction(int p, unsigned q)
{
	cont_fract cf = {NULL, NULL, NULL, 0};
	int ps[3] = {0, 1, 0};
	int qs[3] = {1, 0, 0};
	unsigned r = 0;

	if (q == 0)
		return cf;
	cf.partial_numers = numers_buf;
	cf.partial_denoms = denoms_buf;
	cf.convergents = convergents_buf;
	while (q != 0 && cf.len < MAX_LEN) {
		div_t dt = regular_div_with_rem(p, q);
		cf.partial_numers[cf.len] = 1;
		cf.partial_denoms[cf.len] = dt.quot;
		ps[2] = dt.quot * ps[1] + ps[0];
		ps[0] = ps[1], ps[1] = ps[2];
		qs[2] = dt.quot * qs[1] + qs[0];
		qs[0] = qs[1], qs[1] = qs[2];
		cf.convergents[cf.len++] = (double)ps[2] / qs[2];
		r = (unsigned)dt.rem;
		p = (int)q;
		q = r;
	}
	return cf;
}

/*
 * ∀a∈ℤ,b∈ℕ ∃!q,r∈ℤ: a=b×q-r; 0≤r<b
 * q=⌊a/b⌋, r=b×{a/b} 
 *
 * r_0 = a, r_1 = b
 * r_0 = q_1 * r_1 - r_2; 0 < r_2 < r_1
 * r_1 = q_2 * r_2 - r_3; 0 < r_3 < r_2
 *               . . .
 * r_n-2 = q_n-1 * r_n-1 - r_n; 0 < r_n < r_n-1
 * r_n-1 = q_n * r_n - 0
 *
 * Simple continued fraction with minuses:
 * a / b = [q_1;q_2,...q_n] = q_1 - _____________1_____________
 *                                  q_2 - ___________1_________
 *                                        q_3 - _______1_______
 *                                              q_4 - ...
 *                                                        - _1_
 *                                                          q_n
 * Convergents:
 * [a_0;a_1,...,a_i] = p_i / q_i
 * p_n = [a_0,a_1,...,a_n] = a_n * p_n-1 - p_n-2
 * q_n = [a_1,a_2,...,a_n] = a_n * q_n-1 - q_n-2
 */
cont_fract simple_cont_fraction_with_minuses(int p, unsigned q)
{
	cont_fract cf = {NULL, NULL, NULL, 0};
	int ps[3] = {0, 1, 0};
	int qs[3] = {-1, 0, 0};
	unsigned r = 0;

	if (q == 0)
		return cf;
	cf.partial_numers = numers_buf;
	cf.partial_denoms = denoms_buf;
	cf.convergents = convergents_buf;
	while (q != 0 && cf.len < MAX_LEN) {
		div_t dt = div_with_neg_rem(p, q);
		cf.partial_numers[cf.len] = 1;
		cf.partial_denoms[cf.len] = dt.quot;
		ps[2] = dt.quot * ps[1] - ps[0];
		ps[0] = ps[1], ps[1] = ps[2];
		qs[2] = dt.quot * qs[1] - qs[0];
		qs[0] = qs[1], qs[1] = qs[2];
		cf.convergents[cf.len++] = (double)ps[2] / qs[2];
		r = (unsigned)abs(dt.rem);
		p = (int)q;
		q = r;
	}
	return cf;
}
