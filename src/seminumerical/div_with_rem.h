/*
 * ∀a∈ℤ,b∈ℕ ∃!q,r∈ℤ: a=b×q+r; 0≤r<b
 * q=⌊a/b⌋, r=b×{a/b} 
 *
 * Contract: b∈(0,INT_MAX]
 */
extern div_t regular_div_with_rem(int a, unsigned b);

/*
 * ∀a,b∈ℤ ∃!q,r∈ℤ: a=b×q+r; 0≤r<|b|
 * ⎧q=⌊a/b⌋, r=b×{a/b}; b>0
 * ⎨
 * ⎩q=⌈a/b⌉; b<0
 *
 * Contract: b!=0
 */
extern div_t euclidian_div(int a, int b);

/*
 * ∀a∈ℤ,b∈ℕ ∃!q,r∈ℤ: a=b×q-r; 0≤r<b
 * q=⌈a/b⌉
 *
 * Contract: b∈(0,INT_MAX]
 */
extern div_t div_with_neg_rem(int a, unsigned b);

/*
 * ∀a,b∈ℤ ∃!q,r∈ℤ: a=b×q-r; 0≤r<|b|
 * ⎧q=⌈a/b⌉; b>0
 * ⎨
 * ⎩q=⌊a/b⌋, r=b×{a/b}; b<0
 *
 * Contract: b!=0
 */
extern div_t div_away_from_zero(int a, int b);
/*

 * ∀a,b∈ℤ ∃!q,r∈ℤ: a=b×q+r
 * q=⌊a/b⌉=⌈a/b-0.5⌉
 * ⎧r∈[-(b-1)/2,(b-1)/2], b-odd
 * ⎨
 * ⎩r∈(-b/2,b/2], b-even
 *
 * Contract b!=0
 */
extern div_t div_nearest_int(int a, int b);

/*
 * ∀a,b∈ℤ ∃!q,r∈ℤ: a=b×q+r; |r|<|b|
 * ⎧q=⌊a/b⌋, r=b×{a/b}; a and b have the same sign
 * ⎨
 * ⎩q=⌈a/b⌉; otherwise
 *
 * Contract b!=0
 */
extern div_t truncated_div(int a, int b);

/*
 * ∀a,b∈ℤ ∃!q,r∈ℤ: a=b×q+r; |r|<|b|
 * q=⌊a/b⌋, r=b×{a/b}
 *
 * Contract b!=0
 */
extern div_t floor_div(int a, int b);
