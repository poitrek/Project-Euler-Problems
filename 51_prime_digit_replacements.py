# Problem no. 51: Prime digit replacements
###### SOLVED ######

"""
Answer like:
A*BC**DE
- 3 (or multiple of 3) places for digits
e.g.
A0BC00DE A1BC11DE
A3BC33DE A4BC44DE
A5BC55DE A6BC66DE
A7BC77DE A8BC88DE
"""
import bisect
from common.primes import find_primes
from collections import defaultdict
from itertools import combinations


def find_primes_range(n_from, n_to):
    primes = find_primes(n_to)
    n_from_idx = bisect.bisect_left(primes, n_from)
    return primes[n_from_idx:]


def find_3_equal_digits(n) -> list:
    """checks if the number contains 3 equal digits
    :returns: list of all triples of indexes of number n that contain the same digit"""
    digit_idx = defaultdict(list)
    # n = str(n)
    for i, c in enumerate(n):
        digit_idx[c].append(i)
    # To return
    triple_indexes = []
    for d_idx in digit_idx.values():
        if len(d_idx) >= 3:
            triple_indexes.extend(combinations(d_idx, 3))
    return triple_indexes


def contains_3_equal_digits(n) -> bool:
    """checks if the number contains 3 equal digits"""
    dig_cnt = defaultdict(int)
    for c in str(n):
        dig_cnt[c] += 1
    for dcnt in dig_cnt.values():
        if dcnt >= 3:
            return True
    return False


def replace(arr, indexes: tuple, value):
    for idx in indexes:
        arr[idx] = value
    return arr


def replace_str(s: str, indexes: tuple, value) -> str:
    for idx in indexes:
        s = s[:idx] + value + s[idx+1:]
    return s


if __name__ == '__main__':
    primes = find_primes_range(100_000, 1_000_000)
    # primes = set(map(lambda x: list(str(x)), primes))
    primes = set(map(str, primes))
    for p in primes:
        equal_digit_indexes = find_3_equal_digits(p)
        if equal_digit_indexes:
            for eq_dig_idx in equal_digit_indexes:
                similar_primes = []
                for d in ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9']:
                    p = replace_str(p, eq_dig_idx, d)
                    if p in primes:
                        similar_primes.append(p)
                if len(similar_primes) > 6:
                    pattern = replace_str(p, eq_dig_idx, '*')
                    print(f'{len(similar_primes)} similar primes: ({pattern}) {similar_primes}')

