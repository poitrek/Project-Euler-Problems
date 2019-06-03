s = []
plik = open("components.txt", "r")

for l in plik:

    k = l[0:12]  # Wstawiamy do tablicy wyłącznie pierwsze 12 cyfr liczby
    s.append( int(k) )  

plik.close()

Sum = 0
for i in s:
    Sum += i
