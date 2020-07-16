# Problem no. 19: Counting Sundays
###### SOLVED ######

# 0 - Sunday, 6 - Saturday

# Day of week increase after every month
month = [3, 0, 3, 2, 3, 2, 3, 3, 2, 3, 2, 3]
# Same, but for the leap year
monthleap = [3, 1, 3, 2, 3, 2, 3, 3, 2, 3, 2, 3]
sundays = 0
# Starting day of week (Tuesday, 1 Jan 1901)
dayOfWeek = 2
for year in range(1901, 2001):
    # Common year
    if year % 4 != 0:
        for m in month:
            dayOfWeek = (dayOfWeek + m) % 7
            if dayOfWeek == 0:
                sundays += 1
    # Leap year
    else:
        for m in monthleap:
            dayOfWeek = (dayOfWeek + m) % 7
            if dayOfWeek == 0:
                sundays += 1

print('Number of sundays: {}'.format(sundays))
