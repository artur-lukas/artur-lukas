#include "helpers.h"
#include <math.h>
#include <stdbool.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int average;
            average =
                round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
            image[i][j].rgbtBlue = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtRed = average;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sepiaBlue;
            int sepiaGreen;
            int sepiaRed;

            if (round(0.131 * image[i][j].rgbtBlue + 0.534 * image[i][j].rgbtGreen +
                      0.272 * image[i][j].rgbtRed) < 255)
                sepiaBlue = round(0.131 * image[i][j].rgbtBlue + 0.534 * image[i][j].rgbtGreen +
                                  0.272 * image[i][j].rgbtRed);
            else
                sepiaBlue = 255;

            if (round(0.168 * image[i][j].rgbtBlue + 0.686 * image[i][j].rgbtGreen +
                      0.349 * image[i][j].rgbtRed) < 255)
                sepiaGreen = round(0.168 * image[i][j].rgbtBlue + 0.686 * image[i][j].rgbtGreen +
                                   0.349 * image[i][j].rgbtRed);
            else
                sepiaGreen = 255;

            if (round(0.189 * image[i][j].rgbtBlue + 0.769 * image[i][j].rgbtGreen +
                      0.393 * image[i][j].rgbtRed) < 255)
                sepiaRed = round(0.189 * image[i][j].rgbtBlue + 0.769 * image[i][j].rgbtGreen +
                                 0.393 * image[i][j].rgbtRed);
            else
                sepiaRed = 255;

            image[i][j].rgbtBlue = sepiaBlue;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtRed = sepiaRed;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        RGBTRIPLE copy_row[width];
        for (int j = 0; j < width; j++)
            copy_row[j] = image[i][j];
        for (int j = 0; j < width; j++)
            image[i][j] = copy_row[width - j - 1];
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy_image[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy_image[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float sum_B = 0;
            float sum_G = 0;
            float sum_R = 0;
            int sum_pixel = 1;

            sum_B += copy_image[i][j].rgbtBlue;
            sum_G += copy_image[i][j].rgbtGreen;
            sum_R += copy_image[i][j].rgbtRed;

            bool top = false;
            bool down = false;
            bool right = false;
            bool left = false;

            if (0 <= i - 1)
                top = true;
            if (0 <= j - 1)
                left = true;
            if (i + 1 < height)
                down = true;
            if (j + 1 < width)
                right = true;

            if (top && left)
            {
                sum_B += copy_image[i - 1][j - 1].rgbtBlue;
                sum_G += copy_image[i - 1][j - 1].rgbtGreen;
                sum_R += copy_image[i - 1][j - 1].rgbtRed;
                sum_pixel++;
            }

            if (top)
            {
                sum_B += copy_image[i - 1][j].rgbtBlue;
                sum_G += copy_image[i - 1][j].rgbtGreen;
                sum_R += copy_image[i - 1][j].rgbtRed;
                sum_pixel++;
            }

            if (top && right)
            {
                sum_B += copy_image[i - 1][j + 1].rgbtBlue;
                sum_G += copy_image[i - 1][j + 1].rgbtGreen;
                sum_R += copy_image[i - 1][j + 1].rgbtRed;
                sum_pixel++;
            }

            if (left)
            {
                sum_B += copy_image[i][j - 1].rgbtBlue;
                sum_G += copy_image[i][j - 1].rgbtGreen;
                sum_R += copy_image[i][j - 1].rgbtRed;
                sum_pixel++;
            }

            if (down && left)
            {
                sum_B += copy_image[i + 1][j - 1].rgbtBlue;
                sum_G += copy_image[i + 1][j - 1].rgbtGreen;
                sum_R += copy_image[i + 1][j - 1].rgbtRed;
                sum_pixel++;
            }

            if (down)
            {
                sum_B += copy_image[i + 1][j].rgbtBlue;
                sum_G += copy_image[i + 1][j].rgbtGreen;
                sum_R += copy_image[i + 1][j].rgbtRed;
                sum_pixel++;
            }

            if (down && right)
            {
                sum_B += copy_image[i + 1][j + 1].rgbtBlue;
                sum_G += copy_image[i + 1][j + 1].rgbtGreen;
                sum_R += copy_image[i + 1][j + 1].rgbtRed;
                sum_pixel++;
            }

            if (right)
            {
                sum_B += copy_image[i][j + 1].rgbtBlue;
                sum_G += copy_image[i][j + 1].rgbtGreen;
                sum_R += copy_image[i][j + 1].rgbtRed;
                sum_pixel++;
            }

            sum_B = round(sum_B / sum_pixel);
            sum_G = round(sum_G / sum_pixel);
            sum_R = round(sum_R / sum_pixel);

            image[i][j].rgbtBlue = sum_B;
            image[i][j].rgbtGreen = sum_G;
            image[i][j].rgbtRed = sum_R;
        }
    }
    return;
}
