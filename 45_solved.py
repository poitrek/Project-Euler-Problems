# Problem no. 46: Triangular, pentagonal, and hexagonal
###### SOLVED ######
"""
Problem: find an integer that is triangular,
pentagonal, and hexagonal, greater than 40755.
Note: we don't need to check the triangularity,
since each hexagonal number is triangular too:
 H(k) = T(2k+1) for every natural k.

Algorithm:
Calculate consequent pentagonal and check if
they are hexagonal using the inverse function.
"""
from math import sqrt


def p(n):
    return n*(3*n - 1) // 2


def h(n):
    return n*(2*n - 1)


def h_inv(x):
    """Hexagonal inverse function"""
    return (sqrt(8*x+1)+1) / 4


def is_hex(x):
    """Checks if x is a hexagonal number using
    the inverse function"""
    return h_inv(x).is_integer()


if __name__ == '__main__':
    iter_limit = 10**9
    iter_start = 166
    for i in range(iter_start, iter_limit):
        p_i = p(i)
        if is_hex(p_i):
            h_idx = int(h_inv(p_i))
            print(f"p({i}) = {p_i} = h({h_idx})")
            break
