#include <cs50.h>
#include <stdio.h>

void printRow(int, int);
void printLeftRow(int, int);

int main(void)
{

    int height = 0;

    // Prompt user for input
    do
    {
        height = get_int("Height:\n");
    }
    while (height < 1 || height > 8);

    // Print pyramids
    for (int i = 0; i < height; i++)
    {
        printRow(i + 1, height);
        printf("\n");
    }

    return 0;
}

void printRow(int bricks, int height)
{

    // print left part
    printLeftRow(bricks, height);

    // print middle spaces
    printf("  ");

    // print right part
    for (int i = 0; i < bricks; i++)
    {
        printf("#");
    }
}

void printLeftRow(int bricks, int height)
{

    // print blanks
    for (int i = bricks; i < height; i++)
    {
        printf(" ");
    }

    // print bricks
    for (int i = 0; i < bricks; i++)
    {
        printf("#");
    }
}
