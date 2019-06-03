# Problem rozwiązany!
# Odpowiedź: 5777

def IsPrime_(n):

    if n<2: return False
    if n==2: return True
    if n%2==0: return False
    is_prime = True
    SQRT = int(n**0.5)
    i = 3
    while i <= SQRT:
        if n%i==0:
            is_prime = False
            break
        i+=2
    return is_prime

def SearchNumber(ptab, M1, M2):

    i = M1
    if M1%2==0:
        i += 1
        
    ite = 0
    while ptab[ite]<i:
        ite += 1
    cur_prime = ptab[ite]
    
    while i <= M2:

        if i==cur_prime:
            ite += 1
            cur_prime = ptab[ite]
            i += 2
            continue

        j = 1
        FOUND = False
        K = i - 2*j**2        
        while not IsPrime( K, ptab ):            
            j += 1
            K = int(i - 2*j**2)
            if K < 0:
                FOUND = True
                break

        if FOUND:
            print("Found the number:", i)
            break
        #else:
            #print(i," = ",i-2*j**2," + 2 * ",j,"^2",sep='')
            
        i+=2


ptab = []
# Funkcja skopiowana z 50-Consecutive primes
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
        
# Pomiar czasu wykonywania powyższej funkcji
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
    SQRT = n**0.5
    is_prime = True
    for p in ptab:
        if n%p == 0:
            is_prime = False
            break
        if p > SQRT:
            break
    return is_prime
