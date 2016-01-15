/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Dylan P Oldfield
 * dylan.oldfield@yahoo.com
 *
 * Recovers JPEGs from a forensic image.
 */

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    // open card file
    FILE* inpt = fopen("card.raw", "r");
    FILE* oupt = NULL;
   
    // check to see if file is valid
    if ( inpt == NULL)
    {
        printf("Could not open file, card.raw");
        return 1;
    }
   
    // create JPG file name and counter initialisations
    int jpgCount = 0;
    char jpgName[8];
   
    // create buffer --> use char for 1 byte
    unsigned char buffer[512];
   
    // Repeats until end of file
    while(fread(buffer, sizeof(buffer), 1, inpt) == 1)
    {
        // checks beginning of buffer for JPEG markers
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] == 0xe0 || buffer[3] == 0xe1))
        {
            // check if there is a current jpeg being read, then close it
            if (oupt != NULL)
            {
                fclose(oupt);
                oupt = NULL;
            }
           
           
            // create a new JPEG file
            sprintf(jpgName,"%03d.jpg",jpgCount);
           
            oupt = fopen(jpgName,"w");
           
            // checks if it doesn't read
            if ( oupt == NULL)
            {
                printf("Could not open file, card.raw");
                return 1;
            }
           
            // writes to the file
            fwrite(buffer, sizeof(buffer), 1,oupt);
           
            jpgCount++;  
           
       }
       
       else 
        {
            // checks to see if there is a current file then writes to it if 
            if (oupt != NULL)
            {
                fwrite(buffer, sizeof(buffer), 1,oupt);
            }
        }  
   }
   
   // checks if files are open and closes them if so
    if (inpt != NULL)
    {
        fclose(inpt);
    }
   
    if (oupt != NULL)
    {
        fclose(oupt);
    }
   
    return 0;
   
   
   
}
