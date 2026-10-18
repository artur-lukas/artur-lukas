#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

char ABC[26];
int pointlist[26] = {1, 3, 3, 2,  1, 4, 2, 4, 1, 8, 5, 1, 3,
                     1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int get_points(string word1or2)
{
    int sum = 0;
    int lenght = strlen(word1or2) + 1;
    for (int i = 0; i < lenght; i++)
    {
        char letter = toupper(word1or2[i]);
        for (int j = 0; j < 26; j++)
        {
            if (letter == ABC[j])
            {
                sum += pointlist[j];
            }
        }
    }
    return sum;
}

int main(void)
{

    for (int i = 0; i < 26; i++)
    {
        ABC[i] = 'A' + i;
    }

    string word1 = get_string("Player 1:");
    string word2 = get_string("Player 2:");

    int points1 = get_points(word1);
    int points2 = get_points(word2);

    if (points1 > points2)
    {
        printf("Player 1 wins!\n");
    }
    else if (points2 > points1)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
}
