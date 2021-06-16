#include <cs50.h>
#include <stdio.h>
#include <math.h>

float get_floatt(void)
// ask the user how much change is owed
{
    float dollars;
    int cents;
    
    do
    {
        dollars = get_float("Change owed:");

        // transfer amount in dollars into coins
        // round the float-number and transfer it to int-number
        cents = round(dollars * 100);
    }
    while (dollars <= 0);

    return cents;
}


int main(void)
// calculate the number of used coins
// use the largest coins possible
{
    int cents = get_floatt();
    int q = 0;  // q - number of 0,25$ coins
    int d = 0;  // q - number of 0,10$ coins
    int n = 0;  // q - number of 0,05$ coins
    int p = 0;  // q - number of 0,01$ coins



    // check how many 0,25$ coins are needed
    while (cents - q * 25 >= 25)
    {
        q++;
    }
    // print the largest number of q (that the loop gone through)
    //printf("q= %i\n", q);
    // r1 - rest after calculation
    //printf("r1= %.i\n", cents - q * 25);


    //check how many 0,10$ coins is needed
    while (cents - q * 25 - d * 10 >= 10)
    {
        d++;
    }
    // print the largest number of d
    //printf("d= %i\n", d);
    // r2 - rest after calculation
    //printf("r2= %i\n", cents - q * 25 - d * 10);


    //check how many 0,05$ coins is needed
    while (cents - q * 25 - d * 10 - n * 5 >= 5)
    {
        n++;
    }
    // print the largest number of n
    //printf("n= %i\n", n);
    // r3 - rest after calculation
    //printf("r3= %i\n", cents - q * 25 - d * 10 - n * 5);


    //check how many 0,01$ coins is needed
    while (cents - q * 25 - d * 10 - n * 5 - p * 1 >= 1)
    {
        p++;
    }
    // print the largest number of p
    //printf("p= %i\n", p);
    // r4 - rest after calculation
    //printf("r4= %i\n", cents - q * 25 - d * 10 - n * 5 - p * 1);


    // s - summarize the amount of the needed coins
    int s = q + d + n + p;
    printf("%i\n", s);

}



