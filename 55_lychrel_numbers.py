# Problem no. 55: Lychrel numbers
###### SOLVED ######
from tools.timer import Timer


def is_palindrome(n: int) -> bool:
    n = str(n)
    return n == n[::-1]


def is_lychrel_number(n: int, limit=50) -> bool:
    result = True
    for it in range(limit):
        n += int(str(n)[::-1])
        # print(n, end='  ')
        if is_palindrome(n):
            result = False
            break
    # print()
    return result


if __name__ == '__main__':
    lychrel_cnt = 0
    for n in range(10, 10000):
        # print(f"{n}: ", end='')
        if is_lychrel_number(n):
            print(f"lychrel number: {n}")
            lychrel_cnt += 1
    print(lychrel_cnt)