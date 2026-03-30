#include <stdio.h>
#include <math.h>

#define MAX_LAYERS 100
#define TRANSFER_RATIO 0.2

double WAVE_PRESSURE_PSI;
double pressures[MAX_LAYERS][MAX_LAYERS];

double calculate_pressure_recursive(int row, int col)
{
    if (row == 0 && col == 0)
    {
        return WAVE_PRESSURE_PSI;
    }
    else if (col >= 1 && col < row)
    {
        return calculate_pressure_recursive(row-1, col)*(TRANSFER_RATIO) + calculate_pressure_recursive(row-1, col-1)*(TRANSFER_RATIO);
    }
    else if (col == 0)
    {
        return calculate_pressure_recursive(row-1, col)*(TRANSFER_RATIO) + WAVE_PRESSURE_PSI;
    }
    else
    {
        return calculate_pressure_recursive(row-1, col-1)*(TRANSFER_RATIO) + WAVE_PRESSURE_PSI;
    }
}

double calculate_pressure_iterative(int row, int col)
{
    if (row == 0 && col == 0)
    {
        pressures[row][col] = WAVE_PRESSURE_PSI;
    }
    else if (col >= 1 && col < row)
    {
        pressures[row][col] = pressures[row-1][col]*(TRANSFER_RATIO) + pressures[row-1][col-1]*(TRANSFER_RATIO);
    }
    else if (col == 0)
    {
        pressures[row][col] = (pressures[row-1][col]*TRANSFER_RATIO + WAVE_PRESSURE_PSI);
    }
    else
    {
        pressures[row][col] = pressures[row-1][col-1]*TRANSFER_RATIO + WAVE_PRESSURE_PSI;
    }
    
    return pressures[row][col];
}

void print_pressures_on_all_plates(int num_layers, char recursive_or_iterative)
{
    int row, col;
    for (row = 0; row < num_layers; row++)
    {
        for(col = 0; col <= row; col++)
        {
            if (recursive_or_iterative == 'R')
            {
                printf("%d %d %f\n", row, col, calculate_pressure_recursive(row, col));
            }
            else if (recursive_or_iterative == 'I')
            {
                printf("%d %d %f\n", row, col, calculate_pressure_iterative(row, col));
            }
        }
    }
}

int main(void)
{
    int num_layers;
    char rec_or_ite;
    
    scanf("%lf", &WAVE_PRESSURE_PSI);
    scanf("%d", &num_layers);
    scanf(" %c", &rec_or_ite);
    
    print_pressures_on_all_plates(num_layers, rec_or_ite);

    return 0;
}