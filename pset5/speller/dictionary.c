// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <string.h>
#include <stdint.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 26; 

// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word) // check if the word is in dictionary or not
{
    // TODO
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word) // take a word and run hash funct on them, returning a number
{
    // TODO
    int sum = 0;
    return 0;
}

// Loading words from dictionary into structure like hash table
bool load(const char *dictionary)
{
    // define arguments
    FILE *file_dictionary;

    // Open dictionary file
    file_dictionary = fopen(dictionary, "r"); 

    if (dictionary == NULL)
    {
        printf("Could not open %s.\n", dictionary);
        return false;
    }

    // Read Strings from File
    char dictionary_word[LENGTH + 1];
    
    
    char ch; 
    while (fscanf(file_dictionary, "%s", dictionary_word) != EOF)
    {   printf("looping while\n");
        fscanf(file_dictionary, "%s", dictionary_word);
        printf("string: %s\n", dictionary_word);
        
        // Create a new node for each word
        node *new_node = malloc(sizeof(node));
        
        if (new_node == NULL)
        {
            printf("Return value is NULL \n");
            return false;
        }
        
        // Copy word into node
        strcpy(new_node->word, dictionary_word);     
        new_node->next = NULL;
        
        // Inserting that node into one of the linked lists in your hash table
        
    }
    
    //node *list = NULL;

    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void) // returning how many words are in your dictionary
{
    // TODO
    return 0;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void) //free up memory
{
    // TODO
    //free(n);
    return false;
}
