#include <stdio.h>
#include <stdlib.h>

#include "common/utils.h"

#ifndef INPUT_FILE
#error Please define INPUT_FILE on the command line
#endif

void part1(const int* numbers, int length)
{
    for (int i=0; i<length; i++) {
        for (int j=0; j<length; j++) {
            if (i == j) {
                continue;
            }

            if (numbers[i] + numbers[j] == 2020) {
                printf("Result: %d + %d = 2020. -> %d\n", numbers[i], numbers[j], numbers[i]*numbers[j]);
                return;
            }
        }
    }
}

void part2(const int* numbers, int length)
{
    for (int i=0; i<length; i++) {
        for (int j=0; j<length; j++) {
            for (int k=0; k<length; k++) {
                if (i == j || i == k || j == k) {
                    continue;
                }

                if (numbers[i] + numbers[j] + numbers[k] == 2020) {
                    printf("Result: %d + %d + %d = 2020. -> %d\n", numbers[i], numbers[j], numbers[k], numbers[i]*numbers[j]*numbers[k]);
                    return;
                }
            }
        }
    }
}


int main(void)
{
    int* numbers = NULL;
    int length = 0;

    length = read_number_file(INPUT_FILE, &numbers);
    printf("Len: %d\n", length);

    part1(numbers, length);
    part2(numbers, length);

    free(numbers);

    return 0;
}
