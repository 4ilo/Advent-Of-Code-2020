#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_BUFFER_SIZE 265

#ifndef INPUT_FILE
#warning Please define INPUT_FILE on the command line
#endif

enum operation_e {JMP=0, NOP, ACC};
struct instruction {
    enum operation_e operation;
    int argument;
};

int read_input_file(const char* filename, struct instruction** program)
{
    FILE* file;
    int counter = 0;
    struct instruction tmp = {};
    char buffer[MAX_BUFFER_SIZE] = "";

    if((file = fopen(filename, "r")) == 0) {
        perror("Could not open input file\n");
        exit(1);
    }

    do {
        fscanf(file, "%s %d\n", buffer, &tmp.argument);

        if (strncmp(buffer, "nop", 3) == 0) {
            tmp.operation = NOP;
        }
        else if (strncmp(buffer, "acc", 3) == 0) {
            tmp.operation = ACC;
        }
        else if (strncmp(buffer, "jmp", 3) == 0) {
            tmp.operation = JMP;
        }

        // Get some memory and store the password
        *program = (struct instruction*) realloc(*program, (counter+1) * sizeof(struct instruction));
        (*program)[counter] = tmp;

        counter++;
    } while(!feof(file));

    fclose(file);
    return counter;
}

int run_cpu(const struct instruction* program, int length, int* accumulator)
{
    int ip = 0;
    int* executed = calloc(length, sizeof(int));

    // Reset accumulator
    *accumulator = 0;

    while (ip < length) {
        if (executed[ip] == 1) {
            free(executed);
            return 0;
        }
        executed[ip] = 1;

        switch(program[ip].operation) {
            case ACC:
                *accumulator += program[ip].argument;
                break;
            case JMP:
                ip += program[ip].argument;
                continue;
            default:
                break;
        }

        ip++;
    }

    free(executed);
    return 1;
}


void part2(const struct instruction* program, int length)
{
    int accumulator = 0;
    struct instruction* program_copy = NULL;

    for (int i=0; i<length; i++) {
        if (program[i].operation != ACC && program[i].argument != 0) {

            // Copy program
            program_copy = calloc(length, sizeof(struct instruction));
            memcpy(program_copy, program, sizeof(struct instruction) * length);

            // JMP -> NOP || NOP -> JMP
            program_copy[i].operation = !program_copy[i].operation;

            if (run_cpu(program_copy, length, &accumulator)) {
                printf("Part2: %d\n", accumulator);

                free(program_copy);
                return;
            }

            free(program_copy);
        }
    }
}


int main(void)
{
    int length = 0;
    int accumulator = 0;
    struct instruction* program = NULL;

    length = read_input_file(INPUT_FILE, &program);
    printf("Len: %d\n", length);

    // Part 1
    run_cpu(program, length, &accumulator);
    printf("Part1: %d\n", accumulator);

    part2(program, length);

    free(program);

    return 0;
}
