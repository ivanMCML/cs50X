#include <cs50.h>
#include <stdio.h>

int calculateChecksum(long, int *);
int findStartingDigits(long);
void findCard(long);

int main()
{
    long cardNumber = 0;

    // prompt user for input
    do
    {
        cardNumber = get_long("Credit card number: ");
    }
    while (cardNumber < 0);

    // find corresponding card
    findCard(cardNumber);

    return 0;
}

int calculateChecksum(long cardNumber, int *cardLength)
{
    int temp = 0;
    int sum = 0;

    // calculate checksum
    while (cardNumber > 0)
    {
        // multiply every other digit by 2, starting with the second-to-last digit
        if ((*cardLength) % 2)
        {
            temp = cardNumber % 10;
            temp *= 2;

            // add to sum
            sum += (temp / 10 + temp % 10);
        }
        else
        {
            // add digit to sum
            sum += cardNumber % 10;
        }

        // find card length
        (*cardLength)++;

        // go to next last digit
        cardNumber /= 10;
    }

    return sum;
}

int findStartingDigits(long cardNumber)
{
    int firstTwo = 0;

    // while the number is two-digit
    while (cardNumber > 9)
    {
        firstTwo = cardNumber % 100;
        cardNumber /= 10;
    }

    return firstTwo;
}

void findCard(long cardNumber)
{

    int cardLength = 0;
    int startingDigits = 0;

    // check if checksum number is valid
    if (!(calculateChecksum(cardNumber, &cardLength) % 10))
    {
        // first two digits of card number
        startingDigits = findStartingDigits(cardNumber);

        // find American Express
        if (cardLength == 15)
        {
            if (startingDigits == 34 || startingDigits == 37)
            {
                printf("AMEX\n");
            }
            else
            {
                // invalid card number flag
                startingDigits = 0;
            }
        }
        // find MasterCard or 16 digit Visa
        else if (cardLength == 16)
        {
            // MasterCard
            if (startingDigits > 50 && startingDigits < 56)
            {
                printf("MASTERCARD\n");
            }
            // Visa
            else if (startingDigits / 10 == 4)
            {
                printf("VISA\n");
            }
            else
            {
                // invalid card number flag
                startingDigits = 0;
            }
        }
        // find Visa
        else if (cardLength == 13)
        {
            if (startingDigits / 10 == 4)
            {
                printf("VISA\n");
            }
            else
            {
                // invalid card number flag
                startingDigits = 0;
            }
        }
        else
        {
            // invalid card number flag
            startingDigits = 0;
        }
    }

    if (!startingDigits)
    {
        printf("INVALID\n");
    }
}
