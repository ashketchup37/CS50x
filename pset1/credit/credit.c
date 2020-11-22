#include <cs50.h>
#include <stdio.h>
#include <string.h>




string card_type(string number);
bool check_sum(string number);




int main(void)
{
    //keeping the main function simple and beautiful
    string num = get_string("Number: ");
    printf("%s\n", card_type(num));
}




string card_type(string number)
{
    //checking if this number satisfies check_sum
    bool valid = check_sum(number);


    //if it doesn't, it is invalid right away
    if (!valid)
    {
        return "INVALID";
    }



    int len = strlen(number);



    //VISA cards length is 13 or 16.
    //VISA card's first digit is 4
    if (number[0] == '4' && (len == 13 || len == 16))
    {
        return "VISA";
    }



    //AMEX has a length of 15 and its first 2 digit is 34 or 37
    else if (number[0] == '3' && len == 15)
    {
        if (number[1] == '4' || number[1] == '7')
        {
            return "AMEX";
        }
    }



    //MASTERCARD has a length of 16
    //Its first two digit can be 51, 52, 53, 54, 55
    else if (number[0] == '5' && len == 16)
    {
        if (number[1] >= '1' && number[1] <= '5')
        {
            return "MASTERCARD";
        }
    }



    //If nothing was right, then it is Invalid
    return "INVALID";
}




bool check_sum(string number)
{
    //declaring a variable sum that tracks the summation we get after following luhn's algorithm
    //also want to know the lenth of the Card's length.
    int sum = 0, len = strlen(number);



    //In this loop I start from the right most digit
    //If it is the last digit or every other number after that, we just add it to sum
    //Otherwise I multiply with 2 and add it's digits.
    for (int i = 1; i <= len; i++)
    {


        //we start with i = 1, so in the first iteration we will get the right most digit with len - i
        //and eventually i will be equal to len and len - i will be 0, hence the first digit
        if (i % 2 == 0)
        {


            //If the number is more than 4, the 2 * number will be of two digits.
            //As we don't add the whole number in luhn's algorithm, rather the single digits.
            //I add 1 and (2 * number) - 10 to sum
            //1 is for the first digit, and 2n-10 gives the second digit.
            if ((number[len - i] - '0') < 5)
            {
                sum += 2 * (number[len - i] - '0');
            }
            else
            {
                sum += 1 + ((2 * (number[len - i] - '0')) - 10);
            }


        }
        else
        {
            //simply add that number

            sum += (number[len - i] - '0');
        }


    }



    //if the sum is divisible by 10 that it satisfies the check sum
    //otherwise, no
    if (sum % 10 == 0)
    {
        return true;
    }
    else
    {
        return false;
    }


}
