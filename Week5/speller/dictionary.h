// Declares a dictionary's functionality

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stdbool.h>

// Maximum length for a word
// (e.g., pneumonoultramicroscopicsilicovolcanoconiosis)
#define LENGTH 45

// Prototypes
bool check(const char *word);
void delete(int position);
unsigned int hash(const char *word);
bool load(const char *dictionary);
bool pushToFront(int hashValue, const char *word);
unsigned int size(void);
bool unload(void);

#endif // DICTIONARY_H
