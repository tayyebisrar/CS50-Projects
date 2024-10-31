from cs50 import get_string


def main():
    text = get_string("Text: ")  # get text
    ind = cl_index(text)  # find index
    if ind < 1:
        print("Before Grade 1")  # pre grade 1
    elif ind >= 16:
        print("Grade 16+")  # more than grade 16
    else:
        print(f"Grade {ind}")  # print grade


def cl_index(text):
    lettercount = 0
    wordcount = 1
    sentencecount = 0
    for i in range(len(text)):  # for each letter in text
        l = text[i]
        if (l.isalpha()):  # if it's a letter
            lettercount += 1
        elif l == ' ':  # if it's a space
            wordcount += 1
        elif l == '.' or l == '?' or l == '!':  # if it's punctuation
            sentencecount += 1
    index = 0.0588 * lp100w(lettercount, wordcount) - 0.296 * \
        sp100w(sentencecount, wordcount) - 15.8  # find index
    return round(index)  # return rounded index


def lp100w(l, w):
    try:
        return ((l/w) * 100)  # letters per 100 words
    except:
        return 0


def sp100w(s, w):
    try:
        return ((s/w) * 100)  # sentences per 100 words
    except:
        return 0


main()  # call main
