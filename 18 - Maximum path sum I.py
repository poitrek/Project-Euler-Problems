

file = open("triangle2.txt", "r")

T = [  ]
L = 0

for p in file:

    tabs = p.split(" ")
    tab = []
    for i in tabs:
        tab.append(int(i))
    T.append(tab)
    L += 1

file.close()

#print(T)

Max = 0


i  =  L - 2

while  i >= 0:

    for j in range(i+1):

        T[i][j] += max( T[i+1][j], T[i+1][j+1] )

    print(T[i])
    i -= 1
