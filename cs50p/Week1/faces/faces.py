def main():
    # Get the input
    text = input()

    # Convert emoticons to emojis
    text = convert(text)

    # Print the result
    print(text)


# Convert emoticons to emojis
def convert(text):
    text = text.replace(":)", "🙂")
    text = text.replace(":(", "🙁")

    return text


main()
