# Problem no. 47: Distinct primes factors
###### SOLVED ######

from tools.timer import Timer
from common.primes import find_primes
from math import sqrt


def has_4_factors(n, primes):
    """Checks if n has exactly 4 distinct prime factors"""
    factors = set()
    n_sqrt = sqrt(n)
    for p in primes:
        if n % p == 0:
            factors.add(p)
            # More than 4 factors are found, stop
            if len(factors) > 4:
                return False
            n //= p
            while n % p == 0:
                n //= p
        if n == 1:
            break
        if p > n_sqrt:
            factors.add(-1)
            break
    return len(factors) == 4


# def find_prime_factors(n, primes):
#     """Helper function to check duration of
#     repeated modulo & division operations"""
#     for p in primes:
#         while n % p == 0:
#             n //= p
    # ....


if __name__ == '__main__':
    Timer.start_measure()
    prime_limit = int(3.2 * 10 ** 4)
    pr = find_primes(prime_limit)
    # Limit of the iterated integers
    iter_limit = 10**6
    # length of current sequence of 4-factor ints
    four_fact_seq = 0
    for i in range(5, iter_limit):
        if has_4_factors(i, pr):
            four_fact_seq += 1
            if four_fact_seq > 2:
                print([j for j in range(i - four_fact_seq+1, i+1)])
                if four_fact_seq == 4:
                    break
        else:
            four_fact_seq = 0
    Timer.print_time_elapsed()
    print("\nFinished.")

