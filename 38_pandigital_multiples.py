# Problem no. 38: Pandigital multiples
###### SOLVED ######

# key = 9487...9123
# 9-pandigital number: concat(key*1, key*2)

bottom = 9123
top = 9487
digits = set('123456789')
for key in range(top, bottom-1, -1):
    concat = str(key) + str(key * 2)
    if set(concat) == digits:
        print('Found pandigital:', concat)
        print('Key:', key)
        break
