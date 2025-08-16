def floor_div(a, b):
    '''
    ∀a,b∈ℤ ∃!q,r∈ℤ: a=b×q+r; |r|<|b|
    q=⌊a/b⌋, r=b×{a/b}

    Contract b!=0
    '''
    return divmod(a, b)
