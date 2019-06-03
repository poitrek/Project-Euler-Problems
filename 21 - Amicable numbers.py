def sum(n):

    s = 0
    i = 1
    while i <= n//2:

        if n%i == 0:  s += i
        i += 1
    return s


S = 0

for i in range(2, 10001):

    if sum(sum(i))==i:
        if i != sum(i):
            S += i
            print(i, sum(i))

