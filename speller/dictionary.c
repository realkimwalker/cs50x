// Implements a dictionary's functionality
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table (may want to increase this number)
const unsigned int N = 26;

// Hash table
node *table[N];

// Declaring variables
unsigned int numwords;
unsigned int hashtag;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Find the hash value by calling hash
    hashtag = hash(word);

    // Create node ptr cursor to head of linked list
    node *cursor = table[hashtag];

    // Go though linked list comparing for word match
    while (cursor != NULL)
    {
        if (strcasecmp((word), cursor->word) == 0)
        {
            return true;
        }
        else
        {
            cursor = cursor->next;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    // Staying with unsigned int
    unsigned int total = 0;

    for (int i = 0; i < strlen(word); i++)
    {
        // Total all ascii values of each char in word; mod N (26) for remainder placement
        total += tolower(word[i]);
    }

    return total % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open the dictionary file to store contents to a hash table by hash function
    FILE *source = fopen(dictionary, "r");

    // Check to see if string was read correctly
    if (source == NULL)
    {
        return false;
    }

    // Read each word in the file into the hash array node n
    char word[LENGTH + 1];

    // Scan in words from dictionary until EOF
    while (fscanf(source, "%s", word) != EOF)
    {
        // Allocate memory for node
        node *n = malloc(sizeof(node));

        // Add each word to the hash table, create new node
        if (n == NULL)
        {
            return false;
            free(n);
        }

        // Copy dictionary word into node
        else
        {
            strcpy(n->word, word);
            hashtag = hash(word);
            n->next = table[hashtag];
            table[hashtag] = n;

            // Added counter for size function
            numwords++;
        }
    }

    // Close the dictionary file
    fclose(source);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    if (numwords > 0)
    {
        return numwords;
    }
    else
    {
        return 0;
    }
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO Iterate through all hash buckets
    for (int i = 0; i < N; i++)
    {
        // Start at the beginning of linked list
        node *cursor = table[i];

        // If not at end of linked list, free memory
        while (cursor != NULL)
        {
            // create temp
            node *temp = cursor;

            // Move cursor to next node
            cursor = cursor->next;

            // Free temp
            free(temp);
        }

        // If we reach the end of the linked list, return true for success!
        if (cursor == NULL)
        {
            return true;
        }
    }
    return false;
}
