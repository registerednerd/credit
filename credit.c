#include <stdio.h>
#include <cs50.h>
#include <math.h>

string card_logo(long);
bool valid(long);
int extract_digit(long, int);
int count_digits(long);

int main(void)
{
    long cc = get_long("Number: ");
    printf("%s", card_logo(cc));
}

string card_logo(long cc)
{
    // determine if valid
    if (valid(cc))
    {
        int length = count_digits(cc);
        //get first two digits
        int firstTwo = 0;
        firstTwo += extract_digit(cc, length) * 10;
        firstTwo += extract_digit(cc, length - 1);
        //get first digit
        int firstDigit = extract_digit(cc, length);
        //check AMEX conditions
        if (length == 15 && (firstTwo == 34 || firstTwo == 37))
        {
            return ("AMEX\n");
        }
        // check 13-digit Visa conditions
        else if (length == 13 && firstDigit == 4)
        {
            return ("VISA\n");
        }
        // check for 16-digit number
        else if (length == 16)
        {
            //differentiate 16 digit Visa from MC
            if (firstTwo == 51 || firstTwo == 52 || firstTwo == 53 || 
                firstTwo == 54 || firstTwo == 55)
            {
                return ("MASTERCARD\n");
            }
            else if (firstDigit == 4)
            {
                return ("VISA\n");
            }
            else
            {
                return ("INVALID\n");
            }
        }
        else
        {
            return ("INVALID\n");
        }
    }
    else //return if invalid
    {
        return ("INVALID\n");
    }
    
    
}

bool valid(long cc)
{
    int length = count_digits(cc);
    int sum = 0;
    for (int digit = 1; digit <= length; digit++)
    {
        int activeDigit = extract_digit(cc, digit);
        // determine if digit is even or odd
        if (digit % 2 == 0)
        {
            // double the active digit
            activeDigit *= 2;
            // if doubling caused overflow, add component digits
            if (activeDigit > 9)
            {
                sum += extract_digit(activeDigit, 1);
                sum += extract_digit(activeDigit, 2);
            }
            else
            {
                sum += activeDigit;
            }
        }
        else
        {
            sum += activeDigit;
        }
    }
    if (sum % 10 == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int extract_digit(long cc, int digit)
{
    // calculate the power of 10 for the subject digit
    long currentPower = pow(10, digit);
    // calculate the power of the first digit to be removed
    long previousPower = pow(10, (digit - 1));
    // eliminate digits to the left of the subject
    long significantFigures = cc % currentPower;
    // determine the digits to the right of the subject to be removed
    long insignificantFigures = cc % previousPower;
    // subtract the digits to the right (making them zeroes)
    long activeDigit = significantFigures - insignificantFigures;
    // return the resulting single digit, with the trailing zeroes removed
    return activeDigit / previousPower;
}

// go through digits from least to most significant, and find the last non-zero digit
int count_digits(long cc)
{
    int length;
    for (int i = 1; i < 17; i++)
    {
        if (extract_digit(cc, i) != 0)
        {
            length = i;
        }
    }
    return length;
}
