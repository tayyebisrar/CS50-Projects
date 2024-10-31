from cs50 import get_int  # import necessary library


def main():
    cardnumber = get_int("Number: ")  # get card number
    f2 = int(str(cardnumber)[:2])  # find first 2 letters
    cl = int(len(str(cardnumber)))  # find card length
    if (luhnalgorithm(cardnumber) % 10 == 0):
        if cl == 16:  # VISA or Mastercard
            if ((str(cardnumber)[0]) == '4'):
                print("VISA")
            elif (f2 >= 51 and f2 <= 55):  # number begins with 51-55
                print("MASTERCARD")
            else:
                print("INVALID")
        elif (cl == 15) and (f2 == 37 or f2 == 34):  # length 15 and begins with 37 or 34
            print("AMEX")
        elif ((cl == 13) and (int(str(cardnumber)[0]) == 4)):  # starts with 4
            print("VISA")
        else:
            print("INVALID")
    else:
        print("INVALID")


def digit(num, i):  # find digit from number
    num = str(num)
    dig = num[i]
    return int(dig)


def luhnalgorithm(num):
    total = 0
    numlen = int(len(str(num)))  # find length of number
    for i in range(numlen-2, -1, -2):  # from second-last digit
        curr = 2 * digit(num, i)
        for j in range(0, len(str(curr))):  # add all digits
            total += digit(curr, j)
    for a in range(numlen-1, -1, -2):  # add all remaining digits
        total += digit(num, a)
    return total  # return total


main()
