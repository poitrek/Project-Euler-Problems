def collatz(n, write_out = False):

    Counter = 0
    while n > 1:
        Counter += 1
        if write_out == True: print(n, "-> ", end = '')
        if n%2 == 0:
            n = n//2
        else:
            n = 3*n+1
    if write_out == True: print(n)
    return Counter

# Funkcja znajdująca najdłuższy 'łańcuch' Collatza wśród n początkowych
# liczb naturalnych. Jest ona szybsza, niż algorytm naiwny (standardowy, porównujący
# wartości funkcji collatz() dla kolejnych liczb naturalnych)

def biggest_col(n):

    tcol = [ 0, 0, 1, 7, 2, 5 ]
    Max = 7
    pmax = 3
    
    for i in range( 6 , n ):

        k = i
        Counter = 0
        while k >= i:
            if k%2==0: k = k//2
            else:      k = 3*k+1
            Counter += 1
        
        Counter += tcol[ k ]
        tcol.append(Counter)
        if  Counter > Max:
            Max = Counter
            pmax = i

    return [pmax, Max]
