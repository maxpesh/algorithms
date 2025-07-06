#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include "div_with_rem.h"

#define BUF_SIZE (sizeof(int) * CHAR_BIT)

static signed char buf[BUF_SIZE];

signed char *radix_conv(int n, unsigned rd, unsigned *len)
{
	signed char *ds = buf;
	unsigned i = 0, j = 0;

	*len = 0;
	do {
		div_t dt;
		if (n >= 0)
			dt = regular_div_with_rem(n, rd);
		else
			dt = div_with_neg_rem(n, rd);
		*ds++ = (signed char)dt.rem;
		++*len;
		n = dt.quot;
	} while (n != 0);
	/* reverse */
	for (i = 0, j = *len-1; i < j; ++i, --j) {
		signed char t = buf[i];
		buf[i] = buf[j];
		buf[j] = t;
	}
	return buf;
}
