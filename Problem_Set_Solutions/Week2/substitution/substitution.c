#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

string getciphertext(string text, char key_list[]);
int checkkey(string cipherkey);

int main(int argc, string argv[])
{
    if (argc != 2) // if the number of arguments given is wrong
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    if (strlen(argv[1]) != 26) // if the length of the key is wrong
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    else if (checkkey(argv[1]) == 1) // if the key is not valid
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    char keylist[26];
    for (int i = 0; i < 26; i++) // create an array from the key
    {
        if (((argv[1][i]) >= 'a') && ((argv[1][i]) <= 'z'))
        {
            keylist[i] = (char) (argv[1][i] - 32);
        }
        else
        {
            keylist[i] = argv[1][i]; // make sure the entire thing is uppercase
        }
    }
    string plaintext = get_string("plaintext: ");
    string ciphertext = getciphertext(plaintext, keylist); // convert the plain to cipher text
    printf("ciphertext: %s\n", ciphertext);
    return 0;
}

string getciphertext(string text, char key_list[])
{
    for (int i = 0, len = strlen(text); i < len; i++) // for each letter in string
    {
        int curr_letter = text[i];
        if (isalpha(curr_letter)) // if letter of the alphabet
        {
            if (curr_letter >= 'A' &&
                curr_letter <= 'Z') // if letter is uppercase, between values 65 to 90
            {
                text[i] =
                    key_list[(curr_letter -
                              65)]; // change the initial letter to the key's replacement, minusing
                                    // 65 to ensure the index remains between 0 and 26, because 65
                                    // is A. This works because the cipher key is in the alphabet's
                                    // order, so when 65 is minused you're taken to the cipher's
                                    // replacement value of that character, e.g. if the list was the
                                    // alphabet shifted +1, B would be in the 0th index so if you
                                    // typed ABC, you get A - 65 = 0, and in the 0th index is B.
            }
            else
            {
                text[i] = (int) (key_list[(curr_letter - 97)]) +
                          32; // change to replacement, minusing 97 (lowercase a) then adding 32 at
                              // the end to preserve it as lowercase afterwards.
            }
        }
    }
    return text;
}

int checkkey(string cipherkey)
{
    for (int i = 0, len = strlen(cipherkey); i < len; i++) // for each letter in key
    {
        char curr_letter = cipherkey[i];
        if (((curr_letter >= 'A' && curr_letter <= 'Z') ||
             (curr_letter >= 'a' && curr_letter <= 'z')) == false) // make sure they're all letters
        {
            return 1;
        }
        for (int j = i + 1; j < 26; j++)
        {
            if (cipherkey[i] == cipherkey[j]) // make sure there's no duplicates
            {
                return 1;
            }
        }
    }
    return 0;
}
