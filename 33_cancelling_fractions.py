# Problem no. 33: Digit cancelling fractions
###### SOLVED ######


def gcd(x, y):
    while x != y:
        if x > y:
            x -= y
        else:
            y -= x
    return x


if __name__ == '__main__':
    # Find all the triplets A, B, C that satisfy the equality:
    # AB / BC = A / C  ( <=> (10A+B)/(10B+C) = A/C )
    triples = []
    for a in range(1, 10):
        for b in range(1, 10):
            c = 10 * a * b / (9*a + b)
            if a != b and float.is_integer(c) and c < 10:
                triples.append((a, b, int(c)))
    print('triples:', triples)
    # Compose the correct fractions
    fractions = []
    for a, b, c in triples:
        if a < c:
            fractions.append((a, c))
            # fractions.append((10 * a + b, 10 * b + c))
        else:
            fractions.append((c, a))
            # fractions.append((10 * b + c, 10 * a + b))
    # Find the denominator of the product of the fractions
    numer, denom = 1, 1
    for nr, dm in fractions:
        numer *= nr
        denom *= dm
    print("Fractions:", fractions)
    print(f"Fractions' product: {numer} / {denom}")
    nd_gcd = gcd(numer, denom)
    numer, denom = numer // nd_gcd, denom // nd_gcd
    print(f"Fractions' product simplified: {numer} / {denom}")
