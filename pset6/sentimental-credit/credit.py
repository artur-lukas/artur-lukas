sum = 0
digits = 0
number = int(input("Number: "))
i = number

while (i != 0):

    if (i < 100):
        if (i > 9):
            start = i
        elif (i == 4):
            start = i

    if (digits % 2 == 1):
        j = (i % 10) * 2

        if (j > 9):
            sum += j % 10
            sum += j // 10

        else:
            sum += j
    else:
        sum += i % 10
    digits = digits + 1
    i = i // 10

Valid = (sum % 10 == 0)

if (Valid and (digits == 15) and (start == 34 or start == 37)):
    print("AMEX")
elif (Valid and (digits == 16) and (50 < start and start < 56)):
    print("MASTERCARD")
elif (Valid and (start == 4) and (digits == 13 or digits == 16)):
    print("VISA")
else:
    print("INVALID")
