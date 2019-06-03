# 28123  -  every number greater than this limit can be written as the sum of two
# abundant numbers. So, find all natural numbers (smaller than 28123), that cannot
# be represented as the sum of two abundant numbers.

def prop_div( n ):

    s = 0
    for i in range(1, n//2 + 1):

        if n % i == 0: s += i

    if s < n:
        return (s, "deficient")
    if s > n:
        return (s, "ABUNDANT")
    if s == n:
        return (s, "PERFECT")


# Tells how many are there abundant numbers  <= n, and distinguishes abundant numbers
# that are odd

def abund_num(n):

    Counter = 0
    for i in range(1, n+1):
        if prop_div(i)[1] == 'ABUNDANT':
            Counter += 1
            if i%2 == 1:
                print("Odd-abundant:", i)

    return Counter

even_abun = []
odd_abun = []

def set_even_abun(even_abun): # Adds all even-abundant numbers* to proper array
    i = 10
    while i < 28123:

        if i%6 == 0:
            even_abun.append(i)
            i += 2
            continue
        s = 0
        for j in range(1, i//2 + 1):
            if i%j == 0: s += j

        if s > i:
            even_abun.append(i)
        i += 2

def set_odd_abun(odd_abun): # Adds all even-abundant numbers* to proper array
    i = 945
    while i < 28123:
        s = 0
        for j in range(1, i//2 + 1):
            if i%j == 0: s += j
        if s > i:
            odd_abun.append(i)

        i += 30 #Zauważyliśmy, że "odd-abundants" różnią się zawsze o wielokrotność 30




#  * all abundant numbers < 28123

abun = []

def set_abun():

    co = 0
    ce = 0
    for i in range(0, len(even_abun)):

        if even_abun[ce] < odd_abun[co]:
            abun.append(even_abun[ce])
            ce += 1
        else:
            abun.append(odd_abun[co])
            co += 1

# Strasznie dużo mam tych funkcji...
def set_all():
    
    set_even_abun(even_abun)
    set_odd_abun(odd_abun)
    set_abun()
    
# Tells you whether given number can be broken up into sum of two abundant numbers,
# or not.

def abun_num2(n):

    if n < 12: return False
    if n%2 == 0:
        if n%6 == 0: return True
        s = 0
        for i in range(1, n//2 + 1):
            if n%i == 0: s+=i
        if s > n: return True
        else: return False
    if n%2 == 1:
        s = 0
        i = 1
        while i <= n//2 + 1:
            if n%i == 0: s += i
            i += 2
        if s > n: return True
        else: return False

def abun_num3(n):

    if n < 12: return False
    if n%6 == 0: return True
    i = 0
    while even_abun[i] < n: i += 1
    if even_abun[i] == n:
        return True
    else:
        return False
    
def improper1(n):

    T = "can be"
    F = "cannot"
    if n < 945 and n%2==1:
        return F

    i = 0
    while odd_abun[i] < n:
        x = n - odd_abun[i]
        if abun_num3(x):
            return T
        i += 1
    return F       
    


def improper(n):

    T = "can be"
    F = "cannot"
    if n < 945 and n%2==1:
        return F
    i = 0
    while abun[i] <= n//2:
        x = n - abun[i]
        if abun_num2(x):
            return T
        i += 1
    return F
