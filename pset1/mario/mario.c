#include <stdio.h>
#include <cs50.h>

int main()
{
    int height;
    do
    {
        //asking for a height
        height = get_int("Height: ");
    }
    while (height > 8 || height < 1); //checking if it is between 1 and 8

    for (int i = 0; i < height; i++)
    {
        //adding the spaces before
        //the number of spaces in a given line is:
        //total height - line number
        for (int j = height - 1 - i; j > 0; j--)
        {
            printf(" ");
        }

        //printing the #s
        //number of # is equal line number
        for (int j = i + 1; j > 0; j--)
        {
            printf("#");
        }

        //printing two spaces
        printf("  ");

        //printing the second pyramid
        for (int j = i + 1; j > 0; j--)
        {
            printf("#");
        }

        //printing new line
        printf("\n");
    }

}
