# Problem no. 116: Red, green or blue tiles
###### SOLVED ######


def calc_red_tiles(n):
    r0, r1 = 1, 0
    for i in range(3, n+1):
        r0, r1 = r1 + 1, r0 + r1
    return r0 + r1


def calc_green_tiles(n):
    # Coverages with respectively 0, 1, and 2 (or more) trailing gaps
    # Starting for 3-sized row
    g0, g1, g2 = 1, 0, 0
    for i in range(4, n+1):
        g0, g1, g2 = g2+1, g0, g1+g2
    return g0+g1+g2


def calc_blue_tiles(n):
    b0, b1, b2, b3 = 1, 0, 0, 0
    for i in range(5, n+1):
        b0, b1, b2, b3 = b3+1, b0, b1, b2+b3
    return b0+b1+b2+b3


def red_tiles_coverages(N):
    r1, r2 = 1, 0
    covrg = [0, 0, 1]
    for i in range(3, N+1):
        r1, r2 = r2 + 1, r1 + r2
        covrg.append(r1+r2)
    return covrg


if __name__ == '__main__':
    # for i in range(4, 11):
    #     print(i, '->', calc_blue_tiles(i))
    # print('Number of coverage in red tiles of 50:', calc_red_tiles(50))
    # red_coverages = red_tiles_coverages(50)
    # print(red_coverages)
    # for i in range(3, 49):
    #     print(red_coverages[i+1] / red_coverages[i])
    cv_r = calc_red_tiles(50)
    cv_g = calc_green_tiles(50)
    cv_b = calc_blue_tiles(50)
    print('50-sized row:')
    print('Coverage with red tiles:', cv_r)
    print('Coverage with green tiles:', cv_g)
    print('Coverage with blue tiles:', cv_b)
    print('Total number of coverages:', cv_r + cv_g + cv_b)
