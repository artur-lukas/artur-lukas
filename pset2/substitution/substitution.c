#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

char ABC[26];

char abc[26];

string key;

char get_keychar(char a)
{
    if ('A' <= a && a <= 'Z')
    {
        for (int i = 0; i < 26; i++)
        {
            if (a == ABC[i])
            {
                a = toupper(key[i]);
                return a;
            }
        }
    }
    if ('a' <= a && a <= 'z')
    {
        for (int i = 0; i < 26; i++)
        {
            if (a == abc[i])
            {
                a = tolower(key[i]);
                return a;
            }
        }
    }
    return a;
}

int main(int x, string Key[])
{

    if (x != 2)
    {
        printf("Key?!?\n");
        return 1;
    }

    key = Key[1];

    int lenght_key = strlen(key);

    if (lenght_key != 26)
    {
        printf("Key must containing 26 characters!\n");
        return 1;
    }

    for (int i = 0; i < 26; i++)
    {
        if (!('A' <= toupper(key[i]) && toupper(key[i]) <= 'Z'))
        {
            printf("not valid charakter\n");
            return 1;
        }
    }

    for (int i = 0; i < 26; i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (toupper(key[i]) == toupper(key[j]))
            {
                printf("double charakter\n");
                return 1;
            }
        }
    }

    for (int i = 0; i < 26; i++)
        ABC[i] = 'A' + i;

    for (int i = 0; i < 26; i++)
        abc[i] = 'a' + i;

    string Text = get_string("Text: ");

    int lenght_Text = strlen(Text);

    for (int i = 0; i < lenght_Text; i++)
    {
        Text[i] = get_keychar(Text[i]);
    }

    printf("ciphertext: %s\n", Text);
}
