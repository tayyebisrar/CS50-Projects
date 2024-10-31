#include <cs50.h>
#include <stdio.h>

int luhnalgorithm(long num);
int findlength(long num);
long poweroften(int power);
int digit(long num, int digitnum);

int main(void)
{
    long cardnumber = get_long("Number: ");
    int cardlength = findlength(cardnumber);
    int f2digits = (int) (cardnumber / poweroften(cardlength - 2));

    if (luhnalgorithm(cardnumber) % 10 == 0) // check if algorithm returns 0
    {
        if (cardlength == 16) // VISA or Mastercard
        {
            if (digit(cardnumber, cardlength - 1) == 4) // If first digit is 4
            {
                printf("VISA\n");
            }
            else if (f2digits == 51 || f2digits == 52 || f2digits == 53 || f2digits == 54 ||
                     f2digits == 55)
            {
                printf("MASTERCARD\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        else if ((cardlength == 15) && (f2digits == 37 || f2digits == 34))
        {
            printf("AMEX\n");
        }
        else if ((cardlength == 13) && digit(cardnumber, cardlength - 1) == 4)
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}

long poweroften(int power)
{
    long ans = 1;
    for (int i = 0; i < power; i++)
    {
        ans = ans * 10;
    }
    return ans;
}

int digit(long num, int digitnum) // starts from 0, i.e. first digit is index 0.
{
    return num % poweroften(digitnum + 1) / poweroften(digitnum);
}

int findlength(long x)
{
    int len = 0;
    long num = x;
    do
    {
        num = num / 10;
        len++;
    }
    while (num > 0);
    return len;
}

int luhnalgorithm(long num)
{
    int total = 0;
    int numlen = findlength(num);
    for (int i = 1; i < numlen; i += 2) // for every other digit, starting from second-to-last
    {
        int curr = 2 * digit(num, i);
    t    for (int j = 0; j < findlength(curr);
             j++) // for each digit from within each of those digits (1 or 2)
        {
            total += digit(curr, j); // add it to the total
        }
    }
    for (int i = 0; i < numlen; i += 2) // for the remaining digits, starting from the last
    {
        total += digit(num, i);
    }
    return total;
}
