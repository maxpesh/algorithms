typedef struct {
	int *partial_numers;
	int *partial_denoms;
	unsigned len;
} cont_fract;

cont_fract simple_cont_fraction(int, unsigned);
