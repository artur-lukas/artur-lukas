#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int sum = 0;
    int digits = 0;
    int start;
    long number = get_long("Number: ");

    for (long i = number; i != 0; i = i / 10)
    {
        if (i < 100)
        {
            if (i > 9)
                start = i;
            else if (i == 4)
                start = i;
        }
        if (digits % 2 == 1)
        {
            int j = (i % 10) * 2;

            if (j > 9)
            {
                sum += j % 10;
                sum += j / 10;
            }
            else
            {
                sum += j;
            }
        }
        else
        {
            sum += i % 10;
        }

        digits++;
    }
    bool Valid = (sum % 10 == 0);

    if (Valid && (digits == 15) && (start == 34 || start == 37))
        printf("AMEX\n");
    else if (Valid && (digits == 16) && (50 < start && start < 56))
        printf("MASTERCARD\n");
    else if (Valid && (start == 4) && (digits == 13 || digits == 16))
        printf("VISA\n");
    else
        printf("INVALID\n");
}
