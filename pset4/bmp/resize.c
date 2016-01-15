/**
 * copy.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Copies a BMP piece by piece, just because.
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./copy infile outfile\n");
        return 1;
    }

    // remember filenames
    int factor = atoi(argv[1]);
    char* infile = argv[2];
    char* outfile = argv[3];

    if (factor < 1 || factor > 100 )
    {
        printf("Please input a factor of between 1 and 100\n");
        return 2;
    } 
    
    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 3;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 4;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 5;
    }
     
    
    // determine padding for scanlines
    int origpadding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int padding =  (4 - (bi.biWidth * factor * sizeof(RGBTRIPLE)) % 4) % 4;

    // create resized BITMAPINFOHEADER rbi (resized bi)
    BITMAPINFOHEADER rbi;
    rbi.biSize = bi.biSize; 
    rbi.biWidth = bi.biWidth * factor; 
    rbi.biHeight = bi.biHeight * factor; 
    rbi.biPlanes = bi.biPlanes; 
    rbi.biBitCount = bi.biBitCount; 
    rbi.biCompression = bi.biCompression; 
    rbi.biSizeImage = rbi.biWidth * abs(rbi.biHeight) * sizeof(RGBTRIPLE) + padding * abs(rbi.biHeight); 
    rbi.biXPelsPerMeter = bi.biXPelsPerMeter; 
    rbi.biYPelsPerMeter = bi.biYPelsPerMeter; 
    rbi.biClrUsed = bi.biClrUsed; 
    rbi.biClrImportant = bi.biClrImportant;
    
    // create resized BITMAPFILEHEADER rbf (resized bf)
    BITMAPFILEHEADER rbf;
    
    rbf.bfType = bf.bfType; 
    rbf.bfSize = rbi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER); 
    rbf.bfReserved1 = bf.bfReserved1; 
    rbf.bfReserved2 = bf.bfReserved2; 
    rbf.bfOffBits = bf.bfOffBits; 
    
    
    // write outfile's BITMAPFILEHEADER
    fwrite(&rbf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&rbi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // creates an array to store factor number of the same pixel
    RGBTRIPLE resize[rbi.biWidth];
    
    // iterate over infile's scanlines
    
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        // initialise array counter for each line
        int count = 0;
        
        // iterate over pixels in scanline
        for (int j = 0; j < bi.biWidth; j++)
        {   
            
            // temporary storage
            RGBTRIPLE triple;
            
            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
            
            // put into array 
            for (int i = 0; i < factor; i++)
            {
                resize[count] = triple; 
                count++;
              
            }
        
        }

        // skip over padding, if any
        fseek(inptr, origpadding, SEEK_CUR);
        
        // repeat for factor rows
        for (int l = 0; l < factor; l++)
        {
            // write RGB triple to outfile
            fwrite(&resize, sizeof(RGBTRIPLE), rbi.biWidth, outptr);

            // then add padding scaled for new file
            for (int k = 0; k < padding; k++)
            {
                fputc(0x00, outptr);
            }
        }
        
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
