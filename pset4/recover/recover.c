#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <string.h>
#include <stdint.h>


int main(int argc, char *argv[])
{
    
// define arguments
    unsigned char buffer[512];
    bool already_found_any_jpeg = false;
    int num_of_imgs = 0;
    char filename[8];
    FILE *img = NULL;
    FILE *card = NULL;

// If there is no or more than one command-line arguments OK
    if (argc != 2)
    {
        printf("missing command-line argument\n");
        return 1;
    }

// Open memory card 
    card = fopen(argv[1], "r");

// If the forensic image cannot be opened for reading
    if (card == NULL)
    {
        printf("Could not open %s.\n", argv[1]);
        return 1;
    }

// Repeat until end of card
    while (fread(buffer, 512, 1, card) != 0)
    {
        // if buffer is a JPG
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // if start of very first JPG
            if (already_found_any_jpeg == false)
            {
                sprintf(filename, "%03i.jpg", num_of_imgs);     
                printf("%s\n", filename);

                img = fopen(filename, "w");                     
                printf("first image %s is opened\n", filename);
                if (img == NULL)
                {
                    printf("Could not open %s.\n", argv[1]);
                    return 1;
                }
                
                fwrite(&buffer, 512, 1, img);
                already_found_any_jpeg = true;
            }
            
            // if start of next JPG
            else if (already_found_any_jpeg == true)
            {
                // close previous img
                fclose(img);
                
                num_of_imgs++;
                sprintf(filename, "%03i.jpg", num_of_imgs);     
                printf("%s\n", filename);

                img = fopen(filename, "w");                     
                printf("image %s is opened\n", filename);
                if (img == NULL)
                {
                    printf("Could not open %s.\n", argv[1]);
                    return 1;
                }
                
                fwrite(&buffer, 512, 1, img);
            }
        }
        else // Write 512 bytes to the last image, until a new JPEG is found
        {
            if (already_found_any_jpeg == true)
            {
                fwrite(&buffer, 512, 1, img);
            }
            else
            {
                
            }
        }
    }
}
