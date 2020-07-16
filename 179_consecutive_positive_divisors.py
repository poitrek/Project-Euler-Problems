# Problem no. 179: Consecutive positive divisors
###### NOT SOLVED ######

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




# TODO: 1) Make eratosthenes sieve to find primes below 10^7,
#       factorization function based on the array of primes,
#       and divisors counting according to the factorization (simple)
#       2) Find out where or when consecutive numbers won't have the
#       same number of divisors


def sieve_primes(limit):
    limit += 1
    prime = [True] * (limit)
    primes_tab = [2]
    for k in range(3, limit, 2):
        if prime[k] == True:
            primes_tab.append(k)
            for mul_k in range(k*k, limit, k):
                prime[mul_k] = False
    return primes_tab


def n_divisors_from_primes(n, primes):
    # Square root of n
    # nsqrt = math.ceil(math.sqrt(n))
    nsqrt = math.floor(math.sqrt(n))
    # Array of exponents in the prime factorization of n (increased by 1 for further calculation)
    # exp_factors = []
    # Product of incremented exponents in the prime factorization of n
    exp_product = 1
    # i, pr_i = 0, 2
    # while n < 1:
    #     exp_count = 0
    #     while n % pr_i == 0:
    #         n /= pr_i
    #         exp_count += 1
    #     if exp_count > 0:
    #         exp_product *= exp_count + 1

    for p in primes:
        exp_count = 0
        while n % p == 0:
            n //= p
            exp_count += 1
        if exp_count > 0:
            exp_product *= exp_count + 1
        if p > nsqrt or n == 1:
            break
    # If n > 1, then there is still one prime divisor greater than nsqrt
    if n > 1:
        exp_product *= 2
    return exp_product


def n_divisors(n):
    nsqrt = math.sqrt(n)
    insqrt = math.ceil(nsqrt)
    counter = 2
    # For squares of natural numbers
    if insqrt == nsqrt:
        counter += 1
    for k in range(2, insqrt):
        if n % k == 0:
            counter += 2
    return counter


if __name__ == '__main__':
    Timer.start_measure_time()
    # M = 10**6
    # primes = sieve_primes(M)
    # primes_set = set(primes)

    for i in range(5, 101):
        print(i, n_divisors(i))
    # for i in range(2, M):
    #     if i not in primes_set:
    #         x = n_divisors_from_primes(i, primes)
        # x = n_divisors(i)

    Timer.print_time_elapsed()


