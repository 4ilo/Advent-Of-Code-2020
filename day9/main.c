#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifdef EXAMPLE
#define PREAMBLE 5
#else
#define PREAMBLE 25
#endif

#include "common/utils.h"

#ifndef INPUT_FILE
#error Please define INPUT_FILE on the command line
#endif

int valid_number(const int* all_numbers, int length, int number)
{
    for (int i=0; i<length; i++) {
        for (int j=i; j<length; j++) {
            if (all_numbers[i] + all_numbers[j] == number) {
                return 1;
            }
        }
    }

    return 0;
}


int part1(const int* numbers, int length)
{
    int preamble = PREAMBLE;

    for (int i=preamble; i<length; i++) {
        if (!valid_number(&(numbers[i-preamble]), preamble, numbers[i])) {
            printf("Part 1: %d\n", numbers[i]);
            return numbers[i];
        }
    }

    return 0;
}


int find_sum(const int* numbers, int length, int target, int range, int* result)
{
    int sum = 0;

    for (int i=0; i<(length-range); i++) {
        sum = 0;
        for (int j=0; j<range; j++) {
            sum += numbers[i+j];
        }

        if (sum == target) {
            memcpy(result, &(numbers[i]), range*sizeof(int));
            return 1;
        }
    }

    return 0;
}


void part2(const int* numbers, int length, int target)
{
    int result[length];

    for (int i=2; i<length; i++) {
        if (find_sum(numbers, length, target, i, result)) {
            qsort(result, i, sizeof(int), sortFunc);
            printf("Part2: %d\n", result[0] + result[i-1]);
        }
    }
}


int main(void)
{
    int* numbers = NULL;
    int length = 0;
    int invalid_number = 0;

    length = read_number_file(INPUT_FILE, &numbers);
    printf("Len: %d\n", length);

    invalid_number = part1(numbers, length);
    part2(numbers, length, invalid_number);

    free(numbers);

    return 0;
}
