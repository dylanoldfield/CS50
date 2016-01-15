/**
*caeser.c
*
*Dylan P Oldfield
*dylan.oldfield@yahoo.com
*
*This programs encrypts input  data based on an integer key k
*provided by the user. It utilises caeser cipher which transposes
*letter c by k overall with 26 being the limit
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
    // converts string argument to int 
    int key = atoi(argv[1]);
    
    // checks to see if key is valid else yells and exits with error 1
    if ( key < 0 )
    {
        printf("Please input valid integer key\n");
        return 1; 
    }
    
    // gets phrase to encrypt from user
    string phrase = GetString();
    int length = strlen(phrase);
    
    // goes through string checking to see if characters are alphabetical
    for(int i=0; i < length; i++)
    {
       // wrap-around for lower-case characters
        if ( islower(phrase[i]) )
        {
            printf("%c",(97 + ((phrase[i] + key) % 97) % 26));
        }
       // wrap-around for upper-case characters
        else if ( isupper(phrase[i]) )
        {
            printf("%c",(65 + ( ( phrase[i] + key ) % 65) % 26));
        }         
        else
        {
            printf("%c",phrase[i]);
        }     
       
    }
    
    printf("\n");
    return 0;
    
}

