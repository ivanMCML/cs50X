#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define JPG_BLOCK_SIZE 512

int main(int argc, char *argv[])
{
    FILE *memoryCard = NULL;

    // Check if there is only one command-line argument
    if (argc != 2)
    {
        printf("Usage: ./recover FILE\n");
        return 1;
    }

    // Open memory card
    memoryCard = fopen(argv[1], "r");

    // Check if memory card is opened successfully
    if (memoryCard == NULL)
    {
        printf("Failed to open %s\n", argv[1]);
        return 1;
    }

    // Create a buffer for a block of data
    uint8_t buffer[JPG_BLOCK_SIZE];

    // Number of found images
    int imageCounter = 0;

    // Name of .jpg file
    char fileName[8] = " ";

    FILE *outFile = NULL;

    // Read through memory card while there is still data left
    while (fread(buffer, sizeof(uint8_t), JPG_BLOCK_SIZE, memoryCard) == JPG_BLOCK_SIZE)
    {
        // Look for JPEG starting bits
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff)
        {
            if ((buffer[3] & 0xf0) == 0xe0)
            {
                // Close the previous .jpg file
                if (imageCounter)
                    fclose(outFile);

                // Create a new .jpg file name
                sprintf(fileName, "%03i.jpg", imageCounter);
                imageCounter++;

                // Open a new .jpg file
                outFile = fopen(fileName, "w");
                if (outFile == NULL)
                {
                    printf("Failed to open %s\n", fileName);
                    return 1;
                }
            }
        }
        // Write data to the file
        if (imageCounter)
            fwrite(buffer, sizeof(uint8_t), JPG_BLOCK_SIZE, outFile);
    }

    // Close the last .jpg file
    if (imageCounter)
        fclose(outFile);

    // Close memory card
    fclose(memoryCard);

    return 0;
}
