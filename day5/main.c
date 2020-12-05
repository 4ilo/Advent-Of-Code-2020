#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_BUFFER_SIZE 265

#ifndef INPUT_FILE
#warning Please define INPUT_FILE on the command line
#endif

int read_input_file(const char* filename, char*** seats, int width)
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

        // Get some memory and store the password
        *seats = (char**) realloc(*seats, (counter+1) * sizeof(char*));
        (*seats)[counter] = (char*) calloc(width, sizeof(char));
        strncpy((*seats)[counter], buffer, width);

        counter++;
    } while(!feof(file));

    fclose(file);
    return counter;
}

int find_row(const char* seat, char letter, int length)
{
    int min = 0;
    int max = (int) pow(2, length);

    for (int j=0; j<length; j++) {
        if (seat[j] == letter) {
            max -= ((max-min)/2);
        }
        else {
            min += ((max-min)/2);
        }
    }

    return min;
}


int part1(char** seats, int length, int* ids)
{
    int highest = 0;
    int lowest = 10000;

    for (int i=0; i<length; i++) {
        int x = find_row(seats[i], 'F', 7);
        int y = find_row(seats[i]+7, 'L', 3);
        ids[i] = x*8+y;

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


int sortFunc(const void* a, const void* b)
{
    return *(int*)a - *(int*)b;
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


void release(char*** seats, int length)
{
    for (int i=0; i<length; i++) {
        free((*seats)[i]);
    }

    free(*seats);
}


int main(void)
{
    char** seats = NULL;
    int* ids = NULL;
    int length = 0;
    int width = 10;
    int lowest = 0;

    length = read_input_file(INPUT_FILE, &seats, width);
    printf("Len: %d, Width: %d\n", length, width);

    // Get some memory to store the seat_ids
    ids = (int*) calloc(length, sizeof(int));

    lowest = part1(seats, length, ids);
    part2(ids, length, lowest);

    release(&seats, length);
    free(ids);

    return 0;
}
