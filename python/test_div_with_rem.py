import div_with_rem

# floor_div
def test_floor_div():
    inputs = [
      (8, 3), (-8, 3),
      (1, 2), (-1, 2),
      (0, 1729),
    ]
    expected_results = [
      (2, 2), (-3, 1),
      (0, 1), (-1, 1),
      (0, 0),
    ]
    
    for (a, b), (exp_quot, exp_rem) in zip(inputs, expected_results):
        quot, rem = div_with_rem.floor_div(a, b)
        assert(quot == exp_quot)
        assert(rem == exp_rem)

# run tests
test_floor_div()
