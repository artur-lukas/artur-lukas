#include <cs50.h>
#include <stdio.h>

int main(void)
{
    string name = get_string("What's ur name?: ");
    printf("Hello, %s\n", name);
}
