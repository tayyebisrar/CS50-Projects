#include <cs50.h>
#include <stdio.h>
#include <string.h>

int scrabblescore(string answer);
string lowercase(string str);

int main(int argc, string argv[])
{
    string p1ans = get_string("Player 1: ");
    string p2ans = get_string("Player 2: ");

    printf("Lowercase: %s", lowercase(p1ans));

    if (scrabblescore(p1ans) > scrabblescore(p2ans))
    {
        printf("Player 1 Wins!\n");
    }
    else if (scrabblescore(p1ans) < scrabblescore(p2ans))
    {
        printf("Player 2 Wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
}

int scrabblescore(string answer)
{
    int score = 0;
    answer = lowercase(answer);
    for (int i = 0, len = strlen(answer); i < len; i++) // for each letter in string
    {
        char l = answer[i];
        if (l == 'b' || l == 'c' || l == 'm' || l == 'p') // add correct score
        {
            score += 3;
        }
        else if (l == 'd' || l == 'g')
        {
            score += 2;
        }
        else if (l == 'f' || l == 'h' || l == 'v' || l == 'w' || l == 'y')
        {
            score += 4;
        }
        else if (l == 'k')
        {
            score += 5;
        }
        else if (l == 'j' || l == 'x')
        {
            score += 8;
        }
        else if (l == 'q' || l == 'z')
        {
            score += 10;
        }
        else
        {
            if (l >= 'a' && l <= 'z') // letters with score 1 are the leftovers
            {
                score += 1;
            }
        }
    }
    return score;
}

string lowercase(string str)
{
    string new_str = str;
    for (int i = 0, len = strlen(str); i < len; i++) // For each letter in the string
    {
        // char current_letter_val = str[i];
        // lowercase values are from a-z 97-122 and caps are 32 less
        if (str[i] >= 'A' && str[i] <= 'Z')
        {
            new_str[i] += ('a' - 'A');
        }
    }
    return new_str;
}
