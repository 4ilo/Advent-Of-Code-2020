#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

int read_number_file(const char* filename, int** numbers)
{
    FILE* file;
    int counter = 0;
    int temp = 0;

    if((file = fopen(filename, "r")) == 0) {
        perror("Could not open input file\n");
        exit(1);
    }

    do {
        fscanf(file, "%d", &temp);
        counter++;

        // Get some memory and store the number
        *numbers = (int*) realloc(*numbers, counter * sizeof(int));
        (*numbers)[counter-1] = temp;

    } while(getc(file) != EOF);

    fclose(file);
    return counter - 1;
}


int sortFunc(const void* a, const void* b)
{
    return *(int*)a - *(int*)b;
}
