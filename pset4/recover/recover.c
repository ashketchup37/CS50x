#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    // Declares a Buffer
    BYTE data[520];

    // Opening the card from where I'll read data
    FILE *inp = fopen(argv[1], "r");

    // Declaring the output file pointer
    FILE *img;

    // I'll need 8 characters to represent the file name, so taking one more to be extra safe
    char filename[9];

    // Picture Counter
    int count = 0;

    // Flag to know if we're already reading or not.
    int reading = 0;

    while (1)
    {
        // fread returns the number of bytes we were able to read. If it is less than 512, it means we have reached the end
        int num = fread(data, 1, 512, inp);
        if (num != 512)
        {
            // If we have reached the end, copy these last data, close the file and break the loop.
            fwrite(data, 1, num, img);
            fclose(img);
            break;
        }

        if (data[0] == 0xff && data[1] == 0xd8 && data[2] == 0xff && (data[3] & 0xf0) == 0xe0)
        {
            // If we see start of a new file, we:
            //          1) Close the previous file, if we are already reading
            //          2) Make the reading flag True, if we were not reading
            if (reading)
            {
                fclose(img);
            }
            else
            {
                reading = 1;
            }

            // Start of a new file.
            sprintf(filename, "%03i.jpg", count);
            count++;
            img = fopen(filename, "w");
        }

        // If we are already reading, and this chunck doesn't have the header, we add to the previous file.
        if (reading)
        {
            fwrite(data, 1, 512, img);
        }


    }

    return 0;
}

/*
    About this program:
    I am very proud of this program.
    Before this pset, every program had some supporting code already given.
    But in this pset, I wrote this program from scratch. And didn't look anyone else's code.
    I took help from the Course material(Walkthrough and Pseudocode, but no direct code) and from the internet. Googled about those functions that I didn't understand,
    about how to do a specific job. But at the end of the day, I had to combine all of those ideas together. No one spoon fed me.
*/
