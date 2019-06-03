def factorial_notation(n):

    Ftab = []
    i = 1
    while math.factorial(i+1) < n: i += 1
    Ftab.append(i)
    while i > 0:

        fact = math.factorial(i)
        ff = n // fact
        Ftab.append(ff)
        n = n % fact
        i -= 1

    return Ftab

# Problem rozwiązany!
