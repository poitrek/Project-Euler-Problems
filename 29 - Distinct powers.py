base = 2

number = [2, 4, 8, 16, 32, 64]

Exp_value = [] # Tablica z wykładnikami w rozkładach na
               # czynniki wartości danej 'klasy'

def insert_values(number):

    for n in number:
        
        exp = IntLog(base, n)        
        for k in range(2, 101):

            X = exp*k
            if not X in Exp_value:
                Exp_value.append(X)

        


def IntLog(base, power):

    Counter = 0
    while power%base==0:        
        power = power//base
        Counter += 1
        
    return Counter
