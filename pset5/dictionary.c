/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/

#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#include "dictionary.h"


node *root;

int wordCount = 0;


/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    if (word == NULL)
    {
        printf("No word given \n");
        return false;
    }
    // sets current node to root
    node *curNode = root;
    char curWord = word[0];
   
    // checks if dictionary is loaded
    if (wordCount == 0)
    {
        printf("No dictionary loaded\n");
        return false;
    }
    
    
    // iterates through the word setting the characters to lower case
    for(int i = 0; word[i] != '\0'; i++)
    {
        curWord = tolower(word[i]);
        // checks if it is alphabetic
        if ( isalpha(curWord))
        {
            // see if current is not present
            if ( curNode->letter[curWord - 'a'] != NULL)
            {
                curNode = curNode->letter[curWord - 'a'];
            }
            // else if present
            else 
            {
                return false;
            }
        }
        // checks to see if it is an apostrophe
        else if ( curWord == 39)
        {
            // see if it's not present
            if ( curNode->letter[26] != NULL)
            {
                curNode = curNode->letter[26];  
            }
            // moves to next letter
            else 
            {
                 return false;
            }  
        }
        // else wouldn't be in dictionary anyway, see load
        else
        {
            return false;
        }       
    }
    
    // checks to see if it forms a word
    if ( curNode->word == true )
    {
        return true;
    }
    // if if doesn't return false
    else
    {
        return false;
    }
    
    
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 * Uses Trie data structure
 */
bool load(const char* dictionary)
{
    // declares root node & current node
    root = malloc(sizeof(node));
    node *curNode = root;
    
    // reads dictionary in as a file
    FILE *dic = fopen(dictionary,"r");
    
    // checks if dictionary is valid
    if (dic == NULL)
    {
        return false;
    }
    
    // word count
    int words = 0;
    
    int numLetter = 0;
     
    
    // iterate through whole dictionary file
    for( int curLetter  =  fgetc(dic); curLetter != EOF; curLetter = fgetc(dic))
    {
        if (numLetter > LENGTH)
        {
            printf("Word is too long, needs to be less than %d\n",LENGTH);
            fclose(dic);
            return false;
        }
        // Adds letters to a word until end of line then starts new word
        if (isalpha(curLetter) || curLetter == 39)
        {
           // checks if letter is apostrophe
            if (curLetter == 39)
            {
                // checks to see if apostrophe spot is null if so assigns spot
                if (curNode->letter[26] == NULL)
                {
                    curNode->letter[26] = malloc(sizeof(node));
                }
               
                // preps for next letter
                curNode = curNode->letter[26];
                numLetter++;
                
            }
            // must be alphabetical
            else
            {
                // checks if corresponding letter spot is null if so assign spot
                if (curNode->letter[curLetter - 'a'] == NULL)
                {
                    curNode->letter[curLetter - 'a'] = malloc(sizeof(node));
                }
                
                // preps for next letter
                curNode = curNode->letter[curLetter - 'a'];
                numLetter++;
                
            } 
        }
        // checks for end of a word 
        else if ( curLetter == '\n' && numLetter > 0 )
        {
            // set bool to signify that point as a word
            curNode->word = true;
            // preps for next word
            curNode = root;
            numLetter = 0; 
            words++;
        }
        // else wait for a word to start
        else
        {
            curNode = root;
            numLetter = 0; 
        }
        
    }
    
    // closes dictionary file
    if (dic != NULL)
    {
        fclose(dic);
    }
    
    // sets word count for dictionary
    wordCount = words;
    
    // says YAY you didn't screw up
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return wordCount;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    if ( destroy(root) )
    {
        return true;
    }
    else
    {
        return false;
    } 
}

/**
 * recursively removes letters from each node (self-implemented)
 */
bool destroy(node *curNode)
{
    for (int i = 0; i < 27; i++)
    {
        if (curNode->letter[i] != NULL)
        {
            destroy( curNode->letter[i]);   
        }
    }
    
    free(curNode);
    return true;
}

