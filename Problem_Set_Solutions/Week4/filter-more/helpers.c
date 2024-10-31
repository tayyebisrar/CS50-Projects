#include "helpers.h"
#include <math.h>
#include <stdlib.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++) // for each pixel
        {
            float average = (image[i][j].rgbtBlue + image[i][j].rgbtRed + image[i][j].rgbtGreen) /
                            3.0;            // find the average
            average = (int) round(average); // round it and make it an integer
            image[i][j].rgbtRed = average;  // assign all rgb the same average value
            image[i][j].rgbtBlue = average;
            image[i][j].rgbtGreen = average;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++) // for each row
    {
        for (int j = 0; j < width / 2; j++) // for each column (so each pixel now)
        {
            RGBTRIPLE *temp = malloc(sizeof(RGBTRIPLE)); // assign a temporary pixel
            *temp = image[i][j];                         // store the old pixel
            image[i][j] = image[i][width - j - 1];       // swap the first pixel
            image[i][width - j - 1] = *temp;             // with the opposite pixel
            free(temp);                                  // free memory
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp_image[height][width]; // create a temporary image

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++) // for each pixel
        {
            int count = 0;
            int r_total = 0; // hold a running total for rgb
            int g_total = 0;
            int b_total = 0;

            for (int a = -1; a < 2; a++)
            {
                for (int b = -1; b < 2; b++) // within the 3x3 grid
                {
                    if ((((i + a) < height) && ((i + a) >= 0)) &&
                        (((j + b) < width) && ((j + b) >= 0))) // if 3x3 is possible for that pixel
                    {
                        r_total += image[i + a][j + b].rgbtRed; // add its values to the total
                        g_total += image[i + a][j + b].rgbtGreen;
                        b_total += image[i + a][j + b].rgbtBlue;
                        count++; // increment counter
                    }
                }
            }
            count = (float) count; // calculate the average to blur the pixel
            r_total = round((float) r_total / count);
            g_total = round((float) g_total / count);
            b_total = round((float) b_total / count);
            temp_image[i][j].rgbtRed = (int) r_total; // assign the new blurred pixels to the image
            temp_image[i][j].rgbtGreen = (int) g_total;
            temp_image[i][j].rgbtBlue = (int) b_total;
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++) // for each pixel
        {
            image[i][j] = temp_image[i][j]; // replace the old pixel with the new blurred pixel
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}}; // initialise the Gx matrix
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}}; // initialise the Gy matrix

    RGBTRIPLE temp_image[height][width]; // create a temporary image

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int r_total_x = 0; // create variables for rgb for the Gx values
            int g_total_x = 0;
            int b_total_x = 0;
            int r_total_y = 0; // create variables for rgb for the Gy values
            int g_total_y = 0;
            int b_total_y = 0;
            for (int a = -1; a < 2; a++)
            {
                for (int b = -1; b < 2; b++) // within the 3x3 area around the pixel
                {
                    if ((((i + a) < height) && ((i + a) >= 0)) &&
                        (((j + b) < width) && ((j + b) >= 0))) // if it's in the image
                    {
                        r_total_x += (image[i + a][j + b].rgbtRed *
                                      Gx[a + 1][b + 1]); // add up the Gx and Gy values
                        g_total_x += (image[i + a][j + b].rgbtGreen * Gx[a + 1][b + 1]);
                        b_total_x += (image[i + a][j + b].rgbtBlue * Gx[a + 1][b + 1]);
                        r_total_y += (image[i + a][j + b].rgbtRed * Gy[a + 1][b + 1]);
                        g_total_y += (image[i + a][j + b].rgbtGreen * Gy[a + 1][b + 1]);
                        b_total_y += (image[i + a][j + b].rgbtBlue * Gy[a + 1][b + 1]);
                    }
                }
            }
            int sobelvalr = (int) round(sqrt(
                pow(r_total_x, 2) + pow(r_total_y, 2))); // find the squared average and round it
            int sobelvalg =
                (int) round(sqrt(pow(g_total_x, 2) + pow(g_total_y, 2))); // then cast to integer
            int sobelvalb = (int) round(
                sqrt(pow(b_total_x, 2) + pow(b_total_y, 2))); // then store in variables rgb
            if (sobelvalr > 255)                              // make sure they are capped at 255
            {
                sobelvalr = 255;
            }
            if (sobelvalg > 255)
            {
                sobelvalg = 255;
            }
            if (sobelvalb > 255)
            {
                sobelvalb = 255;
            }

            temp_image[i][j].rgbtRed = sobelvalr; // assign the rgb values to the new image
            temp_image[i][j].rgbtGreen = sobelvalg;
            temp_image[i][j].rgbtBlue = sobelvalb;
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++) // for each pixel
        {
            image[i][j] = temp_image[i][j]; // replace the old pixel with the new altered pixel
        }
    }

    return;
}†
