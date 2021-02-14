# Problem no. 22: Circular primes
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


def eratosthenes_sieve(N):
    # Increment once in order to remove redundancy
    N += 1
    prime = [True] * (N)
    primes_tab = [2]
    for c in range(3, N, 2):
        if prime[c] == True:
            primes_tab.append(c)
            # Mark all multiples of c as composite
            for mul_c in range(c*c, N, c):
                prime[mul_c] = False
    return primes_tab


# Checks if the number has the circular prime property
def circ_prime(s, primes_tab):
    for i in range(len(s)):
        x = int(s[i:] + s[:i])
        if x not in primes_tab:
            return False
    return True


if __name__ == '__main__':
    Timer.start_measure_time()
    primes = set(eratosthenes_sieve(10**6))
    Timer.print_time_elapsed()
    digits = ['1', '3', '7', '9']
    counter = 0
    circprimes = [2, 3, 5, 7]
    # Test 3-digit numbers
    for a in digits:
        for b in digits:
            s2 = a + b
            if circ_prime(s2, primes):
                circprimes.append(int(s2))
            for c in digits:
                s3 = s2 + c
                if circ_prime(s3, primes):
                    circprimes.append(int(s3))
                for d in digits:
                    s4 = s3 + d
                    if circ_prime(s4, primes):
                        circprimes.append(int(s4))
                    for e in digits:
                        s5 = s4 + e
                        if circ_prime(s5, primes):
                            circprimes.append(int(s5))
                        for f in digits:
                            s6 = s5 + f
                            if circ_prime(s6, primes):
                                circprimes.append(int(s6))
    print('Found {} circular primes:'.format(len(circprimes)))
    print(circprimes)
    Timer.print_time_elapsed()
