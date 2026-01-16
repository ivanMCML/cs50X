def main():
    height = getHeight()
    printPyramid(height)


# Get the height of the pyramid
def getHeight():

    while True:
        # Get user input
        height = input("Height: ")

        # Check if valid input
        if height.isnumeric():
            height = int(height)

            if height in range(1, 9):
                break

    return height


# Print the pyramid
def printPyramid(height):

    for i in range(1, height + 1):
        # Print a row
        print((height - i) * " " + i * "#" + "  " + i * "#")


main()
