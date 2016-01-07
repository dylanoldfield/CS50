/**
*greedy.c
*
*Dylan P. Oldfield
*dylan.oldfield@yahoo.com
*
*this program calculates the smallest number of coins used
*to give a certain amount of change
*
*/

#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    float change = -1.0; 
    int coins = 0;
    // checks to see if change is valid
    while (change < 0)
    {
        printf("O hai! How much change is owed?\n");
        change = GetFloat();
    }
    
    if (change == 0.0)
    {
        printf("0");
    }
    /* 
        converts float to int by multiplying by 100
        fixes any inaccuracies by rounding
    */    
    int changei = round( change * 100 );
    
    /* 
        checks range of change and divides int to find number 
        of coins needed. Then uses modular to determine the 
        remainder to pass onto the next check.
    */   
 
    if (changei > 24)
    {
        coins = coins + ( changei / 25 );
        changei = changei % 25;
    }
    
    if (changei > 9)
    {
        coins = coins + ( changei / 10 );
        changei = changei % 10;
    }
    
    if (changei > 4)
    {
        coins = coins + ( changei / 5 );
        changei = changei % 5;
    }
    
    coins = coins + changei;
    
    printf("%d\n", coins);
       
    
}
