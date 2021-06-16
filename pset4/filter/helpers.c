#include "helpers.h"
#include <cs50.h>
#include <stdio.h>
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // for each row
    for (int i = 0; i < height; i++)
    {
        // for each column
        for (int j = 0; j < width; j++)
        {
            // calculate the average pixel value
            float average_not_rounded = ((float)image[i][j].rgbtRed + (float)image[i][j].rgbtGreen + (float)image[i][j].rgbtBlue) / 3;

            // round to integer
            int average = round(average_not_rounded);

            // set each color value to the average value
            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtBlue = average;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    float originalRed;
    float originalGreen;
    float originalBlue;

    float sepiaRed_not_rounded;
    float sepiaGreen_not_rounded;
    float sepiaBlue_not_rounded;

    int sepiaRed;
    int sepiaGreen;
    int sepiaBlue;

    // for each row
    for (int i = 0; i < height; i++)
    {
        // for each column
        for (int j = 0; j < width; j++)
        {
            // define
            originalRed = image[i][j].rgbtRed;          //printf ("originalRed = %f\n", originalRed);
            originalGreen = image[i][j].rgbtGreen;
            originalBlue = image[i][j].rgbtBlue;

            // convert to sepia by calculating new value
            sepiaRed_not_rounded = (float).393 * originalRed + (float).769 * originalGreen + (float).189 * originalBlue;
            sepiaGreen_not_rounded = (float).349 * originalRed + (float).686 * originalGreen + (float).168 * originalBlue;
            sepiaBlue_not_rounded = (float).272 * originalRed + (float).534 * originalGreen + (float).131 * originalBlue;

            // round to integer
            sepiaRed = round(sepiaRed_not_rounded);         //printf ("sepiaRed = %i\n", sepiaRed);
            sepiaGreen = round(sepiaGreen_not_rounded);       //printf ("sepiaGreen = %i\n", sepiaGreen);
            sepiaBlue = round(sepiaBlue_not_rounded);       //printf ("sepiaBlue = %i\n", sepiaBlue);

            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }

            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }

            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }

            // set each color value to the sepia value
            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int k;

    // for each row
    for (int i = 0; i < height; i++)
    {
        // for each column
        for (int j = 0; j < (0.5 * width); j++)
        {
            k = width - j - 1;

            // safe the original pixel (left side of picture)
            int original_pixel_left_red = image[i][j].rgbtRed;
            int original_pixel_left_green = image[i][j].rgbtGreen;
            int original_pixel_left_blue = image[i][j].rgbtBlue;

            // switch the left side of picture
            image[i][j].rgbtRed = image[i][k].rgbtRed;
            image[i][j].rgbtGreen = image[i][k].rgbtGreen;
            image[i][j].rgbtBlue = image[i][k].rgbtBlue;

            // switch the right side of picture
            image[i][k].rgbtRed = original_pixel_left_red;
            image[i][k].rgbtGreen = original_pixel_left_green;
            image[i][k].rgbtBlue = original_pixel_left_blue;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // A = pixel_north_west;
    // B = pixel_north;
    // C = pixel_north_east;
    // D = pixel_middle_west;
    // E = pixel_middle; the one to change
    // F = pixel_middle_east;
    // G = pixel_south_west;
    // H = pixel_south;
    // I = pixel_south_east;

    float red_A;          
    float red_B;                      
    float red_C;                      
    float red_D;                      
    float red_E;                      
    float red_F;                      
    float red_G;                      
    float red_H;                      
    float red_I;                      

    float green_A;
    float green_B;
    float green_C;
    float green_D;
    float green_E;
    float green_F;
    float green_G;
    float green_H;
    float green_I;
    
    float blue_A;
    float blue_B;
    float blue_C;
    float blue_D;
    float blue_E;
    float blue_F;
    float blue_G;
    float blue_H;
    float blue_I;

    int summe_of_pixels;
    
    float red_summe_of_colours;
    float green_summe_of_colours;
    float blue_summe_of_colours;
    
    float red_average_not_rounded;
    float green_average_not_rounded;
    float blue_average_not_rounded;
    
    int red_average;
    int green_average; 
    int blue_average;

    int k;                
    int l;
    
    
    // copy an array for new_image, part 1/2
    RGBTRIPLE new_image[height][width];
    

    // for each row
    for (int i = 0; i < height; i++)                              
    {
        // for each column
        for (int j = 0; j < width; j++)                           
        {
            summe_of_pixels = 1;
            
            red_summe_of_colours = 0;       
            green_summe_of_colours = 0;       
            blue_summe_of_colours = 0;
            
            red_average = 0;                
            green_average = 0;                
            blue_average = 0;

            // assign elements to array new_image, part 2/2
            new_image[i][j] = image[i][j];

            // pixel A
            k = i - 1; 
            l = j - 1;
            if (k >= 0 & k < height &l >= 0 & l < width)
            {
                red_A = image[k][l].rgbtRed;
                green_A = image[k][l].rgbtGreen;
                blue_A = image[k][l].rgbtBlue;
            }
            else
            {
                red_A = -1;
            }

            // pixel B
            k = i - 1; 
            l = j;
            if (k >= 0 & k < height &l >= 0 & l < width)
            {   
                red_B = image[k][l].rgbtRed;
                green_B = image[k][l].rgbtGreen;
                blue_B = image[k][l].rgbtBlue;
            }
            else
            {
                red_B = -1;
            }

            // pixel C
            k = i - 1; 
            l = j + 1;
            if (k >= 0 & k < height &l >= 0 & l < width)
            {   
                red_C = image[k][l].rgbtRed;
                green_C = image[k][l].rgbtGreen;
                blue_C = image[k][l].rgbtBlue;
            }
            else
            {
                red_C = -1;
            }

            // pixel D
            k = i; 
            l = j - 1;
            if (k >= 0 & k < height &l >= 0 & l < width)
            {   
                red_D = image[k][l].rgbtRed;
                green_D = image[k][l].rgbtGreen;
                blue_D = image[k][l].rgbtBlue;
            }
            else
            {
                red_D = -1;
            }

            // pixel E (middle)
            red_E = image[i][j].rgbtRed;
            green_E = image[i][j].rgbtGreen;
            blue_E  = image[i][j].rgbtBlue;

            // pixel F
            k = i; 
            l = j + 1;
            if (k >= 0 & k < height &l >= 0 & l < width)
            {   
                red_F   = image[k][l].rgbtRed;               
                green_F = image[k][l].rgbtGreen;
                blue_F  = image[k][l].rgbtBlue;
            }
            else
            {
                red_F = -1;
            }

            // pixel G
            k = i + 1; 
            l = j - 1;                           
            if (k >= 0 & k < height &l >= 0 & l < width)
            {   
                red_G   = image[k][l].rgbtRed;              
                green_G = image[k][l].rgbtGreen;
                blue_G  = image[k][l].rgbtBlue;
            }
            else
            {
                red_G = -1;
            }

            // pixel H
            k = i + 1; 
            l = j;                                 
            if (k >= 0 & k < height &l >= 0 & l < width)
            {   
                red_H   = image[k][l].rgbtRed;              
                green_H = image[k][l].rgbtGreen;
                blue_H  = image[k][l].rgbtBlue;
            }
            else
            {
                red_H = -1;
            }

            // pixel I
            k = i + 1; 
            l = j + 1;                        
            if (k >= 0 & k < height &l >= 0 & l < width)
            {   
                red_I = image[k][l].rgbtRed;
                green_I = image[k][l].rgbtGreen;
                blue_I  = image[k][l].rgbtBlue;
            }
            else
            {
                red_I = -1;
            }

            // calculate number of existing pixels nearby (8 pixels) (its enough only for one colour)
            if (red_A >= 0)
            {
                summe_of_pixels++;
            }
            if (red_B >= 0)
            {
                summe_of_pixels++;
            }
            if (red_C >= 0)
            {
                summe_of_pixels++;
            }
            if (red_D >= 0)
            {
                summe_of_pixels++;
            }
            if (red_F >= 0)
            {
                summe_of_pixels++;
            }
            if (red_G >= 0)
            {
                summe_of_pixels++;
            }
            if (red_H >= 0)
            {
                summe_of_pixels++;
            }
            if (red_I >= 0)
            {
                summe_of_pixels++;
            }

            //printf ("summe_of_pixels = %i\n", summe_of_pixels);

            // calculate summe of colours of all existing pixels nearby (including middle = 9 pixels)
            if (red_A >= 0)
            {
                red_summe_of_colours = red_A;                              
                green_summe_of_colours = green_A;
                blue_summe_of_colours = blue_A;
            }
            if (red_B >= 0)
            {
                red_summe_of_colours = red_summe_of_colours + red_B;       
                green_summe_of_colours = green_summe_of_colours + green_B;
                blue_summe_of_colours = blue_summe_of_colours + blue_B;
            }
            if (red_C >= 0)
            {
                red_summe_of_colours = red_summe_of_colours + red_C;        
                green_summe_of_colours = green_summe_of_colours + green_C;
                blue_summe_of_colours = blue_summe_of_colours + blue_C;
            }
            if (red_D >= 0)
            {
                red_summe_of_colours = red_summe_of_colours + red_D;       
                green_summe_of_colours = green_summe_of_colours + green_D;
                blue_summe_of_colours = blue_summe_of_colours + blue_D;
            }
            if (red_E >= 0)
            {
                red_summe_of_colours = red_summe_of_colours + red_E;        
                green_summe_of_colours = green_summe_of_colours + green_E;
                blue_summe_of_colours = blue_summe_of_colours + blue_E;
            }
            if (red_F >= 0)
            {
                red_summe_of_colours = red_summe_of_colours + red_F;        
                green_summe_of_colours = green_summe_of_colours + green_F;
                blue_summe_of_colours = blue_summe_of_colours + blue_F;
            }
            if (red_G >= 0)
            {
                red_summe_of_colours = red_summe_of_colours + red_G;        
                green_summe_of_colours = green_summe_of_colours + green_G;
                blue_summe_of_colours = blue_summe_of_colours + blue_G;
            }
            if (red_H >= 0)
            {
                red_summe_of_colours = red_summe_of_colours + red_H;        
                green_summe_of_colours = green_summe_of_colours + green_H;
                blue_summe_of_colours = blue_summe_of_colours + blue_H;
            }
            if (red_I >= 0)
            {
                red_summe_of_colours = red_summe_of_colours + red_I;        
                green_summe_of_colours = green_summe_of_colours + green_I;
                blue_summe_of_colours = blue_summe_of_colours + blue_I;
            }

            //printf ("red_summe of colors = %f\n", red_summe_of_colours);
            //printf ("green_summe of colors = %f\n", green_summe_of_colours);
            //printf ("blue_summe of colors = %f\n", blue_summe_of_colours);

            //calculate average colour
            red_average_not_rounded = red_summe_of_colours / summe_of_pixels; 
            green_average_not_rounded = green_summe_of_colours / summe_of_pixels;
            blue_average_not_rounded = blue_summe_of_colours / summe_of_pixels;

            // round the average colour number to the full number
            red_average = round(red_average_not_rounded);                     
            green_average = round(green_average_not_rounded);
            blue_average = round(blue_average_not_rounded);
            
            // give new value to pixels from new_image
            new_image[i][j].rgbtRed = red_average; 
            new_image[i][j].rgbtGreen = green_average;
            new_image[i][j].rgbtBlue = blue_average;
        }
    }

    // print new_image after all pixels have been calculated

    // for each row
    for (int i = 0; i < height; i++)                
    {
        // for each column
        for (int j = 0; j < width; j++)                        
        {
            // give new value to the pixel_middle in original image
            image[i][j].rgbtRed = new_image[i][j].rgbtRed; 
            image[i][j].rgbtGreen = new_image[i][j].rgbtGreen;
            image[i][j].rgbtBlue = new_image[i][j].rgbtBlue;
        }
    }
    return;
}
