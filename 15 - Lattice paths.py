'''
Zadanie sprowadza się do obliczenia współczynnika dwumianowego
 f(n, k) = n!/(k!(n-k)!)
'''
def binom(n, k):

    if k > n-k:
        return binom(n, n-k)
    L = 1
    for i in range(n-k+1, n+1):
        L *= i
    M = 1
    for i in range(1, k+1):
        M *= i
    a = L//M
    return a
