ptab = []

# 1) Funkcja uzupełnia tablicę liczb pierwszych
#(gdy jest pusta lub gdy zawiera już pewne elementy)
# do wszystkich l. pierwszych mniejszych lub równych N
def SetTabPrimes(p_tab, N):
    if N<2:
        return
    if p_tab == []:
        p_tab.append(2)
    if N==2:
        return
    
    I = p_tab[-1] + 1
    while I <= N:

        is_prime = True
        sqrt = int(I**0.5)
        for p in p_tab:
            if I%p == 0:
                is_prime = False
                break
            if p > sqrt:
                break
            
        if is_prime:
            p_tab.append(I)
        I += 1

# 1a) Pomiar czasu wykonywania powyższej funkcji
import time
def STP_time(p_tab, N):

    t1 = time.time()
    SetTabPrimes(p_tab, N)
    t2 = time.time()
    print("Process time:", t2-t1)

# 2) Funkcja sprawdzająca, na podstawie gotowej tablicy
# liczb pierwszych ptab, przekazywanej jako parametr,
# czy dana liczba n jest pierwsza
def IsPrime(n, ptab):
    SQRT = int(n**0.5)
    is_prime = True
    for p in ptab:
        if n%p == 0:
            is_prime = False
            break
        if p > SQRT:
            break
    return is_prime
'''  Zamiast sprawdzać w powyższej funkcji, czy liczba n
    znajduje się w tablicy ptab sprawdzamy, czy nie dzieli
    się przez któryś z jej elementów. MIMO, ŻE działanie mod
    też kosztuje trochę czasu, wystarczy sprawdzać do sqrt(n)

    [ Jeśli istnieje k > sqrt(n) takie, że k|n, to istnieje
    też takie j < sqrt(n) takie, że j|n. Tą liczbą jest j = n/k ]
'''

# 3) Funkcja zwracająca sumę n początkowych liczb pierwszych z
# danej tablicy ptab przekazywanej jako parametr
def PrimeSum(n, ptab):
    Sum = 0
    for i in range(n):
        Sum += ptab[i]
    return Sum
