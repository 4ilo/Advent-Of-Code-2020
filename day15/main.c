#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_BUFFER_SIZE 265

#ifndef INPUT_FILE
#warning Please define INPUT_FILE on the command line
#endif

int read_input_file(const char* filename, int** numbers)
{
    FILE* file;
    int tmp = 0;
    int counter = 0;

    if((file = fopen(filename, "r")) == 0) {
        perror("Could not open input file\n");
        exit(1);
    }

    do {
        fscanf(file, "%d%*c\n", &tmp);

        // Get some memory and store the instruction
        *numbers = (int*) realloc(*numbers, (counter+1) * sizeof(int));
        (*numbers)[counter] = tmp;

        counter++;
    } while(!feof(file));

    fclose(file);
    return counter;
}


void solution(const int* numbers, int length, int limit)
{
    int* map = NULL;
    int next = 0;
    int last = numbers[0];

    if ((map = (int*) calloc(limit, sizeof(int))) == NULL) {
        perror("Could not allocate memory.\n");
        exit(1);
    }

    for (int i=0; i<length; i++) {
        map[last] = i;
        last = numbers[i];
    }

    for (int counter=length; counter<limit; counter++) {
        if (map[last] == 0) {
            map[last] = counter;
            next = 0;
        }
        else {
            next = counter-map[last];
            map[last] = counter;
        }

        last = next;
    }

    printf("Last number: %d\n", last);
    free(map);
}


int main(void)
{
    int length = 0;
    int* numbers = NULL;

    length = read_input_file(INPUT_FILE, &numbers);
    printf("Len: %d\n", length);

    solution(numbers, length, 2020);
    solution(numbers, length, 30000000);

    free(numbers);

    return 0;
}
