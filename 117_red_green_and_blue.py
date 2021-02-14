# Problem no. 117: Red, green and blue tiles
###### SOLVED ######


def count_coverage_ways(n):
    c0, c1, c2, c3 = 4, 2, 1, 1
    for i in range(5, n+1):
        c0, c1, c2, c3 = c1+c2*2+c3*3, c0, c1, c2+c3
    return c0+c1+c2+c3


def count_coverages_for_all(N):
    covrg = [0, 0, 1, 3, 8]
    c0, c1, c2, c3 = 4, 2, 1, 1
    for i in range(5, N+1):
        c0, c1, c2, c3 = c1+c2*2+c3*3, c0, c1, c2+c3
        covrg.append(c0+c1+c2+c3)
    return covrg


if __name__ == '__main__':
    # for i in range(4, 16):
    #     print(i, '<--', count_coverage_ways(i))
    print('Number of ways to cover 50-size row using red, green, and blue tiles:')
    print(count_coverage_ways(50))
    coverages = count_coverages_for_all(72)
    for i in range(4, len(coverages)-1):
        print(i, '', coverages[i], '', coverages[i+1]/coverages[i])
    print('200-size row:')
    print(count_coverage_ways(200))

