#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>

float readability(string input);

int main(void)
{
    string input = get_string("Text: ");
    float grade = readability(input);


    if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (grade >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %d\n", (int) round(grade));
    }
    return 0;
}

float readability(string input)
{

    int length = strlen(input);

    //variable to record if a character is a part of a different word or the same word. Also for sentences.
    bool rWord = false, rSentence = false;

    int letters = 0, words = 0, sentences = 0;

    for (int i = 0; i < length; i++)
    {
        if ((input[i] >= 'a' && input[i] <= 'z') || (input[i] >= 'A' && input[i] <= 'Z'))
        {
            letters++;
            if (!rWord)
            {
                rWord = true;
            }
            if (!rSentence)
            {
                rSentence = true;
            }
        }
        else
        {
            if (input[i] == ' ')
            {
                //if there was a word, count and end it
                if (rWord)
                {
                    words++;
                    rWord = false;
                }
            }
            else if (input[i] == '.' || input[i] == '!' || input[i] == '?')
            {
                //if there was a word, count and end it
                if (rWord)
                {
                    words++;
                    rWord = false;
                }
                //if there was a sentence, count and end it
                if (rSentence)
                {
                    sentences++;
                    rSentence = false;
                }
            }
        }
    }

    //was facing problems for not converting the ints to floats

    float letter_percent = (letters * 100.0 / words);
    float sentence_percent = (sentences * 100.0 / words);
    float grade = (0.0588 * letter_percent) - (0.296 * sentence_percent) - 15.8;

    // printf("%d %d %d\n", letters, words, sentences);
    // printf("%f %f %f\n", letter_percent, sentence_percent, grade);
    return grade;
}
