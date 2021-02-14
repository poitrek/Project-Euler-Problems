# Problem no. 44: Pentagon numbers
###### SOLVED ######
import math

import time
class Timer:
    _start_time = None
    @classmethod
    def start_measure_time(cls):
        cls._start_time = time.perf_counter()
    @classmethod
    def print_time_elapsed(cls, comment='Time elapsed'):
        time_elapsed = time.perf_counter() - cls._start_time
        print('{}: {:.3f} s'.format(comment, time_elapsed))


def p(n):
    return n*(3*n - 1) // 2


def search_alg3_corrected(pent_size=6000):
    """Corrected alg1 search method. Finally works.
    :returns desired difference D"""
    pentas = [p(i) for i in range(1, pent_size)]
    print(pentas[:50], '...', pentas[-10:])
    pentasset = set(pentas)
    Timer.print_time_elapsed('Set creation time')
    pent_iter_limit = int(pent_size * 0.7)
    for i in range(0, pent_iter_limit):
        p_i = pentas[i]
        for j in range(0, i-1):
            pes = p_i + pentas[j]
            if pes in pentasset:
                pes2_1, pes2_2 = pes + pentas[j], pes + p_i
                if pes2_1 in pentasset:
                    return p_i
                if pes2_2 in pentasset:
                    return pentas[j]


"""
==============================================
All then approaches below have a common mistake
that makes it impossible to solve the problem.
==============================================
"""

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


def search_alg_2():
    pentas = [p(i) for i in range(1, 4050)]
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


def search_alg_1(pent_size=6000):
    """Search for pentagonal quadruple using a
    set of pentagonals. First implementation
    :return number of found pentagonal triples"""
    # Arbitrary list of pentagonal numbers
    pentas = [p(i) for i in range(1, pent_size)]
    print(pentas[:50], '...', pentas[-10:])

    # Set made of list, for faster testing of inclusion in it
    pentasset = set(pentas)
    full_iter_proper_ratio = 0.578
    pent_iter_limit = int(pent_size * 0.8)
    triplet_cnt = 0
    for i in range(0, pent_iter_limit):
        # inner_range_start = int(i * 0.75)
        # inner_range_end = 1000
        p_i = pentas[i]
        for j in range(0, i):
            pes = p_i + pentas[j]
            if pes in pentasset:
                triplet_cnt += 1
                # print('p({}) + p({}) = p({})'.format(j, i, pentas.index(pes)))
                # print('{}     {}     {}'.format(pentas[j], pentas[i], pes))
                '''MISTAKE!!
                Should also calculate & check pentas[j] + pes !!'''
                pes2 = p_i + pes
                if pes2 in pentasset:
                    print_result_arr(i, j, pentas, pes, pes2)

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
    return triplet_cnt


def search_different_order(pent_size=6000):
    """Search for pentagonal quadruples similarly to
    search_alg_1, but in slightly changed order.
    This method assumes that the answer to the problem
    will be a relatively small number.
    :return number of found pentagonal triples"""
    pentas = [p(i) for i in range(1, pent_size)]
    print(pentas[:50], '...', pentas[-10:])
    pentasset = set(pentas)
    Timer.print_time_elapsed('Set creation time')
    triplet_cnt = 0
    pent_iter_limit = int(pent_size*0.7)
    first_iter_lim = int(pent_size*0.01)
    for j in range(0, 1000):
        p_j = pentas[j]
        iter_stop = min(pent_iter_limit, (p_j - 1) // 3 + 1)
        for i in range(j+1, iter_stop):
            pes = pentas[j] + pentas[i]
            if pes in pentasset:
                triplet_cnt += 1
                pes2 = pentas[i] + pes
                if pes2 in pentasset:
                    print_result_arr(i, j, pentas, pes, pes2)
    return triplet_cnt


def p_inv(n):
    """Pentagonal inverse function"""
    return (math.sqrt(24 * n + 1) + 1) / 6


def is_pentagonal(n):
    """Checks if n is a pentagonal number using the
    inverse function"""
    return p_inv(n).is_integer()


def search_inverse_check(pent_size=6000):
    """Search for pentagonal quadruple using
    the inverse function in is_pentagonal().
    Slower than search_alg1()."""
    pentas = [p(i) for i in range(1, pent_size)]
    print(pentas[:50], '...', pentas[-10:])
    triplet_cnt = 0
    pent_iter_limit = int(pent_size * 0.7)
    for i in range(0, pent_iter_limit):
        p_i = pentas[i]
        for j in range(0, i):
            pes = p_i + pentas[j]
            if is_pentagonal(pes):
                triplet_cnt += 1
                pes2 = pentas[i] + pes
                if is_pentagonal(pes2):
                    print_result_arr(i, j, pentas, pes, pes2)
    return triplet_cnt


def search_from_mathblog():
    """Search method found at mathblog.dk that
    explained the mistake"""
    i = 1
    while(True):
        i += 1
        p_i = p(i)
        for j in range(i-1, 0, -1):
            p_j = p(j)
            ij_sum_inv = p_inv(p_i + p_j)
            ij_dif_inv = p_inv(p_i - p_j)
            if ij_sum_inv.is_integer() and ij_dif_inv.is_integer():
                result = p_i - p_j
                print_result(i, j, int(ij_sum_inv), int(ij_dif_inv), result)
                return result


def print_result(i, j, ij_sum, ij_dif, DIFF):
    print(f"p({i}) + p({j}) = {p(i) + p(j)} = p({ij_sum})")
    print(f"p({i}) - p({j}) = {p(i) - p(j)} = p({ij_dif})")
    print(f"DIFF = {DIFF}")


def print_result_arr(i, j, pentas, pes, pes2):
    print('p({}) + p({}) = p({})'.format(j, i, pentas.index(pes)))
    print('{}     {}     {}'.format(pentas[j], pentas[i], pes))
    print('p({}) + p({}) = {}'.format(i, pentas.index(pes), pes2))
    print('FOUND: p({}) = {}'.format(pentas.index(pes2), pes2))


if __name__ == '__main__':
    Timer.start_measure_time()
    # n_pentagonals = 5000
    # triplet_count = search_alg_1(n_pentagonals)
    # triplet_count = search_inverse_check(n_pentagonals)
    # triplet_count = search_different_order(n_pentagonals)
    # print(f'Found pentagonal triplets: {triplet_count}')

    # CORRECT APPROACH
    result = search_alg3_corrected(10000)
    print(result)
    Timer.print_time_elapsed()
