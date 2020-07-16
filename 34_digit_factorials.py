# Problem no. 34: Digit factorials
###### NOT SOLVED ######

factorials = []
for i in range(10):
    p = 1
    for j in range(1, i+1):
        p *= j
    factorials.append(p)

print(factorials)

def digfac(n):
    fsum = 0
    for c in str(n):
        fsum += factorials[int(c)]
    return fsum


for k in range(40):
    print('{} <- {}'.format(k, digfac(k)))
