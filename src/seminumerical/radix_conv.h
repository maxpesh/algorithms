typedef struct {
	signed char *digits;
	unsigned len;
} digits;

digits radix_convi(int a, unsigned char r);

typedef struct {
	signed char* int_part;
	signed char* fract_part;
	unsigned int_part_len;
	unsigned fract_part_len;
} rational_digits;

rational_digits radix_convf(double a, unsigned char r);
