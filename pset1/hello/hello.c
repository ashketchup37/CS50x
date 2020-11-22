#include <stdio.h>
#include <cs50.h>

int main(void)
{
    string name = get_string("What is your name?\n");
    //because there is no string data type in C and it is only defined in cs50 header
    //we had to include cs50 header
    printf("hello, %s\n", name);
}
