# Problem no. 32: Pandigital products
###### SOLVED ######

from itertools import product

# ------- HARD APPROACH - CANCELLED -------

primes_global = [2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,
                 53,59,61,67,71,73,79,83,89,97]

# Factorizes a natural number
# Returns list of tuples:
# [(pr1, ex1), (pr2, ex2),...]
# pr1, pr2... - consecutive primes
# ex1, ex2... - corresponding exponents
def factorize(n):
    fact_exps = list()
    it = 0
    while n > 1 and it < len(primes_global):
        prime = primes_global[it]
        # Counter of the prime factor exponent
        exp_count = 0
        while n % prime == 0:
            n = n // prime
            exp_count += 1
        if (exp_count > 0):
            # Add to the list of prime factors
            fact_exps.append((prime, exp_count))
        it += 1
    # If n hasn't been reduced to 1 yet, then
    # it is the last prime factor
    if n > 1:
        fact_exps.append((n, 1))
    return fact_exps


def dividers(n):
    # Factorize n
    fact_exps = factorize(n)
    n_primes = len(fact_exps)

    # Find all dividers of n
    # ...



# -------- MUCH MORE SIMPLE APPROACH - FINISHED --------

'''
 39 x 186 = 7254

 AB x CDE = FGHI
 A x BCDE = FGHI
 A,B,C,D,E,F,G,H,I =>{1,2,...,9}
 k x l = m

 k,l % 5 != 0
 
'''
digits1_9 = ['1', '2', '3', '4', '5', '6', '7', '8', '9']

def pandigital(a, b, c):
    string = str(a)+str(b)+str(c)
    return sorted(string) == digits1_9

pand_triples = []
pand_products = set()

for i in range(12, 99):
    # If the number is divisble by 5
    if i % 5 == 0:
        continue
    # If the number contains 0 digit
    if '0' in str(i):
        continue
    for j in range(123, 987):
        # Filter with the same rule
        if j % 5 == 0 or '0' in str(j):
            continue
        prod = i * j
        if pandigital(i, j, prod):
            print(i, '*', j, '=', prod)
            pand_triples.append((i, j, prod))
            pand_products.add(prod)

for i in range(1, 10):
    if i == 5:
        continue
    for j in range(1234, 9877):
        if j % 5 == 0 or '0' in str(j):
            continue
        prod = i * j
        if pandigital(i, j, prod):
            print(i, '*', j, '=', prod)
            pand_triples.append((i, j, prod))
            pand_products.add(prod)
    

