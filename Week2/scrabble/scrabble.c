#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int calculatePoints(string);

int main()
{

    string word = " ";
    int firstPlayer = 0;
    int secondPlayer = 0;

    // Prompt player 1 for input
    word = get_string("Player 1: ");

    // Calculate first player points
    firstPlayer = calculatePoints(word);

    // Prompt player 2 for input
    word = get_string("Player 2: ");

    // Calculate second player points
    secondPlayer = calculatePoints(word);

    // Print the winner
    if (firstPlayer > secondPlayer)
    {
        printf("Player 1 wins!\n");
    }
    else if (firstPlayer < secondPlayer)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }

    return 0;
}

int calculatePoints(string word)
{

    // The value of each letter in alphabet from "a" to "z"
    int letterValue[] = {1, 3, 3, 2,  1, 4, 2, 4, 1, 8, 5, 1, 3,
                         1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};
    int points = 0;
    int length = strlen(word);

    // Add points for each letter in word
    for (int i = 0; i < length; i++)
    {
        // If letter is uppercase
        if (isupper(word[i]))
        {
            points += letterValue[word[i] - 'A'];
        }
        // If letter is lowercase
        else if (islower(word[i]))
        {
            points += letterValue[word[i] - 'a'];
        }
    }

    return points;
}
