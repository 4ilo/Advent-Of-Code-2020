#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common/utils.h"

#define MAX_BUFFER_SIZE 265

#ifndef INPUT_FILE
#warning Please define INPUT_FILE on the command line
#endif

int read_input_file(const char* filename, char*** map, int* width)
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

        *width = strnlen(buffer, MAX_BUFFER_SIZE);

        // Get some memory and store the password
        *map = (char**) realloc(*map, (counter+1) * sizeof(char*));
        (*map)[counter] = (char*) calloc(*width, sizeof(char));
        strncpy((*map)[counter], buffer, *width);

        counter++;
    } while(!feof(file));

    fclose(file);
    return counter;
}

int check_slope(char** map, int height, int width, int offset_x, int offset_y)
{
    int y=0, x=0;
    int trees = 0;

    while(y < height) {
        if (map[y][x % width] == '#') {
            trees++;
        }

        x += offset_x;
        y += offset_y;
    }

    return trees;
}

void release(char*** map, int length)
{
    for (int i=0; i<length; i++) {
        free((*map)[i]);
    }

    free(*map);
}


int main(void)
{
    char** map = NULL;
    int length = 0;
    int width = 0;

    length = read_input_file(INPUT_FILE, &map, &width);
    printf("Len: %d, Width: %d\n", length, width);

    // Part 1
    int trees = check_slope(map, length, width, 3, 1);
    printf("Part 1: %d\n", trees);

    // Part 2
    // Result doesn't fit inside int -.-. Took way to long to realize
    long result = 1;
    result *= check_slope(map, length, width, 1, 1);
    result *= check_slope(map, length, width, 3, 1);
    result *= check_slope(map, length, width, 5, 1);
    result *= check_slope(map, length, width, 7, 1);
    result *= check_slope(map, length, width, 1, 2);

    printf("Part 2: %ld\n", result);

    release(&map, length);

    return 0;
}
