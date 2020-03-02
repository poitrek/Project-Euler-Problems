# Problem no. 17: Number letter counts
###### SOLVED ######


def number_to_words(n):
    if n == 1000:
        return 'one thousand'

    hundreds = n // 100
    dozens = (n % 100) // 10
    units = n % 10

    string = ''
    if hundreds > 0:
        string += unit_word(hundreds) + ' hundred'
        if dozens + units > 0:
            string += ' and '

    if dozens > 1:
        string += dozen_word(dozens)
        if units > 0:
            string += '-' + unit_word(units)
    elif dozens == 1:
        string += teen_word(units)
    else:
        if units > 0:
            string += unit_word(units)
    return string



def unit_word(n):
    word_dict = {
        0: '',
        1: 'one', 2: 'two', 3: 'three', 4: 'four',
        5: 'five', 6: 'six', 7: 'seven', 8: 'eight',
        9: 'nine'
    }
    return word_dict[n]


def dozen_word(n):
    word_dict = {
        1: 'ten',
        2: 'twenty', 3: 'thirty', 4: 'forty', 5: 'fifty',
        6: 'sixty', 7: 'seventy', 8: 'eighty', 9: 'ninety'
    }
    return word_dict[n]


def teen_word(n):
    word_dict = {
        0: 'ten', 1: 'eleven', 2: 'twelve', 3: 'thirteen',
        4: 'fourteen', 5: 'fifteen', 6: 'sixteen', 7: 'seventeen',
        8: 'eighteen', 9: 'nineteen'
    }
    return word_dict[n]


def letter_count(n):
    n_words = number_to_words(n)
    n_words = n_words.replace(' ', '')
    n_words = n_words.replace('-', '')
    return len(n_words)


print('356:', number_to_words(356))
print('701', number_to_words(701))
print('88:', number_to_words(88))
print('217:', number_to_words(217))
print('18:', number_to_words(18))
print('200:', number_to_words(200))
print('50:', number_to_words(50))
print()
print('336:', letter_count(336))
print('103:', letter_count(103))
print('342:', letter_count(342))
print('115:', letter_count(115))
print()
# for i in range(1, 40):
#     print(number_to_words(i), ':', letter_count(i))

total_letters = 0
for i in range(1, 1001):
    total_letters += letter_count(i)
    if i % 100 == 0:
        print(i, ':', total_letters, 'letters')

print('Number of letters under 1000:', total_letters)
