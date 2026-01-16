#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

void countLettersWordsSentences(string, int *, int *, int *);
int colemanLiauIndex(int, int, int);
void printGrade(int);

int main()
{

    string text;
    int letters = 0;
    int words = 1;
    int sentences = 0;
    int index = 0;

    // prompt user for text
    text = get_string("Text: ");

    // count number of letters, words and sentences
    countLettersWordsSentences(text, &letters, &words, &sentences);

    // compute the Coleman-Liau index
    index = colemanLiauIndex(letters, words, sentences);

    // find corresponding grade
    printGrade(index);

    return 0;
}

void countLettersWordsSentences(string text, int *letters, int *words, int *sentences)
{

    int i = 0;

    while (text[i] != '\0')
    {
        // check and increment if letter
        if (isalpha(text[i]))
        {
            (*letters)++;
        }
        // check and increment if word
        else if (isspace(text[i]))
        {
            (*words)++;
        }
        // check and increment if sentence
        else if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            (*sentences)++;
        }

        i++;
    }
}

int colemanLiauIndex(int letters, int words, int sentences)
{
    // index = 0.0588 * L - 0.296 * S - 15.8

    float l;
    float s;
    float index;

    // L => number of letters per 100 words
    l = ((float) letters / words) * 100;

    // S => number of sentences per 100 words
    s = ((float) sentences / words) * 100;

    // compute the index
    index = (0.0588 * l) - (0.296 * s) - 15.8;

    // round to the nearest whole number
    if (index >= 0)
    {
        index += 0.5;
    }
    else
    {
        index -= 0.5;
    }

    return (int) index;
}

void printGrade(int grade)
{
    if (grade >= 16)
    {
        printf("Grade 16+\n");
    }
    else if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %d\n", grade);
    }
}
