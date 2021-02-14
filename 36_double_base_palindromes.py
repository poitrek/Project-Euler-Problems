# Problem no. 36: Double-base palindromes

"""
Note 1: check only odd integers. Even numbers in binary
system end with '0', and always start with '1'.
"""


def palindrome(sr):
    return sr == sr[::-1]


if __name__ == '__main__':
    s = 0
    iter_stop = 10**6
    for i in range(1, 10**6, 2):
        if palindrome(str(i)) and palindrome(f'{i:b}'):
            s += i
            print(i, end=' ')
    print('\nSum =', s)
