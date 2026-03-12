#include <stdio.h>

int main()
{
    int N;
    int pre_number;
    int current_number;
    int total = 0;
    int sum_modulo;
    int multiplier = 1;
    int new_number = 0;
    scanf("%d", &N);
    printf("Initial number: %d\n", N);
    pre_number = N % 10;
    N = N / 10;

    while (N > 0)
    {
        current_number = N % 10;
        sum_modulo = (pre_number + current_number) % 10;
        new_number += sum_modulo * multiplier;
        pre_number = current_number;
        multiplier *= 10;
        
        N = N / 10;
        
        if (N == 0)
        {
            total++;
            if (new_number < 10)
            {   
                printf("Step %d: %d\n", total, new_number);
                printf("Final digit: %d\n", new_number);
                break;
            }
            else
            { 
                
                N = new_number;
                multiplier = 1;
                printf("Step %d: %d\n", total, N);
                new_number = 0;
                pre_number = N % 10;
                N = N / 10;
                
            }
        }
        

    }
    printf("Total Steps: %d\n", total);
    return 0;
}