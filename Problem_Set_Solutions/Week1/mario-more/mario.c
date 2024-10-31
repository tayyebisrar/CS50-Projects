#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Ask the user for the height of the pyramid, ensuring it is an integer more than 0.
    int n;
    do
    {
        n = get_int("Height: ");
    }
    while (n < 1);

    // left side of pyramid
    for (int i = 0; i < n; i++) // for each line
    {
        for (int j = 0; j < (n - i - 1); j++) // print n-i-1 spaces
        {
            printf(" ");
        }
        for (int k = 0; k < i + 1; k++) // print i+1 hashtags
        {
            printf("#");
        }
        printf("  ");
        for (int k = 0; k < i + 1; k++) // print i+1 hashtags
        {
            printf("#");
        }
        printf("\n");
    }
}
