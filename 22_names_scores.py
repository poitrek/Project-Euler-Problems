# Problem no. 22: Names scores
###### SOLVED ######

from requests import get

# Get file with names
response = get('https://projecteuler.net/project/resources/p022_names.txt')

# Get response content and decode to string
text = response.content.decode()

# Remove parentheses
text = text.replace('"', '')

# Make list of names
names = text.split(',')

# Sort names
names.sort()

alphabet = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ'

# Weight letters with a dictionary
alpha_dict = dict()

for i in range(len(alphabet)):
    alpha_dict[alphabet[i]] = i + 1

# Calculates word score by its letters' weights
def word_score(word):
    score = 0
    for ch in word:
        score += alpha_dict[ch]
    return score


total = 0

for i in range(len(names)):
    total += (i+1) * word_score(names[i])

print('Total score of sorted names:', total)
