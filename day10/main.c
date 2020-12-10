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

void part1(const int* numbers, int length)
{
    int out = 0;
    int diff_1 = 0;
    int diff_3 = 1;         // The last diff is always 3

    for (int i=0; i<length; i++) {
        if (numbers[i] <= out+3) {
            if (numbers[i] - out == 1) {
                diff_1++;
            }
            if (numbers[i] - out == 3) {
                diff_3++;
            }

            out = numbers[i];
        }
    }

    printf("%d, %d\n", diff_1,diff_3);
    printf("Part 1: %d\n", diff_1*diff_3);
}

long find(int* map, long* cache, int i, int max)
{
    long result = 0;

    if(cache[i]) {
        return cache[i];
    }

    if (map[i] == max) {
        cache[i] = 1;
        return 1;
    }

    for(int k = 1; k <= 3; k++){
        if(!map[i + k]) {
            continue;
        }
        result += find(map, cache, i + k, max);
    }

    cache[i] = result;

    return result;
}

void part2(const int* numbers, int length)
{
    int max = 0;
    int* map = NULL;
    long* cache = NULL;
    long result = 0;

    max = numbers[length-1];

    map = calloc(max + 3, sizeof(int));
    cache = calloc(max + 3, sizeof(long));

    for (int j=0; j<=length; j++) {
        map[numbers[j]] = numbers[j];
    }

    result = find(map, cache, 0, max);
    printf("Part2: %ld\n", result);
}

int main(void)
{
    int* numbers = NULL;
    int length = 0;

    length = read_number_file(INPUT_FILE, &numbers);
    printf("Len: %d\n", length);

    qsort(numbers, length, sizeof(int), sortFunc);

    part1(numbers, length);

    numbers = realloc(numbers, (length+1)*sizeof(int));
    part2(numbers, length);

    free(numbers);

    return 0;
}
