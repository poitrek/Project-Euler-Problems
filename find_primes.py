import numpy as np
import math

import time
class Timer:
    _start_time = None
    @classmethod
    def start_measure_time(cls):
        cls._start_time = time.perf_counter()

    @classmethod
    def print_time_elapsed(cls):
        time_elapsed = time.perf_counter() - cls._start_time
        print('Time elapsed: {:.3f} s'.format(time_elapsed))


def find_primes_classic(N):
    primes = [2, 3]
    primes_sq = [4, 9]
    for c in range(5, N+1, 2):
        # c_sqrt = math.sqrt(c)
        i = 1
        # Iterate until we pass square root of c or find a divider of c
        while primes_sq[i] <= c and c % primes[i] != 0:
            i += 1
        # If the loop ended without finding a divider of c and surpassing square root of c
        if primes_sq[i] > c:
            primes.append(c)
            primes_sq.append(c*c)
    return primes


# Standard Eratosthenes Sieve
# This function is currently the fastest
def eratosthenes_sieve(N):
    # Increment once in order to remove redundancy
    N += 1
    prime = [True] * (N)
    primes_tab = [2]
    for c in range(3, N, 2):
        if prime[c] == True:
            primes_tab.append(c)
            # Mark all multiples of c as composite
            for mul_c in range(c*c, N, c):
                prime[mul_c] = False
    return primes_tab


# Uses the Sundaram Sieve to find primes
def sundaram_sieve(N):
    N = (N-1) // 2
    primes = []
    base = [True] * (N+1)
    for i in range(1, (N-1) // 3 + 1):
        for j in range(1, i+1):
            k = i + j + 2*i*j
            if k > N:
                break
            else:
                base[k] = False
            j += 1
    for k, val in enumerate(base):
        if val:
            primes.append(2*k + 1)
    primes[0] = 2
    return primes




if __name__ == '__main__':
    Timer.start_measure_time()
    # pr = find_primes_classic(4*10**6)
    pr = eratosthenes_sieve(10 ** 7)
    # pr = sundaram_sieve(10**6)
    print('Found {} primes'.format(len(pr)))
    print(pr[:10], '...', pr[-10:])
    Timer.print_time_elapsed()
