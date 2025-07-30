''' 
#step 1: split the sample text in the string and display each word on new line
#step 2: look for duplicate words in the string, print the number of times 
# each word is used in the string

sample = "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Nibh venenatis cras sed felis eget velit aliquet sagittis id. Posuere urna nec tincidunt praesent semper feugiat. Tortor posuere ac ut consequat semper viverra nam libero. Posuere ac ut consequat semper 
viverra. Urna neque viverra justo nec ultrices dui sapien eget mi."
'''

sample = "Lorem ipsum dolor sit amet consectetur adipiscing elit sed do eiusmod tempor incididunt ut labore et dolore magna aliqua Nibh venenatis cras sed felis eget velit aliquet sagittis id Posuere urna nec tincidunt praesent semper feugiat Tortor posuere ac ut consequat semper viverra nam libero Posuere ac ut consequat semper viverra Urna neque viverra justo nec ultrices dui sapien eget mi"


def word_split(sample):
    split = sample.split()

    for x in split:
        print(x)

def word_frequency(sample):
# clean input 
    cleaned_words = sample.lower().split()
# count each freq
#  holds words and freq of each word -
    frequency_word = {}
    for word in cleaned_words:
        if word in frequency_word:
            frequency_word[word] += 1
        else:
            frequency_word[word] = 1
# print 
    for word in frequency_word:
        if frequency_word[word] > 1:
            print(f"{word}: {frequency_word[word]}")
#word_split(sample)
word_frequency(sample)

