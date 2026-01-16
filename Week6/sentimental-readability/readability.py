def main():

    # Prompt user for text
    text = input("Text: ")

    # Compute the Coleman-Liau Index
    grade = colemanLiauIndex(text)

    # Print grade
    printGrade(grade)


def colemanLiauIndex(text):

    letters = 0
    words = 1
    sentences = 0

    # Calculate number of letters, words and sentences
    for char in text:
        if char.isalpha():
            letters += 1
        elif char.isspace():
            words += 1
        elif char == '.' or char == '!' or char == '?':
            sentences += 1

    if text[len(text) - 1] == ' ':
        words -= 1

    # Compute the Coleman-Liau Index
    return 5.88 * (letters / words) - 29.6 * (sentences / words) - 15.8


# Print grade
def printGrade(grade):

    if grade > 16:
        print("Grade 16+")
    elif grade < 1:
        print("Before Grade 1")
    else:
        print("Grade", int(grade + 0.5))


main()
