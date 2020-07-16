# Problem no. 37: Truncatable primes
###### SOLVED ######

# 1. 3797: 797, 97, 7; 379, 37, 3
# 2. 797: 97, 7; 79, 7
# 3. 73: 3; 7
# 4. 53: 3; 5
# 5. 37: 7; 3
# 6. 23: 2; 3
# 7. 313: 13, 3; 31, 3
# 8. 317: 17, 7; 31, 3
# 9. 373: 73, 3; 37, 3
# 10. 739397: 39397, 9397, 397, 97, 7; 73939, 7393, 739, 73, 7
# 11. 3137


# Others' rules:
# 1. Number must start with either 3 or 7, end with either 3 or 7
#    and consist inside only of 1, 3, 7, 9
# 2. If number is more than 3-digital, it has to have exactly two digits
#    from the set {1, 7}

# Facts:
# - The number cannot start with 5, because the first truncation from the
# right with a digit 1 or 7 will be divisible by 3. If there are no digits 1 or 7
# (only 3 and 9), all truncations from the left will be divisible by 3.
# - For the same reason cannot start with 2 (if longer than 2 digits)
# - The number cannot contain more than 2 digits from {1, 7} - if so, then any
# truncation containing 3 of such digits will be divisible by 3

# 371977973
# 379391937137
# 010001001101
# 59933739139371

# 393139337 - NO
# 7399393313 - MAYBE
# 319393373 - MAYBE

# 313: 31, 3, 13, 3


first2d = ['37', '31', '73', '79']
last2d =  ['13', '73', '37', '97']

# Any possible truncatable candidate form:
# first2d[i] + 'xxx...xx' + last2d[j]
# where every x is 3 or 9


truncatable_primes = {23, 37, 53, 73, 313, 317, 373, 797, 3797}

import math

# Global set containing all primes found while truncating
truncated_primes = {3, 7}

# Tells if the number is prime. If so, it's added to global set of found primes
def is_prime(n):
    if n in truncated_primes:
        return True
    if n <= 1:
        return False
    if n == 2:
        return True
    if n % 2 == 0:
        return False
    n_sq = math.ceil(math.sqrt(n)) + 1
    for k in range(3, n_sq, 2):
        if n % k == 0:
            return False
    truncated_primes.add(n)
    return True


# Tells if given number is truncatable prime
def is_truncatable(n_str):
    # From index
    if not is_prime(int(n_str)):
        return False
    for buffer in range(1, len(n_str)):
        n_prefix = int(n_str[:buffer])
        if not is_prime(n_prefix):
            return False
        n_suffix = int(n_str[buffer:])
        if not is_prime(n_suffix):
            return False
    return True


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


if __name__ == '__main__':
    Timer.start_measure_time()
    LIMIT = 10**10
    counter = 9
    k = 0
    try:
        while len(truncatable_primes) < 11:
            mid_digits = bin(k)[3:]
            mid_digits = mid_digits.replace('0', '3').replace('1', '9')
            for f2d in first2d:
                for l2d in last2d:
                    candidate = f2d + mid_digits + l2d
                    n_candidate = int(candidate)
                    if n_candidate > LIMIT:
                        raise Exception('The candidate numbers exceeded given limit! Value: {}'.format(candidate))
                    if is_truncatable(candidate):
                        if n_candidate not in truncatable_primes:
                            print('Truncatable prime:', candidate)
                            truncatable_primes.add(int(candidate))
            k += 1
    finally:
        print('Sum of all truncatable primes:', sum(truncatable_primes))
        Timer.print_time_elapsed()
        # print('Truncated primes: {}'.format(len(truncated_primes)))
        # print(truncated_primes)

