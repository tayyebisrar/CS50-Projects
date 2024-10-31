// Implements a dictionary's functionality

#include "dictionary.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 676;
int words = 0;
// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    unsigned int hashval = hash(word); // find hash value to choose which array index to search from
    for (node *ptr = table[hashval]; ptr != NULL;
         ptr = ptr->next) // go through that index's linked list
    {
        if (strcasecmp(ptr->word, word) == 0) // if the value matches
        {
            return true; // word is there
        }
    }
    return false; // if it wasn't found it wasn't there
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // Find first letter
    int l1 = toupper(word[0]) - 'A';
    int l2;
    // Find second letter
    if (word[1] != '\0')
    {
        l2 = toupper(word[1]) - 'A';
    }
    else
    {
        l2 = 1;
    }
    return (26 * (l1) + (l2));
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }
    FILE *dict = fopen(dictionary, "r");
    if (dict == NULL)
    {
        return false;
    }
    char word[LENGTH + 1];
    // for each word in dictionary...
    while (fscanf(dict, "%s", word) != -1)
    {
        node *curr_node = malloc(sizeof(node)); // new node
        if (curr_node == NULL)                  // if it can't be allocated memory
        {
            return false; // return false
        }
        strcpy(curr_node->word, word);   // copy the value into new node
        unsigned int hashv = hash(word); // find the hash
        // go to that hash location in array and prepend word
        curr_node->next = table[hashv];
        // reassign start of the linked list
        table[hashv] = curr_node;
        // curr_node->next = table[hashv];
        // table[hashv] = curr_node;
        words++;
    }
    fclose(dict);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return words;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    if (words == 0)
    {
        return false;
    }
    for (int i = 0; i < N; i++)
    {
        while (table[i] != NULL)
        {
            node *n = table[i];
            table[i] = table[i]->next;
            free(n);
            words--;
        }
    }
    return true;
}
