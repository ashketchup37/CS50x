#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {

            int r = image[i][j].rgbtRed;
            int g = image[i][j].rgbtGreen;
            int b = image[i][j].rgbtBlue;
            // Take the average of Red Blue and Green
            float gray = (r + g + b) / 3.0;
            int gray_i = (int) round(gray);
            // No value can be greater than 255
            if (gray_i > 255)
            {
                gray_i = 255;
            }
            // Updating the values
            image[i][j].rgbtRed = gray_i;
            image[i][j].rgbtBlue = gray_i;
            image[i][j].rgbtGreen = gray_i;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0, k = width - 1; j < k; j++, k--)
        {
            // swapping the left-most pixel with the right-most pixel until they meet in the middle.
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][k];
            image[i][k] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{

    RGBTRIPLE new_image[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Copying the current pixel for later use;
            new_image[i][j] = image[i][j];
            // Keeping track of the number of edges it has
            int count = 0;

            // Total
            // RGBTRIPLE total;
            // total_rgbtRed = 0;
            // total_rgbtBlue = 0;
            // total_rgbtGreen = 0;


            // I tried to use RGBTRIPLE total, but didn't work.
            // It can not store more than 255. So everytime my sum gets more than 255, it resets to 0
            // I'll have to use Integer

            int total_rgbtRed = 0;
            int total_rgbtBlue = 0;
            int total_rgbtGreen = 0;

            // Adding the top Row
            if (i > 0)
            {
                // Adding the Top-Left
                if (j > 0)
                {
                    total_rgbtRed += new_image[i - 1][j - 1].rgbtRed;
                    total_rgbtBlue += new_image[i - 1][j - 1].rgbtBlue;
                    total_rgbtGreen += new_image[i - 1][j - 1].rgbtGreen;

                    count++;
                }

                // Adding the Top-Middle
                total_rgbtRed += new_image[i - 1][j].rgbtRed;
                total_rgbtBlue += new_image[i - 1][j].rgbtBlue;
                total_rgbtGreen += new_image[i - 1][j].rgbtGreen;

                count++;

                // Adding the Top-Right
                if (j < width - 1)
                {
                    total_rgbtRed += new_image[i - 1][j + 1].rgbtRed;
                    total_rgbtBlue += new_image[i - 1][j + 1].rgbtBlue;
                    total_rgbtGreen += new_image[i - 1][j + 1].rgbtGreen;

                    count++;
                }
            }

            // Adding the Same Row

            // Adding the Middle-Left
            if (j > 0)
            {
                total_rgbtRed += new_image[i][j - 1].rgbtRed;
                total_rgbtBlue += new_image[i][j - 1].rgbtBlue;
                total_rgbtGreen += new_image[i][j - 1].rgbtGreen;

                count++;
            }

            // Adding the Middle-Middle :3
            total_rgbtRed += new_image[i][j].rgbtRed;
            total_rgbtBlue += new_image[i][j].rgbtBlue;
            total_rgbtGreen += new_image[i][j].rgbtGreen;

            count++;

            // Adding the Middle-Right
            if (j < width - 1)
            {
                total_rgbtRed += image[i][j + 1].rgbtRed;
                total_rgbtBlue += image[i][j + 1].rgbtBlue;
                total_rgbtGreen += image[i][j + 1].rgbtGreen;

                count++;
            }

            // Adding the Down Row
            if (i < height - 1)
            {
                // Adding the Down-Left
                if (j > 0)
                {
                    total_rgbtRed += image[i + 1][j - 1].rgbtRed;
                    total_rgbtBlue += image[i + 1][j - 1].rgbtBlue;
                    total_rgbtGreen += image[i + 1][j - 1].rgbtGreen;

                    count++;
                }

                // Adding the Down-Middle
                total_rgbtRed += image[i + 1][j].rgbtRed;
                total_rgbtBlue += image[i + 1][j].rgbtBlue;
                total_rgbtGreen += image[i + 1][j].rgbtGreen;

                count++;

                // Adding the Down-Right
                if (j < width - 1)
                {
                    total_rgbtRed += image[i + 1][j + 1].rgbtRed;
                    total_rgbtBlue += image[i + 1][j + 1].rgbtBlue;
                    total_rgbtGreen += image[i + 1][j + 1].rgbtGreen;

                    count++;
                }
            }

            // Calculating and Updating the new values
            int r = (int) round(total_rgbtRed / (count * 1.0));
            int g = (int) round(total_rgbtGreen / (count * 1.0));
            int b = (int) round(total_rgbtBlue / (count * 1.0));

            // Checking if any of them is higher than 255 and correcting it;
            if (r > 255)
            {
                image[i][j].rgbtRed = 255;
            }
            else
            {
                image[i][j].rgbtRed = r;
            }
            if (b > 255)
            {
                image[i][j].rgbtBlue = 255;
            }
            else
            {
                image[i][j].rgbtBlue = b;
            }
            if (g > 255)
            {
                image[i][j].rgbtGreen = 255;
            }
            else
            {
                image[i][j].rgbtGreen = g;
            }
        }
    }

    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE new_image[height + 2][width + 2];
    for (int i = 0; i < height + 2; i++)
    {
        for (int j = 0; j < width + 2; j++)
        {
            if (i == 0 || i == height + 1 || j == 0 || j == width + 1)
            {
                new_image[i][j].rgbtRed = 0;
                new_image[i][j].rgbtBlue = 0;
                new_image[i][j].rgbtGreen = 0;
            }
            else
            {
                new_image[i][j] = image[i - 1][j - 1];
            }
        }
    }

    for (int i = 1; i <= height; i++)
    {
        for (int j = 1; j <= width; j++)
        {
            // Gx
            int gx_red = (-1 * (new_image[i - 1][j - 1].rgbtRed + new_image[i + 1][j - 1].rgbtRed))
                         + (1 * (new_image[i - 1][j + 1].rgbtRed + new_image[i + 1][j + 1].rgbtRed))
                         + (-2 * new_image[i][j - 1].rgbtRed) + (2 * new_image[i][j + 1].rgbtRed);
            int gx_green = (-1 * (new_image[i - 1][j - 1].rgbtGreen + new_image[i + 1][j - 1].rgbtGreen))
                           + (1 * (new_image[i - 1][j + 1].rgbtGreen + new_image[i + 1][j + 1].rgbtGreen))
                           + (-2 * new_image[i][j - 1].rgbtGreen) + (2 * new_image[i][j + 1].rgbtGreen);
            int gx_blue = (-1 * (new_image[i - 1][j - 1].rgbtBlue + new_image[i + 1][j - 1].rgbtBlue))
                          + (1 * (new_image[i - 1][j + 1].rgbtBlue + new_image[i + 1][j + 1].rgbtBlue))
                          + (-2 * new_image[i][j - 1].rgbtBlue) + (2 * new_image[i][j + 1].rgbtBlue);



            // Gy
            int gy_red = (-1 * (new_image[i - 1][j - 1].rgbtRed + new_image[i - 1][j + 1].rgbtRed))
                         + (1 * (new_image[i + 1][j + 1].rgbtRed + new_image[i + 1][j - 1].rgbtRed))
                         + (-2 * new_image[i - 1][j].rgbtRed) + (2 * new_image[i + 1][j].rgbtRed);
            int gy_green = (-1 * (new_image[i - 1][j - 1].rgbtGreen + new_image[i - 1][j + 1].rgbtGreen))
                           + (1 * (new_image[i + 1][j + 1].rgbtGreen + new_image[i + 1][j - 1].rgbtGreen))
                           + (-2 * new_image[i - 1][j].rgbtGreen) + (2 * new_image[i + 1][j].rgbtGreen);
            int gy_blue = (-1 * (new_image[i - 1][j - 1].rgbtBlue + new_image[i - 1][j + 1].rgbtBlue))
                          + (1 * (new_image[i + 1][j + 1].rgbtBlue + new_image[i + 1][j - 1].rgbtBlue))
                          + (-2 * new_image[i - 1][j].rgbtBlue) + (2 * new_image[i + 1][j].rgbtBlue);


            int g_red = (int) round(sqrt((gx_red * gx_red) + (gy_red * gy_red)));
            int g_blue = (int) round(sqrt((gx_blue * gx_blue) + (gy_blue * gy_blue)));
            int g_green = (int) round(sqrt((gx_green * gx_green) + (gy_green * gy_green)));

            if (g_red > 255)
            {
                image[i - 1][j - 1].rgbtRed = 255;
            }
            else
            {
                image[i - 1][j - 1].rgbtRed = g_red;
            }
            if (g_blue > 255)
            {
                image[i - 1][j - 1].rgbtBlue = 255;
            }
            else
            {
                image[i - 1][j - 1].rgbtBlue = g_blue;
            }
            if (g_green > 255)
            {
                image[i - 1][j - 1].rgbtGreen = 255;
            }
            else
            {
                image[i - 1][j - 1].rgbtGreen = g_green;
            }
        }
    }
    return;
}
