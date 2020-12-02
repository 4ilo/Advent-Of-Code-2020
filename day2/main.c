#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common/utils.h"

#define MAX_BUFFER_SIZE 265

#ifndef INPUT_FILE
#warning Please define INPUT_FILE on the command line
#endif

struct password_record {
    int min;
    int max;
    char letter;
    char* password;
    int password_len;
};

int read_passwords_file(const char* filename, struct password_record** passwords)
{
    FILE* file;
    int counter = 0;
    struct password_record temp = {};
    struct password_record* pwptr = NULL;
    char buffer[MAX_BUFFER_SIZE] = "";

    if((file = fopen(filename, "r")) == 0) {
        perror("Could not open input file\n");
        exit(1);
    }

    do {
        fscanf(file, "%d-%d %c: %s\n", &temp.min, &temp.max, &temp.letter, buffer);
        counter++;

        // Get some memory and store the password
        *passwords = (struct password_record*) realloc(*passwords, counter * sizeof(struct password_record));

        // Create pointer to the current password
        pwptr = &(*passwords)[counter-1];
        memcpy(pwptr, &temp, sizeof(struct password_record));

        pwptr->password_len = strnlen(buffer, MAX_BUFFER_SIZE);

        pwptr->password = calloc(pwptr->password_len, sizeof(char));
        strncpy(pwptr->password, buffer, pwptr->password_len);

    } while(!feof(file));

    fclose(file);
    return counter;
}


void release(struct password_record** passwords, int length)
{
    for (int i=0; i<length; i++) {
        free((*passwords)[i].password);
        (*passwords)[i].password = NULL;
    }

    free(*passwords);
}


void part1(const struct password_record* passwords, int length)
{
    int counter = 0;
    int correct_passwords = 0;

    for (int i=0; i<length; i++) {
        counter = 0;
        for (int j=0; j<passwords[i].password_len; j++) {
            if (passwords[i].password[j] == passwords[i].letter) {
                counter++;
            }
        }

        if (counter >= passwords[i].min && counter <= passwords[i].max) {
            correct_passwords++;
        }
    }

    printf("Correct passwords: %d\n", correct_passwords);
}


void part2(const struct password_record* passwords, int length)
{
    int correct_passwords = 0;

    for (int i=0; i<length; i++) {
        if (!(passwords[i].password[passwords[i].min - 1] == passwords[i].letter) !=
            !(passwords[i].password[passwords[i].max - 1] == passwords[i].letter)) {
            correct_passwords++;
        }
    }

    printf("Correct passwords: %d\n", correct_passwords);
}


int main(void)
{
    struct password_record* passwords = NULL;
    int length = 0;

    length = read_passwords_file(INPUT_FILE, &passwords);
    printf("Len: %d\n", length);

    part1(passwords, length);
    part2(passwords, length);

    release(&passwords, length);

    return 0;
}
