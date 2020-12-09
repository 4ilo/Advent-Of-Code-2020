#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "common/utils.h"

#define MAX_BUFFER_SIZE 265

#ifndef INPUT_FILE
#warning Please define INPUT_FILE on the command line
#endif

int str_2_bin(const char* buffer)
{
    int number = 0;

    for (int i=0; i<10; i++) {
        if (buffer[i] == 'B' || buffer[i] == 'R') {
            number |= (1 << (9- i));
        }
    }

    return number;
}

int read_input_file(const char* filename, int** ids)
{
    FILE* file;
    int counter = 0;
    char buffer[MAX_BUFFER_SIZE] = "";

    if((file = fopen(filename, "r")) == 0) {
        perror("Could not open input file\n");
        exit(1);
    }

    do {
        fscanf(file, "%s\n", buffer);

        int id = str_2_bin(buffer);

        // Get some memory and store the password
        *ids = (int*) realloc(*ids, (counter+1) * sizeof(int));
        (*ids)[counter] = id;

        counter++;
    } while(!feof(file));

    fclose(file);
    return counter;
}

int part1(int* ids, int length)
{
    int highest = 0;
    int lowest = 10000;

    for (int i=0; i<length; i++) {
        if (ids[i] > highest) {
            highest = ids[i];
        }

        if (ids[i] < lowest) {
            lowest = ids[i];
        }
    }

    printf("Highest id: %d\n", highest);

    return lowest;
}


void part2(int* ids, int length, int lowest)
{
    qsort(ids, length, sizeof(int), sortFunc);

    int counter = lowest+1;

    for (int i=1; i<length-1; i++) {
        if (ids[i-1] == counter-1 && ids[i] == counter+1) {
            printf("My seat: %d\n", counter);
            return;
        }

        counter++;
    }
}


int main(void)
{
    int* ids = NULL;
    int length = 0;
    int lowest = 0;

    length = read_input_file(INPUT_FILE, &ids);
    printf("Len: %d\n", length);

    lowest = part1(ids, length);
    part2(ids, length, lowest);

    free(ids);

    return 0;
}
