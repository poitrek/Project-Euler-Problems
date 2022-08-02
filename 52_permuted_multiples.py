# Problem no. 52: Permuted multiples
###### SOLVED ######

"""
Remark no. 1:
The number 2x should be in range
1.0 ... 3.33(3) x 10^n
for some n. Otherwise 2x and 6x will have different number of digits. Hence
0.5 <= x <= 1.66(6)
Remark no. 2:
x must be divisible by 3. Otherwise 2x and 3x have different sums of digits
mod 3, and cannot have the same digits.
Remark no. 2.5:
x must be divisible by 9. Otherwise 2x won't be divisible by 9, when 3x is,
since we know that x is divisible by 3. We use the same rule as divisibility
by 3 to conclude that 2x and 3x will contain different digits.
Remark no. 3:
The smallest x cannot be divisible by 10. If a number x has the desired property
and is divisible by 10, then x/10 will have it too.
"""
from collections import defaultdict
from tools.timer import Timer
from math import ceil


def digit_cnt(n: int):
    d_cnt = defaultdict(int)
    for c in str(n):
        d_cnt[int(c)] += 1
    return d_cnt


def ceil_to_multiple(n: int, k: int):
    """Rounds up n to the nearest multiple of k, e.g.
    ceil_to_multiple(100, 9) --> 108"""
    return n + (k - n % k) % k


def check_permuted_multiples(n: int) -> bool:
    # ns, n2s, n3s, n4s, n5s = digit_cnt(n), digit_cnt(n*2), digit_cnt(n*3), digit_cnt(n*4), digit_cnt(n*5)
    n2s, n3s, n4s, n5s, n6s = sorted(str(n*2)), sorted(str(n*3)), \
                              sorted(str(n*4)), sorted(str(n*5)), sorted(str(n*6))
    return n2s == n3s and n2s == n4s and n2s == n5s and n2s == n6s


if __name__ == '__main__':
    Timer.start_measure()
    for exp in range(7):
        stop = False
        # Start of the checked range
        rng_start = 5 * 10**exp
        # Round to the multiple of 9
        rng_start = ceil_to_multiple(rng_start, 9)
        # End of the checked range
        rng_end = ceil(16.7 * 10**exp)
        for n in range(rng_start, rng_end, 9):
            if n % 10 != 0 and check_permuted_multiples(n):
                print(n, n * 2, n * 3, n * 4, n * 5, n * 6)
                stop = True
                break
        if stop:
            break

    # for n in range(9, 16_000_000, 9):
    #     if check_permuted_multiples(n):
    #         print(n, n*2, n*3, n*4, n*5, n*6)
    #         break
    Timer.print_time_elapsed()
