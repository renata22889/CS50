#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // ask user for name
    string answer = get_string("What's your name?\n");
    
    // greet user with their name
    printf("hello, %s\n", answer);
}