Text = input("Text: ")
lenght = len(Text)
letters = 0
words = 1
senten = 0
i = 0
while (i < lenght):
    if ('A' <= (Text[i].upper()) and (Text[i]).upper() <= 'Z'):
        letters += 1

    elif (' ' == Text[i]):
        words += 1

    elif ('.' == Text[i] or Text[i] == '!' or Text[i] == '?'):
        senten += 1
    i += 1

index = round(0.0588 * (letters / words * 100) - 0.296 * (senten / words * 100) - 15.8)

if (index < 1):
    print("Before Grade 1")

elif (0 < index and index < 17):
    print("Grade " + str(index))

else:
    print("Grade 16+")
