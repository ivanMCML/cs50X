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

// Choose number of buckets in hash table
const unsigned int N = 143093;

// Hash table
node *table[N] = {NULL};

// Number of words in dictionary
unsigned int dictionarySize = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    node *temporary = NULL;
    // Find corresponding linked list
    temporary = table[hash(word)];

    // Go through linked list
    while (temporary != NULL)
    {
        // Check if words are same
        if (!strcasecmp(temporary->word, word))
            return true;
        temporary = temporary->next;
    }

    return false;
}

// Deletes linked list
void delete(int position)
{
    node *current;

    // Go through linked list
    while (table[position] != NULL)
    {
        // Delete first element
        current = table[position];
        table[position] = table[position]->next;
        free(current);
    }
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    int hashValue = 0;

    // Hash function that I already used before at Faculty of Electrical Engineering, Mechanical
    // Engineering and Naval Architecture in Split, Croatia
    while (*word != '\0')
    {
        hashValue = (hashValue << 5) + tolower(*word);
        word++;
    }
    return hashValue % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{

    // Open the dictionary file
    FILE *source = fopen(dictionary, "r");

    // Check if successfully opened
    if (source == NULL)
    {
        printf("ERROR! Failed to open a file!\n");
        return false;
    }

    char buffer[LENGTH + 1];

    // Read each word in the file
    while (fscanf(source, " %s", buffer) != EOF)
    {
        // Count words in the dictionary
        dictionarySize++;

        // Add each word to the hash table
        if (!pushToFront(hash(buffer), buffer))
        {
            fclose(source);
            return false;
        }
    }

    // Close dicitonary file
    fclose(source);

    return true;
}

// Push the word to the beginning of the linked list in hash table
bool pushToFront(int hashValue, const char *word)
{
    node *newWord = NULL;

    // Allocate memory for new word
    newWord = (node *) malloc(sizeof(node));
    if (newWord == NULL)
    {
        printf("ERROR! Failed to allocate memory!\n");
        return false;
    }

    // Add word to the beginning of the linked list
    strcpy(newWord->word, word);
    newWord->next = table[hashValue];
    table[hashValue] = newWord;

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return dictionarySize;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // Go through hash array
    for (int i = 0; i < N; i++)
        delete(i);

    return true;
}
