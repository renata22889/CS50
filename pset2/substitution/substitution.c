#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>


int main(int argc, string argv[])
{
// check if there is no or more than one command-line arguments
    if (argc != 2)
    {
        printf("missing command-line argument\n");
        return 1;
    }

// define arguments
    int s = strlen(argv[1]);
    int i = 0;
    int input[s];

// check if any of the characters of the command-line argument is:

    // CON1 - not containing 26 characters,
    int CON1 = (s != 26);

    if (CON1)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
        
    // CON2 and CON3
    for (i = 0; i < s; i++)
    {
        input[i] = argv[1][i];

        // CON3 - not an alphabetic character,
        int CON3 = (input[i] < 65) | (input[i] > 90 & input[i] < 97) | (input[i] > 122);

        if (CON3)
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }

        // CON2 - not containing each letter exactly once.
        for (int j = i + 1; j < s; j++)
        {
            input[j] = argv[1][j];
            //printf("input[i]= %c input[j] = %c\n", input[i], input[j]);
            if (input[i] == input[j])
            {
                printf("Usage: ./caesar key\n");
                return 1;
            }
        }

        for (int j = i - 1; j >= 0; j--)
        {
            input[j] = argv[1][j];

            if (input[i] == input[j])
            {
                printf("Usage: ./caesar key\n");
                return 1;
            }
        }
    }
    

// convert plaintext into ciphertext

    string plaintext = get_string("plaintext:");
    string ciphertext = "";
    printf("ciphertext:");

// define arguments
    int p = strlen(plaintext);
    int current_char;
    int after_calculation;

// change each letter of plaintext into cyphertext
    for (i = 0; i < p; i++)
    {
        // if plaintext is a small letter
        if (plaintext[i] >= 'a' && plaintext[i] <= 'z')
        {
            current_char = plaintext[i] - 97;
            
            // if current_char in code is a small letter
            if (input[current_char] >= 'a' && input[current_char] <= 'z')
            {
                printf("%c", argv[1][current_char]);
            }
            
            // if current_char in code is a big letter
            else
            {
                after_calculation = argv[1][current_char] + 32;
                printf("%c", after_calculation);
            }
        }

        // if plaintext is a big letter
        else if (plaintext[i] >= 'A' && plaintext[i] <= 'Z')
        {
            current_char = plaintext[i] - 65;
            
            // if current_char in code is a big letter
            if (input[current_char] >= 'A' && input[current_char] <= 'Z')
            {
                printf("%c", argv[1][current_char]);
            }
            
            // if current_char in code is a small letter
            else 
            {
                after_calculation = argv[1][current_char] - 32;
                printf("%c", after_calculation);
            }
        }

        //leave other signs unconverted
        else
        {
            printf("%c", plaintext[i]);
        }
    }
    printf("\n");
    return 0;
}
