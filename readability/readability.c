#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

//define all functions
int cl_index(string text);
float lettersper100words(int letters, int words);
float sentencesper100words(int sentences, int words);

int main(int argc, string argv[])
{
    string text = get_string("Text: "); // get the string and find out the index score
    int index_score = cl_index(text);
    if (index_score < 1) // if the score was less than 1 or more than/equal to 16 then display as such
    {
        printf("Before Grade 1\n");
    }
    else if (index_score >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index_score); // otherwise just display as it is.
    }
}

int cl_index(string text)
{
    int lettercount = 0, wordcount = 1, sentencecount = 0;
    for (int i = 0, len = strlen(text); i < len; i++) // for each character in the text
    {
        char l = text[i];
        if (isalpha(l)) // if it's a letter
        {
            lettercount++;
        }
        else if (l == ' ') // a space
        {
            wordcount++;
        }
        else if (l == '.' || l == '?' || l == '!') // punctuation that denotes a new sentence
        {
            sentencecount++;
        }
    }

    float index = 0.0588 * lettersper100words(lettercount, wordcount) -
                  0.296 * sentencesper100words(sentencecount, wordcount) - 15.8; // find out the index score as a float
    index = round(index); // round it to the nearest integer
    return (int) index;
}

float lettersper100words(int letters, int words)
{
    float l = (float) letters;
    float w = (float) words;
    return (l / w) * 100.0; // letters per 100 words
}

float sentencesper100words(int sentences, int words)
{
    float s = (float) sentences;
    float w = (float) words;
    return (s / w) * 100.0; // sentences per 100 words
}
