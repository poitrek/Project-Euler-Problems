def xprimes(n): # zwraca liczbę liczb pierwszych w przedziale [0, n]

    sum = 0
    if n < 2: return 0
    if n == 2: return 1
    p_tab = [3] # Dynamiczna tablica liczb pierwszych bez dwójki - podzielności
                # przez nią nie będziemy sprawdzać, liczby parzyste będą pomijane
    Counter = 2 # Jeśli n >= 3, to mamy już na wstępie 2 l. pierwsze
    sum += 2+3
    i = 5
    while i <= n:

        ff = True   
        for j in p_tab: #sprawdzamy podzielność i przez elementy tablicy l. pierwszych
            if i%j == 0:
                ff = False
                break
            if j > int(i**0.5): break

        if ff==True:  # i jest liczbą pierwszą
            p_tab.append(i)  # więc dodajemy ją do naszej tablicy
            Counter += 1
            sum += i
            
        i += 2

    print("Sum of all primes in the range:", sum)
    return Counter
