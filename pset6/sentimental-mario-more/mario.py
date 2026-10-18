while (True):
    while (True):
        try:
            height = int(input("Height: "))
            break
        except ValueError:
            print("give height from range 1-8")

    if (0 < height and height < 9):
        for i in range(1, height + 1):
            for j in range(0, height - i):
                print(" ", end="")

            for j in range(0, i):
                print("#", end="")

            print("  ", end="")

            for j in range(0, i):
                print("#", end="")

            print("")
        break
    else:
        print("height range 1-8")
