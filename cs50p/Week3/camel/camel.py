variable_name = input("camelCase: ").strip()

for letter in variable_name:
    if letter.isupper():
        variable_name = variable_name.replace(letter, "_" + letter.lower())

print(f"snake_case: {variable_name}")
