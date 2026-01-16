text = input("Input: ")

for letter in ["a", "e", "i", "o", "u", "A", "E", "I", "O", "U"]:
    text = text.replace(letter, "")

print(f"Output: {text}")
