# Problem no. 41: Pandigital prime
###### SOLVED ######

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
        print('Time elapsed: {} s'.format(time_elapsed))


# Generates next greater/smaller permutation than the current one
def next_perm(s):
    i = -1
    while s[i] > s[i-1]:
        i -= 1
    if i == -1:
        return s[:i-1] + s[i] + s[i-1]
    else:
        # Index to make swap
        swi = -1
        while s[swi] > s[i-1]:
            swi -= 1
        if swi == -1:
            s_lat = s[i: swi] + s[i-1]
        else:
            s_lat = s[i: swi] + s[i-1] + s[swi+1:]
        return s[:i-1] + s[swi] + s_lat[::-1]


def is_prime(n):
    if n <= 1:
        return False
    elif n == 2:
        return True
    elif n % 2 == 0:
        return False
    else:
        nsq = math.ceil(math.sqrt(n))
        for k in range(3, nsq+1, 2):
            if n % k == 0:
                return False
        return True


if __name__ == '__main__':
    Timer.start_measure_time()

    # 8- and 9-pandigital numbers are always divisible by 3 and won't be prime.
    # Therefore make search through 7-pandigitals.

    # Generate consecutive permutations of 7654321, starting from the greatest,
    # until we get a number that is prime.

    s = '7654321'
    num = 7654321
    counter = 0
    while num > 1234567:
        s = next_perm(s)
        num = int(s)
        if is_prime(num):
            break
        counter += 1


    print(s)
    print('Number of iterations: {}'.format(counter))

    Timer.print_time_elapsed()
