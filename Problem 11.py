file = open("numbers.txt", "r")

tab = [ [0 for i in range(20)] for j in range(20) ] 

for i in range(20):
    s = file.readline()
    tabs = s.split(" ")
    for j in range(20):
        tab[i][j] = int(tabs[j])

file.close()

Max = 8 * 2 * 22 * 97
pmax = [0,0]

for i in range(20):
    for j in range(17):

        x = tab[i][j] * tab[i][j+1] * tab[i][j+2] * tab[i][j+3]
        if x > Max:
            Max = x
            pmax = [i, j]

print(Max)

for i in range(20):
    for j in range(17):

        x = tab[j][i] * tab[j+1][i] * tab[j+2][i] * tab[j+3][i]
        if x > Max:
            Max = x

print(Max)

for i in range(17):
    for j in range(17):

        x = tab[i][j] * tab[i+1][j+1] * tab[i+2][j+2] * tab[i+3][j+3]
        if x > Max:
            Max = x

print(Max)

for i in range(3, 20):
    for j in range(0, 17):

        x = tab[i][j] * tab[i-1][j+1] * tab[i-2][j+2] * tab[i-3][j+3]
        if x > Max:
            Max = x
            pmax = [i, j]

print(Max, pmax)
