# Problem no. 49: Prime permutations
###### SOLVED ######


from common.primes import find_primes
from tools.timer import Timer


def permutations(seq):
    """Generates all permutations of a list of objects
    :returns: list of permutations of seq"""
    lens = len(seq)
    if lens == 1:
        return [seq]
    else:
        perms = []
        perms_prev = permutations(seq[:-1])
        new_el = seq[-1]
        for p_prev in perms_prev:
            for i in range(lens):
                perms.append(p_prev[:i] + [new_el] + p_prev[i:])
        return perms


# All possible permutations of indexes for a 4-digit number
four_digit_perms = permutations([0, 1, 2, 3])


def number_permutations(n):
    """Generates all permutation numbers of a 4-digit number
    :returns: list of ints"""
    global four_digit_perms
    n_str = str(n)
    n_perm_strings = []
    for idx_perm in four_digit_perms:
        n_perm_strings.append([n_str[idx] for idx in idx_perm])
    return [int("".join(s)) for s in n_perm_strings]


def find_arithmetic_sequence(seq):
    """Finds an arithmetically increasing triplet in a sequence
    :returns: list of 3 ints if there's an arithmetic sequence, None otherwise"""
    if len(seq) < 3:
        return None
    else:
        for i in range(len(seq)-2):
            s_i = seq[i]
            k = i + 2
            stop_j = False
            for j in range(i+1, len(seq)-1):
                dif = seq[j] - s_i
                expect = seq[j] + dif
                while seq[k] < expect:
                    k += 1
                    # If k exceeds the bounds of the sequence, break
                    # iteration for j
                    if k >= len(seq):
                        stop_j = True
                        break
                if stop_j:
                    break
                # Found a triplet
                if seq[k] == expect:
                    return [s_i, seq[j], expect]
        return None


def solve():
    prime_tab = find_primes(10 ** 4)
    # primes in 10^3-10^4
    prime_set = set(prime_tab).difference(set(find_primes(1000)))
    print(len(prime_tab))
    # Partition the prime set into permutations
    prime_perm_groups = []
    while prime_set:
        p = prime_set.pop()
        # Find all permutations of p that are primes too
        p_perms = [p]
        for p_gen in number_permutations(p):
            if p_gen in prime_set:
                p_perms.append(p_gen)
                prime_set.remove(p_gen)
        if len(p_perms) >= 3:
            prime_perm_groups.append(sorted(p_perms))
    print("Prime permutation groups:", len(prime_perm_groups))
    print(prime_perm_groups)
    for pp_group in prime_perm_groups:
        arithm_triple = find_arithmetic_sequence(pp_group)
        if arithm_triple:
            print("Prime perm group:", pp_group)
            print("Arithmetic sequence:", arithm_triple)


if __name__ == '__main__':
    # n_perms = number_permutations(1234)
    # print(len(n_perms))
    # print(n_perms)
    Timer.start_measure()
    solve()
    Timer.print_time_elapsed()
