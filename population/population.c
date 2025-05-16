#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // TODO: Prompt for start size
    int n;
    do
    {
        n = get_int("Start Size: ");
    }
    while (n < 9);

    // TODO: Prompt for end size
    int p;
    do
    {
        p = get_int("End Size: ");
    }
    while (p < n);

    // TODO: Calculate number of years until we reach threshold
    int i = 0;
    do
    {
        n = n + (n / 3) - (n / 4);
        i = i + 1;
    }
    while (n < p);

    // TODO: Print number of years
    printf("Years: %i\n", i);
}
