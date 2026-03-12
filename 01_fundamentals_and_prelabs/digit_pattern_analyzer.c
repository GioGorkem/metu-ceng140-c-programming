#include <stdio.h>
#include <stdlib.h>
void digit_pattern_analyzer(int N)
{
    int max_digit = 0;
    int helper_digit;
    int digit1;
    int digit2;
    int N_back;
    int state = 0;
    int total_difference = 0;

    if (N < 0)
    {
        N = -N;
    }
    digit1 = (N%10);
    N_back = N;

    while (N_back > 0)
    {
        helper_digit = N_back % 10;
        if (helper_digit > max_digit)
        {
            max_digit = helper_digit;
        }
        N_back = N_back / 10;
    }
    N = N /10;
    while (N > 0)
    {
        digit2 = N % 10;
        total_difference += abs(digit2 - digit1);
        digit1 = digit2;
        N = N/10;

    }
    if (total_difference > max_digit) 
        {
            state = 1;
        }
    
    switch (state)
    {
    case 1:
        printf("The max digit is: %d\n", max_digit);
        printf("Total difference: %d\n", total_difference);
        printf("Status: Volatile\n");
        break;
    
    default:
        printf("The max digit is: %d\n", max_digit);
        printf("Total difference: %d\n", total_difference);
        printf("Status: Stable\n");
        break;
    }
}




int main()
{
    int number = 0;
    scanf("%d", &number);
    digit_pattern_analyzer(number);


    return 0;
}