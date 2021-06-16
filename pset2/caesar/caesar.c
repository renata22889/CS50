#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>


int main(int argc, string argv[])
{
// if there is no or more than one command-line arguments
    if (argc != 2)
    {
        printf("missing command-line argument\n");
        return 1;
    }
    
// convert string_k to int_k
    int s = strlen(argv[1]);
    int digit[s];
    int input[s];
    int value[s];
    int power;
    int k = 0;
    int i;
      
      
    for (i = 0; i < s ; i++)  
    {
        digit[i] = argv[1][i] - 48;

        power = pow(10, s - i - 1);
        value[i] = digit[i] * power;
    
        k = k + value[i];
    }

// if any of the characters of the command-line argument is not a decimal digit
    for (i = 0; i < s; i++)
    {
        input[i] = argv[1][i];
 
        if (input[i] < 48 || input[i] > 57 || k < 0)
        {
            printf("Usage: ./caesar key\n");
            return 1; 
        }
    }

// if there is a correct command-line argument

    //convert plaintext into ciphertext
    string plaintext = get_string("plaintext:");
    
    printf("ciphertext:");

    int p = strlen(plaintext);
    for (i = 0; i < p; i++)
    {
        // convert small letters with code
        if (plaintext[i] >= 'a' && plaintext[i] <= 'z')
        {
            // if a letter with code is "z" or smaller
            if (plaintext[i] + k <= 'z')
            {
                int p1 = plaintext[i] + k;
                printf("%c", p1);
            }
            // if a letter with code is bigger than "z"
            else
            {
                int p2 = (plaintext[i] + k);

                while (p2 > 122)
                {
                    p2 =  p2 - 26;
                }
                printf("%c", p2);
            }
        }
        //convert big letters with code
        else if (plaintext[i] >= 'A' && plaintext[i] <= 'Z')
        {
            // if a letter with code is "Z" or smaller
            if (plaintext[i] + k <= 'Z')
            {
                int p1 = plaintext[i] + k;
                printf("%c", p1);
            }
            // if a letter with code is bigger than "Z"
            else
            {
                int p2 = plaintext[i] + k;

                while (p2 > 90)
                {
                    p2 = p2 - 26;
                }
                printf("%c", p2);
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