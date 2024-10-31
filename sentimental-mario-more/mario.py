from cs50 import get_int  # import library to use get_int


def main():
    while True:
        height = get_int("Height: ")  # ask for height
        if height >= 1 and height <= 8:  # ensure height is between 1 and 8 inclusive
            break
    pyramid(height)  # print the pyramid to user's height


def pyramid(n):
    for i in range(1, n+1):  # from 1 to height inclusive
        print(" "*(n-i), end="")  # print n-i spaces
        print("#"*i, end="")  # print i hashtags
        print("  ", end="")  # print 2 spaces
        print("#"*(i))  # print i more hashtags


main()  # call main
