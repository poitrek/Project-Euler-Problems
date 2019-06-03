def unitfr(n, write_out = True):

    f = []
    r = []
    t = 1
    

    while(1):

        r.append(t)
        q = (10*t)//n
        f.append( q )
        t = 10*t - q*n

        Bool = False
        for j in range(len(r)):
            if t == r[j]:
                Bool = True
                cycle = j 
                break
        
        if Bool:
            break

    if write_out:
        
        print(f)
        s = ""
        for i in f:
            s += str(i)
        s = "0," + s[:cycle] + "(" + s[cycle:] + ")"
        print(s)
        print(r, "-", t)
        print(cycle, "-", len(r) - cycle)

    else:
        return len(r)-cycle
    
def unitfr2(n, M):

    f = []
    r = []
    t = 1  

    for i in range(M):

        r.append(t)
        q = (10*t)//n
        f.append( q )
        t = 10*t - q*n
        
    #print(f)
    s = ""
    for i in f:
        s += str(i)
    s = "0," + s
    print(s)  
    
