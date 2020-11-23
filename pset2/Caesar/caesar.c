#include <stdio.h>
#include <cs50.h>
#include <string.h>

int main(int argc, string argv[])
{
    int key = 0;
    //If command line gives us zero argument, or more than 2 argument...
    //this condition block will filter it.
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    else
    {
        //now we are sure that there is valid number of commands
        int n = strlen(argv[1]);

        //so we have to retrieve the key from this string
        //also we will look if that string is a number or not.
        for (int i = n - 1, x = 1; i >= 0; i--, x *= 10)
        {
            if (argv[1][i] >= '0' && argv[1][i] <= '9')
            {
                key += ((argv[1][i] - '0') * x);
            }
            else
            {
                printf("Usage: ./caesar key\n");
                return 1;
            }
        }
    }

    string inp = get_string("plaintext: ");
    printf("ciphertext: ");
    for (int i = 0, n = strlen(inp); i < n; i++)
    {
        //tried to use, ci = (pi + key) % 26
        //But it doesn't work that way
        //had to take the char to 0 first.
        char s;
        if (inp[i] >= 'a' && inp[i] <= 'z')
        {
            s = (inp[i] - 'a' + key) % 26;
            s += 'a';
        }
        else if (inp[i] >= 'A' && inp[i] <= 'Z')
        {
            s = (inp[i] - 'A' + key) % 26;
            s += 'A';
        }
        else
        {
            s = inp[i];
        }
        printf("%c", s);
    }
    printf("\n");
}
