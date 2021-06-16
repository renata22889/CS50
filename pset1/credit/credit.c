#include <cs50.h>
#include <stdio.h>
#include <math.h>

// defined function power
// because orginal function "pow" not work between long (nr) and double(pow)
long power(int m, int n)
{ 
    long p = 1;

    for (int i = 0; i < n; i++)
    {
        p = round(p * m);
    }
    return p;
}


// defined function, which add each digit of the number separately
int add(int r)
{
    int p = 2 * r;                                //printf(" p = %i\n", p);
    int p1 = p % power(10, 1);                  //printf(" p1 = %i\n", p1);
    int p2 = (p % power(10, 2) - p1) / 10;     //printf(" p2 = %i\n", p2);

    return p1 + p2;                               //printf(" p1 + p2 = %i\n", p1 + p2);
}


long get_nr(void)
// ask the user for credit card number
// nr < 13 digits
// nr > 13 digits & nr < 15 digits
// nr > 16 digits
{
    long nr;

    do
    {
        nr = get_long("Number:");
        
    }
    while (nr < 0);
    
    if (nr < power(10, 12) || (nr > 9999999999999 & nr < power(10, 14))  || nr > 9999999999999999)
    {
        printf("INVALID\n");
    }
    else
    {

    }

    return nr;
}


int main(void)
{
    long nr = get_nr();

// number of digit, from right to left
    if ((nr >= power(10, 12) & nr < power(10, 13)) || (nr >= power(10, 14) & nr < power(10, 16))) 
    {

        int nr1 = nr % power(10, 1);                                            //printf(" nr1 = %i\n", nr1);
        int nr2 = (nr % power(10, 2) - nr1) / 10;                               //printf(" nr2 = %i\n", nr2);
        int nr3 = (nr % power(10, 3) - nr % power(10, 2)) / power(10, 2);      //printf(" nr3 = %i\n", nr3);
        int nr4 = (nr % power(10, 4) - nr % power(10, 3)) / power(10, 3);       //printf(" nr4 = %i\n", nr4);
        int nr5 = (nr % power(10, 5) - nr % power(10, 4)) / power(10, 4);       //printf(" nr5 = %i\n", nr5);
        int nr6 = (nr % power(10, 6) - nr % power(10, 5)) / power(10, 5);       //printf(" nr6 = %i\n", nr6);
        int nr7 = (nr % power(10, 7) - nr % power(10, 6)) / power(10, 6);       //printf(" nr7 = %i\n", nr7);
        int nr8 = (nr % power(10, 8) - nr % power(10, 7)) / power(10, 7);       //printf(" nr8 = %i\n", nr8);
        int nr9 = (nr % power(10, 9) - nr % power(10, 8)) / power(10, 8);       //printf(" nr9 = %i\n", nr9);
        int nr10 = (nr % power(10, 10) - nr % power(10, 9)) / power(10, 9);     //printf(" nr10 = %i\n", nr10);
        int nr11 = (nr % power(10, 11) - nr % power(10, 10)) / power(10, 10);   //printf(" nr11 = %i\n", nr11);
        int nr12 = (nr % power(10, 12) - nr % power(10, 11)) / power(10, 11);   //printf(" nr12 = %i\n", nr12);
        int nr13 = (nr % power(10, 13) - nr % power(10, 12)) / power(10, 12);   //printf(" nr13 = %i\n", nr13);
        int nr14 = (nr % power(10, 14) - nr % power(10, 13)) / power(10, 13);   //printf(" nr14 = %i\n", nr14);
        int nr15 = (nr % power(10, 15) - nr % power(10, 14)) / power(10, 14);   //printf(" nr15 = %i\n", nr15);
        int nr16 = (nr % power(10, 16) - nr % power(10, 15)) / power(10, 15);   //printf(" nr16 = %i\n", nr16);

        int nr12and13 = (nr % power(10, 13) - nr % power(10, 11)) / power(10, 11); //printf(" nr12and13 = %i\n", nr12and13);
        int nr14and15 = (nr % power(10, 15) - nr % power(10, 13)) / power(10, 13); //printf(" nr14and15 = %i\n", nr14and15);
        int nr15and16 = (nr % power(10, 16) - nr % power(10, 14)) / power(10, 14); //printf(" nr15and16 = %i\n", nr15and16);


// checksum Luhn’s Algorithm
    
        // step1: multiply every other digit by 2

        int step1 = 2 * nr2 + 2 * nr4 + 2 * nr6 + 2 * nr8 + 2 * nr10 + 2 * nr12 + 2 * nr14 + 2 * nr16;
        //printf("step1 = %i\n", step1);

        // step2: add those products’ digits together
        // with funcion add() described at beginn of code

        int step2 = add(nr2) +  add(nr4) +  add(nr6) +  add(nr8) +  add(nr10) +  add(nr12) +  add(nr14) +  add(nr16);

        //printf("add(nr2) = %i\n ", add(nr2));
        //printf("step2 = %i\n ", step2);

        // step3: Add the sum to the sum of the digits that weren’t multiplied by 2

        // sum of the digits that weren’t multiplied by 2
        int g = nr1 + nr3 + nr5 + nr7 + nr9 + nr11 + nr13 + nr15;
        //printf("g = %i\n", g);
        int step3 = step2 + g;                                     //printf("step3 = %i\n", step3);

        // step4: If the total’s last digit is 0 (or, put more formally, if the total modulo 10 is congruent to 0), the number is valid

        int step4 = step3 % power(10, 1);                        //printf("step4 = %i\n", step4);


        // validate the nr with company
        
        //calculation in this comment does not work
        //printf("ggg = %li\n,", power(10, 16) - power(10, 0));
        // so I use another one:
                                                                                        
        long y0 = pow(10, 0);                                           //printf("y1 = pow(10, 15) = %li\n", pow(10, 15) );
        long y12 = pow(10, 12);                                         //printf("y2 = pow(10, 0) = %.5f\n", pow(10, 0) );
        long y13 = pow(10, 13);                                         //printf("y1-y2 = pow(10, 0) = %.li\n", y1-y2 );
        long y14 = pow(10, 14);
        long y15 = pow(10, 15);
        long y16 = pow(10, 16);
        
        
        // AMERICAN EXPRESS: nr has 15 digits and starts with 34 or 37
        //printf("y14 = %li\n", y14);
        //printf("y15 - y0 = %li\n", y15 - y0);

        if (step4 == 0 && ((nr >=  y14) & (nr < y15 - y0))  && ((nr14and15 == 34) || (nr14and15 == 37)))
        {                           
            printf("AMEX\n");
        }

        // MASTERCARD: nr has 16 digits and starts with <51 ; 55>
        // here function "pow" - predefined - works, so I leave like that here
        //printf("y16 - y0 = %li\n", y16 - y0);

        else if (step4 == 0  && (nr >= y15  &  nr <= y16 - y0)  && (nr15and16 >= 51 & nr15and16 <= 55))
        {
            printf("MASTERCARD\n");
        }

        // VISA: nr has 13 or 16 digits and starts with 4
        //printf("y13 - y0 = %li\n", y13 - y0);
        //printf("y16 - y0 = %li\n", y16 - y0);

        else if (step4 == 0 && (((nr >= y12 & nr < y13 - y0) & (nr13 == 4)) || ((nr >= y15 & nr < y16 - y0) & (nr16 == 4))))
        {
            printf("VISA\n");
        }
        else 
        {
            printf("INVALID\n");
        }
    }
        
}