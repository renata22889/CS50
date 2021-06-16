#include <cs50.h>
#include <stdio.h>

//prompt user for height of pyramid integer, between 1 and 8 inclusive
int get_integer(void)
{
    // n - height of pyramid
    int n;

    // ask user for height, until given acceptable numer
    do
    {
        //prompt user for height
        n = get_int("Height: ");
    }

    // allow only height numbers between < 1 ; 8 >
    while (n < 1 || n > 8);

    return n;
}

int main(void)
{
    int n = get_integer();
    // create i number of rows
    for (int i = 0; i < n; i++)
    {

        // create j number of columns, fill each with a space
        for (int j = (n - i - 1) ; j > 0; j--)
        {
            printf(" ");
        }

        // create k number of columns, fill it with "#""
        for (int k = 0; k <= i; k++)
        {
            printf("#");
        }

        // create a gap of size of two "#"
        printf("  ");
        
        // create again k number of columns, fill it with "#""
        for (int k = 0; k <= i; k++)
        {
            printf("#");
        }

        // after creating j and k, go to next row
        printf("\n");
    }
}

