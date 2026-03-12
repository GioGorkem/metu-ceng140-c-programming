#include <stdio.h>

/*
    In this task, you should implement the alternating_sum_calculator() function that calculates the alternating sum of the digits of a given number.
*/
void alternating_sum_calculator(int N)
{
    int digit = 0;
    int i = 1;
    int sum = 0;
    while (N > 0)
    {
        digit = N % 10;
        if (i % 2 == 0) {
            sum -= digit;
        }
        else {
            sum += digit;
        }
        N = N / 10;
        i++;
    }
    if (sum > 0) 
    {
        printf("Positive alternating sum: %d\n", sum);
    }
    else if (sum < 0)
    {
        printf("Negative alternating sum: %d\n", sum);
    }
    else
    {
        printf("The alternating sum is zero.\n");
    }
}

int main()
{
    
    int number;
    scanf("%d", &number);
    alternating_sum_calculator(number);

    return 0;
}