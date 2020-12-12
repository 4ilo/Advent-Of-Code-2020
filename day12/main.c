#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_BUFFER_SIZE 265

#ifndef INPUT_FILE
#warning Please define INPUT_FILE on the command line
#endif

struct instruction {
    char action;
    int value;
};

int read_input_file(const char* filename, struct instruction** instructions)
{
    FILE* file;
    int counter = 0;
    struct instruction tmp = {};

    if((file = fopen(filename, "r")) == 0) {
        perror("Could not open input file\n");
        exit(1);
    }

    do {
        fscanf(file, "%c%d\n", &tmp.action, &tmp.value);

        // Get some memory and store the instruction
        *instructions = (struct instruction*) realloc(*instructions, (counter+1) * sizeof(struct instruction));
        (*instructions)[counter] = tmp;

        counter++;
    } while(!feof(file));

    fclose(file);
    return counter;
}


void forward(int* x, int* y, int direction, int value)
{
    const double rad = M_PI/180;
    int sin_y = (int) sin(direction * rad);
    int cos_x = (int) cos(direction * rad);

    *y -= sin_y * value;
    *x += cos_x * value;
}

void part1(const struct instruction* instructions, int length)
{
    int x=0, y=0;
    int direction = 0;

    for (int i=0; i<length; i++) {
        switch (instructions[i].action) {
            case 'N':
                y -= instructions[i].value;
                break;
            case 'S':
                y += instructions[i].value;
                break;
            case 'E':
                x += instructions[i].value;
                break;
            case 'W':
                x -= instructions[i].value;
                break;
            case 'L':
                direction += instructions[i].value;
                break;
            case 'R':
                direction -= instructions[i].value;
                break;
            case 'F':
                forward(&x, &y, direction, instructions[i].value);
                break;
        }
    }

    printf("Part1: %d\n", abs(x) + abs(y));
}


void rotate(int* x, int* y, int angle, int direction)
{
    int tmp = 0;
    int rotations = angle/90;

    for (int i=0; i<rotations; i++) {
        tmp = *x;
        *x = direction * (*y);
        *y = -direction * tmp;
    }
}


void part2(const struct instruction* instructions, int length)
{
    int x_s=0, y_s=0;
    int x_w=10, y_w=-1;

    for (int i=0; i<length; i++) {
        switch (instructions[i].action) {
            case 'N':
                y_w -= instructions[i].value;
                break;
            case 'S':
                y_w += instructions[i].value;
                break;
            case 'E':
                x_w += instructions[i].value;
                break;
            case 'W':
                x_w -= instructions[i].value;
                break;
            case 'L':
                rotate(&x_w, &y_w, instructions[i].value, +1);
                break;
            case 'R':
                rotate(&x_w, &y_w, instructions[i].value, -1);
                break;
            case 'F':
                x_s += x_w*instructions[i].value;
                y_s += y_w*instructions[i].value;
                break;
        }
    }

    printf("Part2: %d\n", abs(x_s) + abs(y_s));
}


int main(void)
{
    int length = 0;
    struct instruction* instructions = NULL;

    length = read_input_file(INPUT_FILE, &instructions);
    printf("Len: %d\n", length);

    part1(instructions, length);
    part2(instructions, length);

    free(instructions);

    return 0;
}
