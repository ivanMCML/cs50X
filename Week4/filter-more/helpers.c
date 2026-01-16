#include "helpers.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int sum = 0;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Calculate average
            sum = image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue;
            sum = (int) (sum / 3.00 + 0.5);

            // Set new values
            image[i][j].rgbtRed = sum;
            image[i][j].rgbtGreen = sum;
            image[i][j].rgbtBlue = sum;
        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temporary;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < (width + 1) / 2; j++)
        {
            // Swap pixels in row on opposite sides
            temporary = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = temporary;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // pixelCounter keeps track of the number of included pixel
    float pixelCounter;

    // Sum of color shares for each included pixel
    int red = 0;
    int green = 0;
    int blue = 0;

    // Allocate matrix for temporary image
    RGBTRIPLE **bluredImage = NULL;
    bluredImage = (RGBTRIPLE **) malloc(sizeof(RGBTRIPLE *) * height);

    // Check if allocation failed
    if (bluredImage == NULL)
    {
        printf("ERROR! Could not allocate memory!\n");
        return;
    }

    for (int i = 0; i < height; i++)
    {
        bluredImage[i] = (RGBTRIPLE *) malloc(sizeof(RGBTRIPLE) * width);

        // Check if allocation failed
        if (bluredImage[i] == NULL)
        {
            printf("ERROR! Could not allocate memory!\n");

            // Free allocated memory
            for (int j = 0; j < i; j++)
                free(bluredImage[j]);
            free(bluredImage);
            return;
        }
    }

    // Update each pixel in matrix
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Set starting values
            pixelCounter = 0;
            red = 0;
            green = 0;
            blue = 0;

            for (int k = i - 1; k < i + 2; k++)
            {
                // Check if pixel is on the edge
                if (k < 0 || k >= height)
                    continue;

                for (int l = j - 1; l < j + 2; l++)
                {
                    // Check if pixel is on the edge
                    if (l < 0 || l >= width)
                        continue;

                    // Update values
                    pixelCounter++;
                    red += image[k][l].rgbtRed;
                    green += image[k][l].rgbtGreen;
                    blue += image[k][l].rgbtBlue;
                }
            }
            // Update temporary image matrix
            bluredImage[i][j].rgbtRed = (int) (red / pixelCounter + 0.5);
            bluredImage[i][j].rgbtGreen = (int) (green / pixelCounter + 0.5);
            bluredImage[i][j].rgbtBlue = (int) (blue / pixelCounter + 0.5);
        }
    }

    // Save values from temporary image matrix into original image matrix
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
            image[i][j] = bluredImage[i][j];
    }

    // Free allocated memory
    for (int i = 0; i < height; i++)
        free(bluredImage[i]);
    free(bluredImage);

    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{

    int xRed = 0;
    int xGreen = 0;
    int xBlue = 0;
    int yRed = 0;
    int yGreen = 0;
    int yBlue = 0;

    int gX[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int gY[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    // Allocate matrix for temporary image
    RGBTRIPLE **edgedImage = NULL;
    edgedImage = (RGBTRIPLE **) malloc(sizeof(RGBTRIPLE *) * height);

    // Check if allocation failed
    if (edgedImage == NULL)
    {
        printf("ERROR! Could not allocate memory!\n");
        return;
    }

    for (int i = 0; i < height; i++)
    {
        edgedImage[i] = (RGBTRIPLE *) malloc(sizeof(RGBTRIPLE) * width);

        // Check if allocation failed
        if (edgedImage[i] == NULL)
        {
            printf("ERROR! Could not allocate memory!\n");

            // Free allocated memory
            for (int j = 0; j < i; j++)
                free(edgedImage[j]);
            free(edgedImage);
            return;
        }
    }

    // Update each pixel in matrix
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            xRed = 0;
            xGreen = 0;
            xBlue = 0;
            yRed = 0;
            yGreen = 0;
            yBlue = 0;

            for (int k = -1; k < 2; k++)
            {
                // Check if pixel is on the edge
                if (i + k < 0 || i + k >= height)
                    continue;

                for (int l = -1; l < 2; l++)
                {
                    // Check if pixel is on the edge
                    if (j + l < 0 || j + l >= width)
                        continue;
                    xRed += image[i + k][j + l].rgbtRed * gX[k + 1][l + 1];
                    xGreen += image[i + k][j + l].rgbtGreen * gX[k + 1][l + 1];
                    xBlue += image[i + k][j + l].rgbtBlue * gX[k + 1][l + 1];
                    yRed += image[i + k][j + l].rgbtRed * gY[k + 1][l + 1];
                    yGreen += image[i + k][j + l].rgbtGreen * gY[k + 1][l + 1];
                    yBlue += image[i + k][j + l].rgbtBlue * gY[k + 1][l + 1];
                }
            }
            xRed = (int) (sqrt((xRed * xRed) + (yRed * yRed)) + 0.5);
            edgedImage[i][j].rgbtRed = (xRed > 255) ? 255 : xRed;

            xGreen = (int) (sqrt((xGreen * xGreen) + (yGreen * yGreen)) + 0.5);
            edgedImage[i][j].rgbtGreen = (xGreen > 255) ? 255 : xGreen;

            xBlue = (int) (sqrt((xBlue * xBlue) + (yBlue * yBlue)) + 0.5);
            edgedImage[i][j].rgbtBlue = (xBlue > 255) ? 255 : xBlue;
        }
    }

    // Save values from temporary image matrix in)to original image matrix
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
            image[i][j] = edgedImage[i][j];
    }

    // Free allocated memory
    for (int i = 0; i < height; i++)
        free(edgedImage[i]);
    free(edgedImage);

    return;
}
