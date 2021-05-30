# Problem no. 34: Digit factorials
###### SOLVED ######

import time
import matplotlib.pyplot as plt
import math


class Timer:
    _start_time = None
    @classmethod
    def start_measure_time(cls):
        cls._start_time = time.perf_counter()

    @classmethod
    def print_time_elapsed(cls):
        time_elapsed = time.perf_counter() - cls._start_time
        print('Time elapsed: {:.3f} s'.format(time_elapsed))


factorials = []
for i in range(10):
    p = 1
    for j in range(1, i+1):
        p *= j
    factorials.append(p)


def digfac(n):
    fsum = 0
    for c in str(n):
        fsum += factorials[int(c)]
    return fsum


def find_results():
    results = []
    for k in range(10**5):
        dgf = digfac(k)
        # print('{} <- {}'.format(k, dgf))
        if k == dgf:
            print('dgf({}) = {}'.format(k, dgf))
            results.append(k)
    return results


def plot_digfac(start, stop):
    y = [digfac(i) for i in range(start, stop)]
    # plt.style.use('seaborn-muted')
    plt.figure(figsize=(12, 6))
    plt.ylabel('f(x)')
    plt.xlabel('x')
    # print(plt.style.available)
    plt.plot(y, 'b-')
    plt.show()


if __name__ == '__main__':
    # Timer.start_measure_time()
    # print(factorials)
    # print('Found results:')
    # print(find_results())
    # Timer.print_time_elapsed()
    plot_digfac(2, 10000)
