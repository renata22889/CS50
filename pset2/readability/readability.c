// pseudocode:
//
// function calculate_grade();
// int main(void)
// {
//      prompt the user for a string of text (using get_string)

//      define arguments:
//       - a letter (as ...)
//       - a word (as ...)
//       - sentence (as ... )

//       print result
//       if (grade >= 1 || grade < 16); print "Grade X"
//       else if (grade >= 16); print "Grade 16+"
//       else (grade < 1) ; print "Before Grade 1"
// }
// function calculate_grade()
// // function average() optional
// index = 0.0588 * L - 0.296 * S - 15.8

#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

// function calculate_grade();

float average(int a, int b);
int calculate_grade(float L, float S);

int main(void)
{
    // prompt the user for a string of text
    string text = get_string("Text:");

    // define arguments:
    int i = 0;
    int all_letters = 0;
    int all_words = 1;
    int all_sentences = 0;
    int text_length = strlen(text);
    float L;    // L - average number of letters per 100 words in the text
    float S;    // S - average number of sentences per 100 words in the text
    int grade;

    for (i = 0; i < text_length; i++)
    {
        // define letter as any lowercase character from a to z or any uppercase character from A to Z
        if (text[i] >= 'a' & text[i] <= 'z' || text[i] >= 'A' & text[i] <= 'Z')
        {
            all_letters += 1;
        }

        // define word as any sequence of characters separated by spaces
        if (text[i] == ' ')
        {
            all_words += 1;
        }

        // define sentence: any occurrence of a period, exclamation point, or question mark indicates the end of a sentence
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            all_sentences += 1;
        }
    }
    //printf("all_letters = %i\n", all_letters);
    //printf("all_words = %i\n", all_words);
    //printf("all_sentences = %i\n", all_sentences);


    // function average() per 100 words;
    L = average(all_letters, all_words); //printf("Lneu = %f\n", L);
    S = average(all_sentences, all_words); //printf("Sneu = %f\n", S);

    // function calculate_grade();
    grade = calculate_grade(L, S);
    printf("grade = %i\n", calculate_grade(L, S));


    // output result
    if (grade >= 1 && grade < 16)
    {
        printf("Grade %i\n", grade);
        return 0;
    }
    else if (grade >= 16)
    {
        printf("Grade 16+\n");
        return 0;
    }
    else // (grade < 1)
    {
        printf("Before Grade 1\n");
        return 0;
    }
}

// function average() per 100 words
float average(int a, int b)
{
    float result = 100 * (float) a / (float) b;
    return result;
}

// function calculate_grade()
int calculate_grade(float L, float S)
{
    float index = round(0.0588 * L - 0.296 * S - 15.8);
    printf("index = %f\n", index);
    return index;
}