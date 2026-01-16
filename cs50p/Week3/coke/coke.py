amount_due = 50

while True:
    print(f"Amount Due: {amount_due}")
    paid = int(input("Insert Coin: "))

    if paid in [5, 10, 25]:
        amount_due -= paid
        if amount_due <= 0:
            print(f"Change Owed: {amount_due * (-1)}")
            break
