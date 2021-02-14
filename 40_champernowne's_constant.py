# Problem no. 40: Champernowne's constant
# ------ SOLVED ------

# 0.12345678910111213141516...

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


def brute_force_sol():
    champ_const = ''
    limit = 10**6
    n = 1
    while len(champ_const) <= limit:
        champ_const += str(n)
        n += 1
    print(champ_const[:50], '...')
    print('...', champ_const[-50:])
    prod = 1
    for exponent in range(7):
        digit = champ_const[10**exponent - 1]
        print('10^{}-th digit: {}'.format(exponent, digit))
        prod *= int(digit)
    print('Digits\' product: {}'.format(prod))



if __name__ == '__main__':

    Timer.start_measure_time()

    brute_force_sol()

    Timer.print_time_elapsed()
