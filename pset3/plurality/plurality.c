#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h> // added by ren

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
int get_max_votes(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;

    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    for (int i = 0; i < candidate_count; i++)
    {
        //printf("i = %i\n", i);
        if (strcmp(candidates[i].name, name) == 0)
        {
            candidates[i].votes = candidates[i].votes + 1;
            return true;
        }
    }
    return false;
}

int get_max_votes(void)
{
    // show candidates votes - just checking, not necessary
    //for (int i = 0 ; i < candidate_count; i++)
        //printf("candidates[%i].name has %i votes\n", i, candidates[i].votes);


    // find the biggest number of votes
    int max_number = 0;

    for (int i = 0 ; i < candidate_count; i++)
    {
        if (candidates[i].votes >= candidates[winner].votes)
            max_number = i;
          
        return max_number;

    }
    //printf("winner is %s\n", candidates[winner].name);
    return true;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    int winner = get_max_votes();

    for (int i = 0 ; i < candidate_count; i++)
    {
        //if (candidates[i].votes == winner)
        //printf("winner from print winner is %s\n", candidates[i].name);
        printf("winner from printwinner is %s\n", candidates[winner].name);
    }
    return;
}