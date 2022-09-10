# Problem no. 56: Powerful digit sum
###### SOLVED ######
from functools import reduce
import matplotlib.pyplot as plt


def power_digit_sum(a: int, b: int) -> int:
    return reduce(lambda x, y: x+y, map(int, list(str(a ** b))))


if __name__ == '__main__':
    print(power_digit_sum(5, 2))
    print(power_digit_sum(5, 3))
    print(power_digit_sum(5, 4))
    print(power_digit_sum(11, 23))
    max_digital_sum = 0
    digital_sums = []
    range_low = 60
    for i in range(99, range_low, -1):
        for j in range(99, 90, -1):
            digital_sum = power_digit_sum(i, j)
            print(f"{i} ^ {j} --> {digital_sum}")
            digital_sums.append(digital_sum)
            # if digital_sum > max_digital_sum:
            #     max_digital_sum = digital_sum
    print("max digital sum:", max(digital_sums))
    plt.plot(digital_sums, 'r.')
    plt.show()
