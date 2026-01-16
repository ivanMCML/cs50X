x, y, z = input("Expression: ").strip().split(" ")

match y:
    case "+":
        print(f"{(int(x) + int(z)):.1f}")
    case "-":
        print(f"{(int(x) - int(z)):.1f}")
    case "*":
        print(f"{(int(x) * int(z)):.1f}")
    case "/":
        print(f"{(int(x) / int(z)):.1f}")
