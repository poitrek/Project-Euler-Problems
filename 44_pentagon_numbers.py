# Problem no. 44: Pentagon numbers
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


def p(n):
    return n*(3*n - 1)//2


coeff = math.sqrt(6) / 3

def in_seq(seq, value):
    idx = math.floor(coeff * math.sqrt(value))
    while(seq[idx] <= value):
        if seq[idx] == value:
            return idx
        idx += 1
    return None

def in_seq_bool(seq, value):
    idx = math.floor(coeff * math.sqrt(value))
    while(seq[idx] <= value):
        if seq[idx] == value:
            return True
        idx += 1
    return False


def test_custom_func():
    pentas = []
    for i in range(1, 4050):
        pentas.append(p(i))

    print(pentas[:30], '...', pentas[-10:])
    counter = 0
    for i in range(2000):
        for j in range(i):
            pes = pentas[i] + pentas[j]
            in_pent = in_seq(pentas, pes)
            if in_pent is not None:
                # if pes in pentas:
                counter += 1
                # pes2 = pentas[i] + pes
                # if in_seq_bool(pentas, pes2):
                #     print('p({}) + p({}) = p({})'.format(j, i, in_pent))
                #     print('{}     {}     {}'.format(pentas[j], pentas[i], pes))
                #     print('p({}) + p({}) = p({})'.format(i, in_pent, pentas.index(pes2)))
                #     print('{}     {}     {}'.format(pentas[i], pes, pes2))
    print('Found cases: {}'.format(counter))


# Verified: we can skip such i that P(i) mod 5 = 2 (i mod 5 = 3 or 4)


def test_with_set():
    pent_size = 7000
    pent_iter_limit = int(pent_size * 0.578)

    pentas = []
    for i in range(1, pent_size):
        pentas.append(p(i))
    print(pentas[:50], '...', pentas[-10:])
    pentasset = set(pentas)
    counter = 0
    for i in range(0, pent_iter_limit):
        for j in range(0, i):
            pes = pentas[i] + pentas[j]
            if pes in pentasset:
                counter += 1
                # print('p({}) + p({}) = p({})'.format(j, i, pentas.index(pes)))
                # print('{}     {}     {}'.format(pentas[j], pentas[i], pes))
                pes2 = pentas[i] + pes
                if pes2 in pentasset:
                    print_result(i, j, pentas, pes, pes2)

    # New method - iterate only i where i mod 5 = 0, 1 or 2
    # for i_5 in range(0, pent_iter_limit, 5):
    #     i = i_5
    #     for j in range(0, i):
    #         pes = pentas[i] + pentas[j]
    #         if pes in pentasset:
    #             counter += 1
    #             # print('p({}) + p({}) = p({})'.format(j, i, pentas.index(pes)))
    #             # print('{}     {}     {}'.format(pentas[j], pentas[i], pes))
    #             pes2 = pentas[i] + pes
    #             if pes2 in pentasset:
    #                 print_result(i, j, pentas, pes, pes2)
    #     i = i_5 + 1
    #     for j in range(0, i):
    #         pes = pentas[i] + pentas[j]
    #         if pes in pentasset:
    #             counter += 1
    #             pes2 = pentas[i] + pes
    #             if pes2 in pentasset:
    #                 print_result(i, j, pentas, pes, pes2)
    #     i = i_5 + 2
    #     for j in range(0, i):
    #         pes = pentas[i] + pentas[j]
    #         if pes in pentasset:
    #             counter += 1
    #             pes2 = pentas[i] + pes
    #             if pes2 in pentasset:
    #                 print_result(i, j, pentas, pes, pes2)

    print('Found cases: {}'.format(counter))


def print_result(i, j, pentas, pes, pes2):
    print('p({}) + p({}) = p({})'.format(j, i, pentas.index(pes)))
    print('{}     {}     {}'.format(pentas[j], pentas[i], pes))
    print('p({}) + p({}) = {}'.format(i, pentas.index(pes), pes2))
    print('FOUND: p({}) = {}'.format(pentas.index(pes2), pes2))


if __name__ == '__main__':
    Timer.start_measure_time()

    # test_custom_func()
    test_with_set()
    Timer.print_time_elapsed()
