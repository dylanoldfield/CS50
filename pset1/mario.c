/**
*mario.c
*
*Dylan P. Oldfield
*dylan.oldfield@yahoo.com
*
*creates a tower of blocks of user specified length between 0-23
*like in mario. 
*
* 
*/


#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height= -1; 
    // checks to see if inputted integer is valid 0-23
    while(height > 23 || height < 0)
    {
        printf("height: ");
        height = GetInt();
    }
    // checks to see if it needs to print anything
    if (height == 0)
    {
        return 0;
    }
    // iterates for each row 
    for(int count = 0; count < height; count++)
    {
        // prints height-2 spaces for each row
        for(int space = count; space <= height - 2; space++)
        {
            printf(" ");
        }
        // prints n+1 blocks for each row greater than zero
        for(int block = 0; block <= count + 1; block++)
        {
            printf("#");
        }
        printf("\n");
    
  }
}
