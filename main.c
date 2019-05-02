//
// Created by Xufeng Weng on 2019-04-20.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int current_capacity = 20;

float* double_size(float* numbers)
{
    float* new_numbers = (float*)malloc(sizeof(float) * current_capacity * 2);
    int i;
    for (i = 0;i < current_capacity; ++i)
    {
        new_numbers[i] = numbers[i];
    }
    free(numbers);
    current_capacity *= 2;
    return new_numbers;
}

int main(int argc, char** argv) {
    if (argc != 2)
    {
        return 1;
    }

    FILE* fp = fopen(argv[1], "r");
    if (fp == NULL)
    {
        return 1;
    }
    float* numbers = (float*)malloc(sizeof(float) * current_capacity);
    int size = 0;
    float number;
    while (fscanf(fp, "%f", &number) > 0)
    {
        if (size == current_capacity)
        {
            numbers = double_size(numbers);
        }
        numbers[size] = number;
        ++size;
    }
    fclose(fp);
    free(numbers);
    int i;
    float sum = 0;
    for (i = 0;i < size; ++i)
    {
        sum += numbers[i];
    }
    float mean = sum / size;
    float stddev = 0;
    for (i = 0;i < size; ++i)
    {
        stddev += (numbers[i] - mean) * (numbers[i] - mean);
    }
    stddev = (float)sqrt(stddev / size);
    //sort and find median
    int j;
    for (i = 1;i < size; ++i)
    {
        sum = numbers[i];
        for (j = i - 1;j >= 0 && numbers[j] > sum; --j)
        {
            numbers[j + 1] = numbers[j];
        }
        numbers[j + 1] = sum;
    }
    printf("Results:\n");
    printf("--------\n");
    printf("Num values:");printf("%14d\n", size);
    printf("      mean:");printf("%14.3f\n", mean);
    float median;
    if (size % 2 == 0)
    {
        median = (numbers[size / 2 - 1] + numbers[size / 2]) / 2;
    }
    else
    {
        median = numbers[size / 2];
    }
    printf("    median:");printf("%14.3f\n", median);
    printf("    stddev:");printf("%14.3f\n", stddev);
    printf("Unused array capacity: %d\n", current_capacity - size);
    return 0;
}