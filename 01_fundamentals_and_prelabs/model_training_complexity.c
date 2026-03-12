#include <stdio.h>

/*
    In this task, you should implement the model_complexity_calculator() function that calculates the estimated
    training time of a machine learning model considering its complexity level and dataset size.
*/

void model_complexity_calculator(char complexity_level, int dataset_size)
{
    float dataset_div_by_1000 = (dataset_size / 1000);
    float data_sec;

    switch (complexity_level)
    {
    case 'B':
        data_sec = (dataset_div_by_1000 * 0.5);
        break;
    
    case 'I':
        data_sec = (dataset_div_by_1000 * 1.0);
        break;

    case 'A':
        data_sec = (dataset_div_by_1000 * 2.5);
        break;

    case 'E':
        data_sec = (dataset_div_by_1000 * 5.0);
        break;

    case 'S':
        data_sec = (dataset_div_by_1000 * 10.0);
        break;
    }
    printf("%.2f\n", data_sec);
}

int main()
{
    
    /* WRITE YOUR CODE HERE */
    char complexity;
    int dataset_s;
    scanf("%c %d", &complexity, &dataset_s);
    model_complexity_calculator(complexity, dataset_s);


    return 0;
}