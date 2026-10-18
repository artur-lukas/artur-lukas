#include <cs50.h>
#include <stdio.h>

int main(void)
{

    int hight = get_int("Give Hight(1-8): ") + 1;

    while (hight < 2 || hight > 9)
    {
        hight = get_int("Give Hight(1-8): ") + 1;
    }

    for (int i = 1; i < hight; i++)
    {

        for (int j = 1; hight - i > j; j++)
        {
            printf(" ");
        }

        for (int j = 0; j < i; j++)
        {
            printf("#");
        }

        printf("  ");

        for (int j = 0; j < i; j++)
        {
            printf("#");
        }
        printf("\n");
    }
}
