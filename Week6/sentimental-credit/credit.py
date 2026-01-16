def main():

    # Propmpt user for card number
    cardNumber = input("Number: ")

    # Check if not numeric
    if not cardNumber.isnumeric():
        print("INVALID")
        return

    # Print INVALID if card not found
    if not findCard(cardNumber):
        print("INVALID")

    return


# Find corresponding card
def findCard(cardNumber):

    if not luhnAlgorithm(cardNumber):
        return False

    # Find Amrican Express
    if len(cardNumber) == 15 and cardNumber[:2] in ['34', '37']:
        print("AMEX")
        return True

    elif len(cardNumber) == 16:
        # Find Mastercard
        if int(cardNumber[:2]) in [51, 55]:
            print("MASTERCARD")
            return True

        # Find Visa
        elif cardNumber[0] == '4':
            print("VISA")
            return True

    # Find Visa
    elif len(cardNumber) == 13 and cardNumber[0] == '4':
        print("VISA")
        return True

    return False


# Calculate Luhn's algorithm
def luhnAlgorithm(cardNumber):

    sum = 0

    # Multiply every other digit by 2, starting with the second-to-last digit
    for i in range(len(cardNumber) - 2, -1, -2):
        temp = int(cardNumber[i]) * 2
        # Add the digits of the product to the sum
        sum += temp // 10 + temp % 10

    # Add other digits to the sum
    for i in range(len(cardNumber) - 1, -1, -2):
        sum += int(cardNumber[i])

    # If the last digit of the sum is not 0, return false
    if sum % 10:
        return False

    return True


main()
