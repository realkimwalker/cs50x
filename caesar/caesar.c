#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool only_digits(string key);
char rotate(char c, int k);

int main(int argc, string argv[])
{
    int k = 0;
    int length = 0;
    char cipherchar;

    // Make sure program is called with one argument that is key number
    while (argc != 2)
    {
        // return 1 indicates error occurred
        printf("Usage: ./caeser key argument error\n");
        return 1;
    }

    // Check to see if argc is only digits and positive integer
    if ((only_digits(argv[1])) && (argv[1] > 0))
    {
        k = atoi(argv[1]);
    }
    else
    {
        printf("Usage: ./caeser key integer invalid\n");
        return 1;
    }

    // Prompt user for plaintext and get plaintext length for array loop
    string plaintext = get_string("Plaintext:  ");
    length = strlen(plaintext);
    printf("ciphertext: ");

    // For ith element in plaintext, call rotate returning cipherchar to print char
    for (int i = 0; i < length; i++)
    {
        cipherchar = rotate(plaintext[i], k);
        printf("%c", (char) cipherchar);
    }

    // Prints newline
    printf("\n");
    return 0;
}

// Is character of string a digit?
bool only_digits(string argc)
{
    for (int i = 0, len = strlen(argc); i < len; i++)
    {
        // Return true if character is a digit, 1
        if (isdigit(argc[i]))
        {
            return 1;
        }
    }
    return 0;
}

// Function takes char c from ith element of plaintext, rotates returning cipherchar
char rotate(char c, int k)
{
    char cipherchar = 0;
    if (islower(c) && (isalpha(c)))
    {
        if ((c + (k % 26)) < 123)
        {
            cipherchar = (((int) c) + (k % 26));
        }
        else if ((c + (k % 26)) >= 123)
        {
            cipherchar = (((int) c) - 26 + (k % 26));
        }

        cipherchar = tolower(cipherchar);
    }
    else if (isupper(c) && (isalpha(c)))
    {
        if ((c + k) < 90)
        {
            cipherchar = (((int) c) + k);
        }
        else if ((c + k) >= 90)
        {
            cipherchar = (((int) c) + (k % 26));
        }

        cipherchar = toupper(cipherchar);
    }

    else if (ispunct(c) || isspace(c) || isdigit(c))
    {
        cipherchar = c;
    }

    return cipherchar;
}
