def times_2(d = []):

    dn = []
    L = len(d)
    p = 0  # Przeniesienie na następną cyfrę
    for i in range(L):
    
        x = d[L-1-i]*2 + p

        if x > 9:
            x = x-10
            p = 1
        else:
            p = 0
        
        dn.append(x) # Dodajemy kolejną cyfrę do wyniku
    if p == 1:
        dn.append(p)

    L = len(dn)
    for i in range(L//2): # Odwracamy tabelę
        buf = dn[i]
        dn[i] = dn[L-1-i]
        dn[L-1-i] = buf    
    return dn

# Ta funkcja zwróci nam sumę cyfr n-tej potęgi dwójki
def SumOfDigits(n):

    P2 = [1]
    for i in range(n):
        P2 = times_2(P2)

    S = 0
    for k in P2:
        S += k
    return S
