#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int checkIfAlpha(string);
int checkIfCharReapeted(string);
void getCipherText(string, string);

int main(int argc, string argv[])
{

    string plaintext;

    // CHECK KEY VALIDITY
    // check if the user has not entered a key
    if (argc != 2)
    {
        printf("Usage: ./substitution KEY\n");
        return 1;
    }
    // cehck if the key does not contain 26 characters
    else if (strlen(argv[1]) < 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    // check if the key contains non-alphabetic characters
    else if (checkIfAlpha(argv[1]))
    {
        printf("Key must only contain alphabetic characters.\n");
        return 1;
    }
    // check if any of the letters are repeated
    else if (checkIfCharReapeted(argv[1]))
    {
        printf("Key must not contain repeated characters.\n");
        return 1;
    }

    // prompt user for plaintext
    plaintext = get_string("plaintext:  ");

    // get ciphertext and store it in plaintext variable
    getCipherText(plaintext, argv[1]);

    // print ciphertext
    printf("ciphertext: %s\n", plaintext);

    return 0;
}

int checkIfAlpha(string key)
{
    // go trough each character
    for (int i = 0; i < 26; i++)
    {
        // if the character is not a letter return 1
        if (!isalpha(key[i]))
        {
            return 1;
        }
    }

    return 0;
}

int checkIfCharReapeted(string key)
{
    // capitalize all letters
    for (int i = 0; i < 26; i++)
    {
        key[i] = toupper(key[i]);
    }

    for (int i = 0; i < 25; i++)
    {
        for (int j = i + 1; j < 26; j++)
        {
            // compare letters to see if they are reapeted
            if (key[i] == key[j])
            {
                return 1;
            }
        }
    }

    return 0;
}

void getCipherText(string plaintext, string key)
{
    int length = strlen(plaintext);

    // change each letter to the corresponding cipher letter
    for (int i = 0; i < length; i++)
    {
        // if letter is uppercase
        if (isupper(plaintext[i]))
        {
            plaintext[i] = key[plaintext[i] - 'A'];
        }
        // if letter is lowercase
        else if (islower(plaintext[i]))
        {
            plaintext[i] = tolower(key[plaintext[i] - 'a']);
        }
    }
}
