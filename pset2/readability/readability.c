#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    string Text = get_string("Text: ");

    int lenght = strlen(Text) + 1;

    float letters = 0;

    float words = 1;

    float senten = 0;

    for (int i = 0; i < lenght; i++)
    {
        if ('A' <= toupper(Text[i]) && toupper(Text[i]) <= 'Z')
            letters++;

        else if (' ' == Text[i])
            words++;

        else if ('.' == Text[i] || Text[i] == '!' || Text[i] == '?')
            senten++;
    }

    int index = round(0.0588 * (letters / words * 100) - 0.296 * (senten / words * 100) - 15.8);

    if (index < 1)
        printf("Before Grade 1\n");

    else if (0 < index && index < 17)
        printf("Grade %i\n", index);

    else
        printf("Grade 16+\n");
}
