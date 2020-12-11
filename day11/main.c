#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "common/utils.h"

#ifndef INPUT_FILE
#error Please define INPUT_FILE on the command line
#endif

#ifdef EXAMPLE
#define SIZE 10
#else
#define SIZE 98
#endif

enum tile_t {FLOOR, EMPTY, FULL};

int read_input_file(const char* filename, enum tile_t map[SIZE][SIZE])
{
    FILE* file;
    int counter = 0;
    char tmp = 0;
    enum tile_t tmp_value = 0;

    if((file = fopen(filename, "r")) == 0) {
        perror("Could not open input file\n");
        exit(1);
    }

    int width = 0;

    do {
        fscanf(file, "%c", &tmp);

        switch (tmp) {
            default:
                counter++;
                width = 0;
                continue;
            case '.':
                tmp_value = FLOOR;
                break;
            case 'L':
                tmp_value = EMPTY;
                break;
            case '#':
                tmp_value = FULL;
                break;
        }

        map[counter][width] = tmp_value;
        width++;

    } while(!feof(file));


    fclose(file);
    return counter;
}

int get_neighbours(enum tile_t map[SIZE][SIZE], int x, int y)
{
    const int move_x[] = {1, 0, -1,  0, 1, -1,  1, -1};
    const int move_y[] = {0, 1,  0, -1, 1, -1, -1,  1};

    int neighbours = 0;

    for (int i=0; i<8; i++) {
        if (x + move_x[i] >= 0 && x + move_x[i] < SIZE && y + move_y[i] >= 0 && y + move_y[i] < SIZE) {
            if (map[y+move_y[i]][x+move_x[i]] == FULL) {
                neighbours++;
            }
        }
    }

    return neighbours;
}

int iter(enum tile_t map[SIZE][SIZE], enum tile_t output[SIZE][SIZE], int length)
{
    int changed = 0;
    int neighbours = 0;

    for (int y=0; y<length; y++) {
        for (int x=0; x<length; x++) {
            neighbours = get_neighbours(map, x, y);

            if (neighbours == 0 && map[y][x] == EMPTY) {
                output[y][x] = FULL;
                changed++;
            }

            if (neighbours >= 4 && map[y][x] == FULL) {
                output[y][x] = EMPTY;
                changed++;
            }
        }
    }

    //for (int y=0; y<length; y++) {
    //    for (int x=0; x<length; x++) {
    //        printf("%d", output[y][x]);
    //    }
    //    printf("\n");
    //}
    //printf("changed: %d\n", changed);

    return changed;
}

void part1(enum tile_t map[SIZE][SIZE], int length)
{
    int counter = 0;
    enum tile_t input[SIZE][SIZE] = {};
    enum tile_t output[SIZE][SIZE] = {};

    memcpy(input, map, SIZE*SIZE*sizeof(enum tile_t));

    while(iter(input, output, length)) {
        memcpy(input, output, SIZE*SIZE*sizeof(enum tile_t));
        counter++;
    }

    printf("Rounds: %d\n", counter);

    counter = 0;
    for (int y=0; y<length; y++) {
        for (int x=0; x<length; x++) {
            if (output[y][x] == FULL) {
                counter++;
            }
        }
    }

    printf("Part 1: %d\n", counter);
}

int main(void)
{
    enum tile_t map[SIZE][SIZE] = {};
    int length = 0;

    length = read_input_file(INPUT_FILE, map);
    printf("Len: %d\n", length);

    part1(map, SIZE);

    //free(numbers);

    return 0;
}
