/**
*intials.c
*
*Dylan P. Oldfield
*dylan.oldfield@yahoo.com
*
*prompts user to input their name and 
*outputs initals in allcaps without spaces
*
*/

#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(void)
{
    string name = GetString();
    // prints the first character in the string 
    printf("%c",toupper(name[0]) );
    // used to iterate through string
    for( int i = 0; i < strlen(name); i++)
    {   
        // checks to see if the character is a space then prints the next
        if ( name[i] == ' ' )
        {
            printf("%c", toupper(name[i + 1]));
        }
    }
    printf("\n");
   
    
}

