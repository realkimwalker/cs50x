#include "helpers.h"
#include "math.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int avgRGB = 0;

    // Loop over all pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Take average of red, green, and blue
            avgRGB = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);

            // Update pixel values
            image[i][j].rgbtRed = avgRGB;
            image[i][j].rgbtGreen = avgRGB;
            image[i][j].rgbtBlue = avgRGB;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop over all pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Initialize values for each loop
            int sepiaRed = 0;
            int sepiaGreen = 0;
            int sepiaBlue = 0;

            // Compute sepia values
            sepiaRed = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);
            sepiaGreen = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
            sepiaBlue = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);

            // Ensure no values are greater than 255 or set at 255
            if (sepiaRed <= 255)
            {
                image[i][j].rgbtRed = sepiaRed;
            }
            else
            {
                image[i][j].rgbtRed = 255;
            }

            if (sepiaGreen <= 255)
            {
                image[i][j].rgbtGreen = sepiaGreen;
            }
            else
            {
                image[i][j].rgbtGreen = 255;
            }

            if (sepiaBlue <= 255)
            {
                image[i][j].rgbtBlue = sepiaBlue;
            }
            else
            {
                image[i][j].rgbtBlue = 255;
            }
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Create a temp of image for pixel swap
    RGBTRIPLE temp[height][width];

    // Loop over all pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            temp[i][j] = image[i][j];
            image[i][j] = image[i][width - (j + 1)];
            image[i][width - (j + 1)] = temp[i][j];
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Create a copy of image
    RGBTRIPLE copy[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    // Tabulate pixel values;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // For all of first row
            if (i == 0)
            {
                image[i][j].rgbtRed = round(
                    (copy[i][j].rgbtRed + copy[i][j + 1].rgbtRed + copy[i + 1][j].rgbtRed + copy[i + 1][j + 1].rgbtRed) / 4.0);
                image[i][j].rgbtGreen = round(
                    (copy[i][j].rgbtGreen + copy[i][j + 1].rgbtGreen + copy[i + 1][j].rgbtGreen + copy[i + 1][j + 1].rgbtGreen) /
                    4.0);
                image[i][j].rgbtBlue = round(
                    (copy[i][j].rgbtBlue + copy[i][j + 1].rgbtBlue + copy[i + 1][j].rgbtBlue + copy[i + 1][j + 1].rgbtBlue) / 4.0);
            }

            // For left most column
            else if ((j == 0) || (i < (height - 1)))
            {
                image[i][j].rgbtRed = round((copy[i - 1][j].rgbtRed + copy[i - 1][j + 1].rgbtRed + copy[i][j].rgbtRed +
                                             copy[i][j + 1].rgbtRed + copy[i + 1][j].rgbtRed + copy[i + 1][j + 1].rgbtRed) /
                                            6.0);
                image[i][j].rgbtGreen = round((copy[i - 1][j].rgbtGreen + copy[i - 1][j + 1].rgbtGreen + copy[i][j].rgbtGreen +
                                               copy[i][j + 1].rgbtGreen + copy[i + 1][j].rgbtGreen + copy[i + 1][j + 1].rgbtGreen) /
                                              6.0);
                image[i][j].rgbtBlue = round((copy[i - 1][j].rgbtBlue + copy[i - 1][j + 1].rgbtBlue + copy[i][j].rgbtBlue +
                                              copy[i][j + 1].rgbtBlue + copy[i + 1][j].rgbtBlue + copy[i + 1][j + 1].rgbtBlue) /
                                             6.0);
            }

            // For last row
            else if (i == (height - 1))
            {
                image[i][j].rgbtRed = round((copy[i][j - 1].rgbtRed + copy[i][j].rgbtRed + copy[i][j + 1].rgbtRed +
                                             copy[i - 1][j - 1].rgbtRed + copy[i - 1][j].rgbtRed + copy[i - 1][j + 1].rgbtRed) /
                                            6.0);
                image[i][j].rgbtGreen =
                    round((copy[i][j - 1].rgbtGreen + copy[i][j].rgbtGreen + copy[i][j + 1].rgbtGreen +
                           copy[i - 1][j - 1].rgbtGreen + copy[i - 1][j].rgbtGreen + copy[i - 1][j + 1].rgbtGreen) /
                          6.0);
                image[i][j].rgbtBlue = round((copy[i][j - 1].rgbtBlue + copy[i][j].rgbtBlue + copy[i][j + 1].rgbtBlue +
                                              copy[i - 1][j - 1].rgbtBlue + copy[i - 1][j].rgbtBlue + copy[i - 1][j + 1].rgbtBlue) /
                                             6.0);
            }

            // For last column
            else if (j == (width - 1))
            {
                image[i][j].rgbtRed = round((copy[i][j].rgbtRed + copy[i][j - 1].rgbtRed + copy[i + 1][j].rgbtRed +
                                             copy[i + 1][j - 1].rgbtRed + copy[i - 1][j].rgbtRed + copy[i - 1][j - 1].rgbtRed) /
                                            6.0);
                image[i][j].rgbtGreen =
                    round((copy[i][j].rgbtGreen + copy[i][j - 1].rgbtGreen + copy[i + 1][j].rgbtGreen +
                           copy[i + 1][j - 1].rgbtGreen + copy[i - 1][j].rgbtGreen + copy[i - 1][j - 1].rgbtGreen) /
                          6.0);
                image[i][j].rgbtBlue = round((copy[i][j].rgbtBlue + copy[i][j - 1].rgbtBlue + copy[i + 1][j].rgbtBlue +
                                              copy[i + 1][j - 1].rgbtBlue + copy[i - 1][j].rgbtBlue + copy[i - 1][j - 1].rgbtBlue) /
                                             6.0);
            }
            else
                // Loop for rows around pixels that are not edges (3 3 box)
                for (int x = -1; x < 2; x++)
                {
                    for (int y = -1; y < 2; y++)
                    {
                        int nx = 0;
                        int ny = 0;
                        float redBlur = 0;
                        float greenBlur = 0;
                        float blueBlur = 0;
                        redBlur += image[i + x][j + y].rgbtRed;
                        greenBlur += image[i + x][j + y].rgbtGreen;
                        blueBlur += image[i + x][j + y].rgbtBlue;

                        copy[i][j].rgbtRed = round(redBlur / 9.0);
                        copy[i][j].rgbtGreen = round(greenBlur / 9.0);
                        copy[i][j].rgbtBlue = round(blueBlur / 9.0);

                        image[i][j].rgbtRed = copy[i][j].rgbtRed;
                        image[i][j].rgbtGreen = copy[i][j].rgbtGreen;
                        image[i][j].rgbtBlue = copy[i][j].rgbtBlue;
                    }
                }
        }
    }
    return;
}
