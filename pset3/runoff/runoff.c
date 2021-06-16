#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid // preferences[i][j] yessss done Ren
bool vote(int voter, int rank, string name)
{
    printf("start function vote\n");

    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i].name, name) == 0)
        {
            preferences[voter][rank] = i;
            //printf("voter %i preference %i is %s\n", voter +1, rank +1, candidates[i].name);
            return true;
        }
    }
    return false;
}

// Tabulate votes for non-eliminated candidates     CHANGE
// void tabulate(void)
void tabulate(void)
{
    printf("start function tabulate\n");
    int k;
    int j;
    
    // for each voter
    for (int i = 0 ; i < voter_count; i++)
    {
        j = 0;
        k = preferences[i][j];
        
        // if the first rank candidate has not been eliminated
        if (candidates[k].eliminated == false)
        {
            candidates[k].votes = candidates[k].votes + 1;
            printf("loop1: candidate %s, i = %i and j = %i has %i votes\n", candidates[k].name, i, j, candidates[k].votes);
        }

        // if the first rank candidate has been eliminated
        else
        {   
            // keep moving to next candidate in rank, until arrive to the candidate who has not been eliminated
            do
            {
                j++;
                
                // update the candidate name
                k = preferences[i][j];
                
                // if arrived to candidate in some lower rank (j), update the votes for this new candidate
                if (candidates[k].eliminated == false)
                {
                    candidates[k].votes = candidates[k].votes + 1;
                    printf("loop2: new candidate is %s, i = %i and j = %i has %i votes\n", candidates[k].name, i, j, candidates[k].votes);
                }
            }
            while (candidates[k].eliminated == true);
        }
        printf("candidate %s final score is %i votes\n", candidates[k].name, candidates[k].votes);
    }
    return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
// candidate who has more than half the vote
{
    printf("start function print winner\n");

    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes > 0.5 * voter_count)
        {
            printf("%s\n", candidates[i].name);
            return true;
        }
    }
    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    printf("start function find min\n");
    int min = voter_count;

    for (int i = 0 ; i < candidate_count; i++)
    {
        printf("candidate %s has %i votes\n",   candidates[i].name, candidates[i].votes);

        if (candidates[i].eliminated == false && candidates[i].votes < min)
        {
            min = candidates[i].votes;
        }
        printf("min number of votes is %i and has it candidate %s\n", min,  candidates[i].name);

    }
    printf("min is %i \n", min);
    return min;
}

// Return true if the election is tied between all remaining candidates, false otherwise
bool is_tie(int min)
{
    printf("start function is tie\n");

    for (int i = 0 ; i < candidate_count; i++)
    {
        if (candidates[i].eliminated == false && candidates[i].votes != min)
        {
            printf("all remaining candidates are not tied\n");
            return false;
        }
    }
    printf("all remaining candidates are tied\n");
    return true;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    printf("start function eliminate\n");

    min = find_min();

    for (int i = 0 ; i < voter_count; i++)
    {
        if (candidates[i].votes == min)
        {
            printf("candidates[i].eliminated is %s\n", candidates[i].name);
            candidates[i].eliminated = true;
        }
    }
    return;
}
