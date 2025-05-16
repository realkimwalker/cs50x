#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count, typedef struct is like defining a type
typedef struct
{
    string name;
    int votes;
} candidate;

// Array of candidates, a global variable accessible by all functions (wk 2)
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates, like PS2, argc - 1 is last candidate entered
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    // Remember PS2 argv[0] is name of program; last element is argv[argc-1];
    // Recall that argv[i + 1] is the first argument at CLP after ./pluarlity i.e. Bob
    // Recall that argc is the size of the array argv; and argv[] is array of strings;
    // Loop is initializing and accessing candidates names & votes from CLP;
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
    int highest_votes = 0;
    string winner;

    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i].name, name) == 0)
        {
            candidates[i].votes += 1;
            return true;
        }
    }
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    int highest_votes = 0;
    string winner;

    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes > highest_votes)
        {
            highest_votes = candidates[i].votes;
            winner = candidates[i].name;
        }
        else if ((candidates[i].votes == highest_votes) && (candidates[i].votes > 0))
        {
            printf("%s\n", candidates[i].name);
        }
    }
    printf("%s\n", winner);
    return;
}
