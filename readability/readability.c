#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    string text = get_string("Text: ");

    // Initialize variables locat to main()
    int L = 0;
    int W = 0;
    int S = 0;

    float index = 0;
    int indexrounded = 0;

    L = count_letters(text);
    W = count_words(text);
    S = count_sentences(text);

    float l = 0;
    float s = 0;

    // Cast each variable l and s to floats before computing Coleman Liau
    l = ((float) L / W) * 100;
    s = ((float) S / W) * 100;

    // Compute the Coleman-Liau index
    index = (0.0588 * l) - (0.296 * s) - 15.8;
    indexrounded = round(index);

    // Print the grade level
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
        printf("Grade %i\n", indexrounded);

    return 0;
}

int count_letters(string text)
{
    int L = 0;

    // Return the number of letters, l, in text
    for (int i = 0, len = strlen(text); i < len; i++)
    {
        // Count number of characters
        if (isalpha(text[i]))
        {
            L++;
        }
    }

    return L;
}

int count_words(string text)
{
    // Return the number of words in text
    int W = 1;

    for (int i = 0, len = strlen(text); i < len; i++)
    {
        // Count number of spaces in text and add to words
        if (isspace(text[i]))
        {
            W++;
        }
    }

    return W;
}

int count_sentences(string text)
{
    // Return the number of sentences, s, in text by counting characters . ! or ?
    int S = 0;

    for (int i = 0, len = strlen(text); i < (len); i++)
    {
        // Count number of sentences by
        char a = '.';
        char b = '?';
        char c = '!';
        if (text[i] == a || text[i] == b || text[i] == c)
        {
            S++;
        }
    }
    return S;
}
