# Problem no. 66: Diophantine equation
###### NOT SOLVED ######
from math import sqrt, isqrt
from tools.timer import Timer


squares = []
squaresset = {}


def find_squares(square_limit: int):
    global squares, squaresset
    n = 1
    n2 = 1
    while n2 <= square_limit:
        squares.append(n2)
        n += 1
        n2 = n*n
    squaresset = set(squares)


def solve_diopheq(D: int, y_limit=10_000_000):
    """Finds the lowest x for which there exists y such that
    x^2 = D * y^2 + 1"""
    # global squares
    if is_square_1(D):
        raise ValueError("No solutions for D being a square")
    y = 1
    while True:
        # x2 = squares[y_i] * D + 1
        # if y % 1_000_000 == 0:
        #     print(f"y: {y}")
        x2 = y*y * D + 1
        x = sqrt(x2)
        if float(x).is_integer():
            x_int = int(x)
            if x_int * x_int == x2:
                return int(x), y
            # return isqrt(x2), y+1
        y += 1
        if y > y_limit:
            raise TimeoutError("y variable exceeded its upper limit")


def is_square_1(n):
    return float(sqrt(n)).is_integer()


def is_square_2(n):
    global squaresset
    return n in squaresset


'''
Results from test:
Method 2 (using set of squares) is 2.1 times faster than method 1
'''
def test_is_square_check(method, limit=100_000_000):
    Timer.start_measure()
    # Method 1
    if method == 2:
        find_squares(limit)
        Timer.print_time_elapsed()
        Timer.start_measure()
    for i in range(limit):
        if method == 1:
            is_square_1(i)
        elif method == 2:
            is_square_2(i)
    Timer.print_time_elapsed()


if __name__ == '__main__':
    # test_is_square_check(1)
    # find_squares(10_000_000**2)
    for D in range(2, 200):
        print(f"{D}: ", end='')
        try:
            x, y = solve_diopheq(D)
            print(f"{x}^2 = {D} * {y}^2 + 1   (x={x})")
        except ValueError:
            print("no solution")
        except TimeoutError as e:
            print(e)
    # print(solve_diopheq(61))
