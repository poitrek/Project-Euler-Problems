# Problem no. 42: Coded triangle numbers
###### SOLVED ######

from requests import get
import logging
logging.basicConfig(level=logging.INFO, format='%(asctime)s %(message)s', datefmt='%m/%d/%Y %I:%M:%S')


# Get file content
response = get('https://projecteuler.net/project/resources/p042_words.txt')
text = response.content.decode()
logging.info('File downloaded.\n')

# Remove parentheses
text = text.replace('"', '')
# Make list of words
words = text.split(',')

# Make alphabet dictionary
alphabet = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ'
alpha_dict = dict()
for i in range(len(alphabet)):
    alpha_dict[alphabet[i]] = i + 1

# Calculates word value by its letters' weights
def word_value(word):
    score = 0
    for ch in word:
        score += alpha_dict[ch]
    return score

# Define sufficient amount of triangle numbers
triangles = [1]
i, tr = 1, 1
while tr < 500:
    i += 1; tr += i
    triangles.append(tr)
triangles = set(triangles)

if __name__ == '__main__':

    print(triangles)
    counter = 0
    for w in words:
        if word_value(w) in triangles:
            counter += 1
            print(w, end=' ')
    print('\nWords with triangle value:', counter)

