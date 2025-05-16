#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Prompt user to enter a positive number between 1 and 8
    int n;
    do
    {
        n = get_int("Enter Number: ");
    }
    while (n < 1 || n > 8);

    // Build a "ascending hash" right alligned pyramid where base is user number and rows equal base
    int i = 0;
    int j = 0;
    for (j = 0; (n - j) > 0; j++)
    {
        for (i = 0; (n - i) > 0; i++)
        {
            if ((i + j) < (n - 1))
            {
                printf(" ");
            }
            else
                printf("#");
        }
        printf("\n");
    }
}
