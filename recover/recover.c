#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // Accept a single command-line argument only, else Usage/return 1
    if (argc != 2)
    {
        printf("Usage: ./recover FILE\n");
        return 1;
    }

    // Open the memory card
    FILE *card = fopen(argv[1], "r");

    if (card == NULL)
    {
        printf("Could not open %s.\n", argv[1]);
        return 2;
    }

    // Set output file, called image, pointer to NULL
    FILE *image = NULL;

    // Allocate 512 bytes of memory for buffer
    BYTE buffer[512];

    // Declare counter variable and initialize to zero
    int counter = 0;

    // Allocate memory for output image file labels
    char filename[8] = {0};

    // While there's still data left to read from the memory card MAYBE less than 512
    // Write until fread returns the number of items of size size were read  at least 1
    while (fread(buffer, sizeof(BYTE) * 512, 1, card) == 1)
    {
        // Search buffer for jpg signatur in header
        if (buffer[0] == 0xFF && buffer[1] == 0xD8 && buffer[2] == 0xFF && (buffer[3] & 0xF0) == 0xE0)
        {
            // Close image ptr if jpeg was found before and written into ###.jpg
            if (image != NULL)
            {
                fclose(image);
            }
            // Sprintf is printing the label of each file
            sprintf(filename, "%03d.jpg", counter++);

            // Open output file named image (pointer) for writing data from buffer
            image = fopen(filename, "w");
        }

        // Check to see if you already have room to write on the file first!
        if (image != NULL)
        {
            fwrite(buffer, sizeof(BYTE) * 512, 1, image);
        }
    }

    // Close last opened output file and opened input file
    if (image != NULL)
    {
        fclose(image);
    }

    fclose(card);

    return 0;
}
