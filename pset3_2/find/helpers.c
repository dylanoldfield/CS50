/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 * 
 * Dylan P. Oldfield
 * dylan.oldfield@yahoo.com
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    if ( n < 0 )
    {
        return false;
    }
   //binary search 
   int low = 0;
   int high = n - 1;
   
   while ( low <= high )
   {
        int mid = low + high / 2;
        
        if (value == values[mid])
        {
            return true;
        }
        else if (value < values[mid])
        {
            high = mid - 1;
        }
        else
        {
            low = mid + 1;
        }
        
   }
  
    return false;  
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{

    //Bubble Sort 
    
    for (int i = 0; i < n; i++)
    {
        //Doesn't check already sorted values a.k.a. end values
        for (int j = 0; j < n - i; j++)
        {
            if (values[j] > values [j + 1] )
            {
                int holder = values[j];
                values[j] = values [j + 1];
                values[j + 1] = holder;
            }
        }
        
    }
    return;
}