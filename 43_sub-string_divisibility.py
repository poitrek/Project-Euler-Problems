# Problem no. 43: Sub-string divisibility
###### SOLVED ######

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

# Searched numbers form:
# ABCDEFGHIJ, where 2 | BCD, 3 | CDE, 5 | DEF, 7 | EFG, 11 | FGH, 13 | GHI
# F = 0 or 5, D in {0,2,4,6,8}

# Generates all two- and three-digit multiples of n, whose digit do not repeat
def gen_multiples(n):
    muls = []
    # 2-digit multiples
    for k in range(10 + n - 10 % n, 100, n):
        strk = str(k)
        if strk[0] != strk[1] and strk[1] != 0:
            muls.append('0' + strk)
    # 3-digit multiples
    for k in range(100 + n - 100 % n, 1000, n):
        strk = str(k)
        if strk[0] != strk[1] and strk[0] != strk[2] and strk[1] != strk[2]:
            muls.append(strk)
    return muls


def number_parts(numbers):
    prefixes, suffixes = [], []
    for num in numbers:
        prefixes.append(num[:2])
        suffixes.append(num[1:])
    return prefixes, suffixes

# Idea:
# Make sets with all the multiples, sets with their first 2,
# and last 2 digits
Timer.start_measure_time()

mul_7 = gen_multiples(7)
mul_11 = gen_multiples(11)
mul_13 = gen_multiples(13)
mul_17 = gen_multiples(17)


# For mul_11 first digit should be 0 or 5
mul_11 = [m11 for m11 in mul_11 if m11[0] in ['0', '5']]

# For mul_7 second digit should be 5 (0 has been excluded by m11)
mul_7 = [m7 for m7 in mul_7 if m7[1] in ['5']]

#  F = 5 !!

# Exclude mul_13s and mul_17s containing digit 5 - already used by F
mul_13 = [m13 for m13 in mul_13 if '5' not in m13]
mul_17 = [m17 for m17 in mul_17 if '5' not in m17]


print('EFG - multiple of 7:')
print(mul_7, '({} numbers)'.format(len(mul_7)))
print('FGH - multiple of 11:')
print(mul_11, '({} numbers)'.format(len(mul_11)))
print('GHI - multiple of 13:')
print(mul_13, '({} numbers)'.format(len(mul_13)))
print('HIJ - multiple of 17:')
print(mul_17, '({} numbers)'.format(len(mul_17)))

# Get prefixes (first two digits) and suffixes (last two digits) of the numbers
# m7_pref, m7_suf = number_parts(mul_7)
# m11_pref, m11_suf = number_parts(mul_11)
# m13_pref, m13_suf = number_parts(mul_13)
# m17_pref, m17_suf = number_parts(mul_17)

cand_6_last = []

for m11 in mul_11:
    for m7 in mul_7:
        # If common digits of these numbers match and the other are different
        if m11[:2] == m7[1:] and m11[2] != m7[0]:
            numstr = m7[0] + m11
            for m13 in mul_13:
                if m13[:2] == m11[1:] and m13[2] not in numstr:
                    numstr = numstr + m13[2]
                    for m17 in mul_17:
                        if m17[:2] == m13[1:] and m17[2] not in numstr:
                            numstr = numstr + m17[2]
                            print('Candidate:', numstr)
                            cand_6_last.append(numstr)

cand_full = []

# Every candidate contains last 6 digits: EFGHIJ
for cand in cand_6_last:
    rem_digits = set('0123456789').difference(set(cand))
    # For every remaining even digit
    for D in rem_digits.intersection(set('02468')):
        for C in rem_digits.difference({D}):
            if int(C + D + cand[0]) % 3 == 0:
                last_2_digs = rem_digits.difference({C, D})
                B = last_2_digs.pop()
                A = last_2_digs.pop()
                last_8_digs = C + D + cand
                cand_full.append(A + B + last_8_digs)
                cand_full.append(B + A + last_8_digs)

print('Final full candidates:')
for cand in cand_full:
    print(cand)

print('Their sum:')
candsum = sum([int(cand) for cand in cand_full])
print(candsum)

Timer.print_time_elapsed()
