from math import ceil, sqrt


def is_prime(n):
    """Checks if n is a prime individually (without any global structure)
    When to use: (TODO)
    Time complexity: O(sqrt(n))
    :returns True if n is prime, False otherwise"""
    if n <= 1:
        return False
    if n == 2:
        return True
    if n % 2 == 0:
        return False
    n_sq = ceil(sqrt(n)) + 1
    for k in range(3, n_sq, 2):
        if n % k == 0:
            return False
    return True

def find_primes(N, method='eratosthenes'):
    """Finds all prime numbers less or equal N
    :param method: ('eratosthenes', 'sundaram', 'alg1')
    :returns: array of primes <=N"""
    if method == 'eratosthenes':
        return _find_primes_eratosthenes(N)
    elif method == 'sundaram':
        return _find_primes_sundaram(N)
    elif method == 'alg1':
        return _find_primes_alg1(N)
    else:
        raise Exception("Invalid prime searching method")

def _find_primes_eratosthenes(N):
    """Finds all prime numbers less or equal N using Eratosthenes Sieve.
    Use only when you need array of all primes <=N.
    Currently the fastest function for this task
    :returns array of primes <=N"""
    # Increment once in order to remove redundancy
    N += 1
    prime = [True] * (N)
    primes_tab = [2]
    for c in range(3, N, 2):
        if prime[c]:
            primes_tab.append(c)
            # Mark all multiples of c as composite
            for mul_c in range(c*c, N, c):
                prime[mul_c] = False
    return primes_tab


def _find_primes_sundaram(N):
    """Finds all primes less or equal N using Sundaram Sieve.
    Slower than Eratosthenes Sieve."""
    N = (N-1) // 2
    primes = []
    base = [True] * (N+1)
    for i in range(1, (N-1) // 3 + 1):
        for j in range(1, i+1):
            k = i + j + 2*i*j
            if k > N:
                break
            else:
                base[k] = False
            j += 1
    for k, val in enumerate(base):
        if val:
            primes.append(2*k + 1)
    primes[0] = 2
    return primes


def _find_primes_alg1(N):
    """Finds all primes less or equal N using method analogous
    to Eratosthenes Sieve (for each next odd number k, check
    if k is divisible by any of the already found primes).
    Slower than Eratosthenes and Sundaram Sieves."""
    primes = [2, 3]
    primes_sq = [4, 9]
    for c in range(5, N+1, 2):
        # c_sqrt = math.sqrt(c)
        i = 1
        # Iterate until we pass square root of c or find a divider of c
        while primes_sq[i] <= c and c % primes[i] != 0:
            i += 1
        # If the loop ended without finding a divider of c and surpassing square root of c
        if primes_sq[i] > c:
            primes.append(c)
            primes_sq.append(c*c)
    return primes
