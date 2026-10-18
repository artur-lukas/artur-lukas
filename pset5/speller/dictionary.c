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

// TODO: Choose number of buckets in hash table
const unsigned int N = 50;

// Hash table
node *table[N];
int size_dictionary = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    node *current_node = table[hash(word)];
    while (current_node != NULL)
    {
        if (strcasecmp(current_node->word, word) == 0)
            return true;
        else
            current_node = current_node->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    // return toupper(word[0]) - 'A';
    long sum = 0;
    for (int i = 0; i != '\0'; i++)
    {
        sum += word[i];
    }
    return sum % 50;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    // Open the dictionary file
    FILE *source = fopen(dictionary, "r");
    if (source == NULL)
        return false;
    // Read each word in the file
    char new_word[LENGTH + 1];
    while (fscanf(source, "%45s", new_word) != EOF)
    {
        // Add each word to the hash table
        struct node *new_node = malloc(sizeof(struct node));
        if (new_node == NULL)
            return false;
        strcpy(new_node->word, new_word);
        int new_hash = hash(new_word);
        // next pointer
        new_node->next = table[new_hash];
        table[new_hash] = new_node;
        size_dictionary++;
    }
    // Close the dictionary file
    fclose(source);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return size_dictionary;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        struct node *cursor = table[i];
        struct node *tmp = NULL;
        while (cursor != NULL)
        {
            tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }
    }

    return true;
}
