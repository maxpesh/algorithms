typedef struct fixed_point {
	signed char* int_part;
	signed char* fract_part;
} fixed_point;

signed char *radix_convi(int a, unsigned char r, unsigned *l);
fixed_point radix_convf(double a, unsigned char r, unsigned *int_len, unsigned *fract_len);
