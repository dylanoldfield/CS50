/**
*vingenere.c
*
*Dylan P Oldfield
*dylan.oldfield@yahoo.com
*
*This program encrypts a string using a vigenere cipher. 
*This works by using a keyword as a key and transposes
*letters in the string by 0-25 dependent on the value 
*of the letters in the key word. 
*
*/

#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
     // checks to see if correct # of arguments entered
    if ( argc != 2 )
    {
        printf("Zero arguments or more than 1 arugment present\n");
        return 1; 
    }
    
    string key = argv[1];
    // checks to see if key is all alphabetic characters
    for (int i = 0; i < strlen(key); i++)
    {
        if (!isalpha(key[i]))
        {
            printf("Invalid key");
            return 1;
        } 
    }
    
    string phrase = GetString();
    int length = strlen(phrase);
    
    // goes through string checking to see if characters are alphabetical
    for(int i = 0, place = 0; i < length; i++)
    {
       // wrap-around for lower-case characters
       // mod the key length to allow it to repeat if too short
        if ( islower(phrase[i]) )
        {
            // turns character into a integer 
            int transpose = tolower(key[place % strlen(key)] % 97);
            // wraps around for lower case characters
            printf("%c",(97 + ( ( ( phrase[i] + transpose ) % 97) % 26) ) );
            place++;
        }
       // wrap-around for upper-case characters
        else if ( isupper( phrase[i] ) )
        {
            // turns character into a integer 
            int transpose = toupper( key[place % strlen(key)] % 65);
             
             // wraps around for upper case characters
            printf("%c",(65 + ( ( ( phrase[i] + transpose ) % 65) % 26) ) );
            place++;
        }         
        // keeps any non-alphabetical characters the same
        else
        {
            printf("%c",phrase[i]);
        }    
    }
    printf("\n");
    return 0;
    
    
}
