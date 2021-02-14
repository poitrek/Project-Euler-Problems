# Problem no. 31: Coin sums
###### SOLVED ######

calls = 0

# Recurrent solution without memorizing (inefficient)
def dispenses(S, n):
    # print('disp({}, {})'.format(S, n))
    global calls
    calls += 1
    if n == 0:
        return 1
    if n < 0:
        return 0
    # If nominal set consists only of 1 element
    if len(S) == 1:
        return int(n % S[0] == 0)
        # return 1 if n % S[0] == 0 else 0
    return dispenses(S[:-1], n) + dispenses(S, n - S[-1])

def dispense_dynamic(S, n):
    # Array of memorized counts for every number up to n and
    # set of nominals
    arr = [[-1] * len(S) for _ in range(n+1)]
    def disp(S, n):
        k = len(S)
        if arr[n][k-1] == -1:
            if n == 0:
                res = 1
            elif n < 0:
                res = 0
            elif k == 1:
                res = int(n % S[0] == 0)
            else:
                if n - S[-1] >= 0:
                    res = disp(S[:-1], n) + disp(S, n - S[-1])
                else:
                    res = disp(S[:-1], n)
            arr[n][k-1] = res
        return arr[n][k-1]
    return disp(S, n)


if __name__ == '__main__':
    disp = dispense_dynamic([1, 2, 4, 8], 25)
    print('Dispenses:', disp)
    # print('Function calls:', calls)