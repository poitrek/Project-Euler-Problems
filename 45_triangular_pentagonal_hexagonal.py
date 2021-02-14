# Problem no. 46: Triangular, pentagonal, and hexagonal

from tools.timer import Timer

# N-th pentagonal number
def p(n):
    return n*(3*n-1)//2

# N-th hexagonal number
def h(n):
    return n*(2*n-1)


# p(n) - p(n-1) = 3n-2
# h(n) - h(n-1) = 4n-3

Timer.start_measure()

# p, h = 5, 6
# ip, ih = 2, 2
# while h < 10**13:
#     # print(p, h)
#     if p < h:
#         ip += 1
#         p += 3*ip - 2
#     elif h < p:
#         ih += 1
#         h += 4*ih - 3
#     else:
#         print('p({}) = h({}) = {}'.format(ip, ih, p))
#         ip += 1
#         ih += 1
#         p += ip
#         h += ih
#
# print('p({}) = {}, h({}) = {}'.format(ip, p, ih, h))

def test_modulo(base):
    print('Testing p and h mod {}'.format(base))
    h_mod = [h(i) % base for i in range(base)]
    p_mod = [p(i) % base for i in range(base)]
    h_mods, p_mods = set(h_mod), set(p_mod)
    common_mods = h_mods.intersection(p_mods)
    print('H_ remainders: {}'.format(h_mods))
    print('P_ remainders: {}'.format(p_mods))
    print('Common: {}'.format(common_mods))
    h_valid = len([1 for m in h_mod if m in common_mods])
    p_valid = len([1 for m in p_mod if m in common_mods])
    print('H_ valid: {} out of {} = {:.3f}'.format(h_valid, base, h_valid / base))
    print('P_ valid: {} out of {} = {:.3f}'.format(p_valid, base, p_valid / base))
    print('---------------------------')


def count_valid_mod(base):
    # print('Testing p and h mod {}'.format(base))
    h_mod = [h(i) % base for i in range(base)]
    p_mod = [p(i) % base for i in range(base)]
    h_mods, p_mods = set(h_mod), set(p_mod)
    common_mods = h_mods.intersection(p_mods)
    h_valid = len([1 for m in h_mod if m in common_mods])
    p_valid = len([1 for m in p_mod if m in common_mods])
    h_ratio = h_valid/base
    p_ratio = p_valid/base
    if h_ratio <= p_ratio:
        return h_ratio, 'h'
    else:
        return p_ratio, 'p'

# 4, 16, 36, 64, 100, 144, 196
#  12, 20, 28, 36, 44, 52
# remainder = 10
# print(' i  h(i) p(i)\tmod {}'.format(remainder))
# for i in range(0, remainder):
#     print('{:2d}|  {:2d}   {:2d}'.format(i, h(i) % remainder, p(i) % remainder))

import pandas as pd

valid_mod_counts = []
for base in range(10, 201):
    ratio, mode = count_valid_mod(base)
    valid_mod_counts.append((base, ratio, mode))

vmc_df = pd.DataFrame(valid_mod_counts, columns=['base', 'ratio', 'mode'])
print(vmc_df.sort_values(by='ratio').head(15))
# for vmc in valid_mod_counts:
#     print('{:d}, {:.3f}'.format(vmc[0], vmc[1]))
for base in vmc_df.sort_values(by='ratio')['base'].head(5):
    test_modulo(base)


Timer.print_time_elapsed()
