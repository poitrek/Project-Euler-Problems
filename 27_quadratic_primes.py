# Problem no. 27: Quadratic primes
###### SOLVED ######


import numpy as np
import time

class Timer:
    def start_measure_time(self):
        self.start_time = time.perf_counter()

    def stop_measure_time(self):
        self.stop_time = time.perf_counter()
        self.time_elapsed = self.stop_time - self.start_time


primes = [2, 3, 5]
max_prime = 5

# Fills the global array of prime numbers with primes less or equal N
def find_primes(N):
    start = primes[-1] + 2
    for c in range(start, N+1, 2):
        c_sqrt = np.sqrt(c)
        i = 0
        # Iterate until we pass square root of c or find a divider of c
        while primes[i] <= c_sqrt and c % primes[i] != 0:
            i += 1
        # If the loop ended without finding a divider of c and surpassing square root of c
        if primes[i] > c_sqrt:
            primes.append(c)
    global max_prime
    max_prime = primes[-1]


def is_prime(n):
    # If n is outside the checked range
    if n < 2:
        return False
    elif n > max_prime:
        return 'unknown'
    elif n in primes:
        return True
    else:
        return False


def f(n, a, b):
    return n*(a+n)+b


def test_func(a, b, verbose=1):
    if verbose==1:
        print('a, b = {}, {}:'.format(a, b))
    n = 0
    while True:
        f_n = f(n, a, b)
        if verbose==1:
            print('{} + {}*{} + {} = {}'.format(n*n, a, n, b, f_n))
        is_pr = is_prime(f_n)
        if is_pr == False:
            break
        elif is_pr == 'unknown':
            print('Exceeded range of found primes!')
            break
        n += 1
    if verbose==1:
        print()
    return n


if __name__ == '__main__':
    timer = Timer()
    timer.start_measure_time()
    find_primes(5000)
    b_primes = primes[:170]
    primes = set(primes)
    print('{} primes found'.format(len(primes)))
    # print(primes[:10], '...')

    # print(test_func(1, 41, verbose=0))
    # print(test_func(9, 7))
    # max_test = 0
    # for b in primes[:20]:
    #     summ, count = 0, 0
    #     for a in range(-b, 500, 2):
    #         test = test_func(a, b, verbose=0)
    #         summ += test**3
    #         count += 1
    #         if test > max_test:
    #             print('{}, {} => {}'.format(a, b, test))
    #             max_test = test
    #     avg = np.power(summ / count, 1/3)
    #     print('Avg b={} : {:.3f}'.format(b, avg))

    max_a, max_b = 0, 0
    max_test = 1
    for b in b_primes:
        for a in range(-b+2, 1, 2):
            test = test_func(a, b, verbose=0)
            if test > max_test:
                # print('{}, {} => {}'.format(a, b, test))
                max_test = test
                max_a, max_b = a, b

    print('\nMaximum sequence of generated primes found for a = {}, b = {}'.format(max_a, max_b))
    print('{} primes in a row:'.format(max_test))
    print()
    test_func(max_a, max_b)

    timer.stop_measure_time()
    print('Program duration: {:.3f} s'.format(timer.time_elapsed))
