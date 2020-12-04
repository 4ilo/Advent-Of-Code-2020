#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common/utils.h"
#include "day4/main.h"

#define MAX_BUFFER_SIZE 265

#ifndef INPUT_FILE
#warning Please define INPUT_FILE on the command line
#endif

void fill_field(const char* buffer, struct password_record* password)
{
    // ecl
    if (strncmp(buffer, "ecl", 3) == 0) {
        strncpy(password->ecl, buffer+4, FIELD_LEN-4);
    }
    // byr
    if (strncmp(buffer, "byr", 3) == 0) {
        strncpy(password->byr, buffer+4, FIELD_LEN-4);
    }
    // cid
    if (strncmp(buffer, "cid", 3) == 0) {
        strncpy(password->cid, buffer+4, FIELD_LEN-4);
    }
    // eyr
    if (strncmp(buffer, "eyr", 3) == 0) {
        strncpy(password->eyr, buffer+4, FIELD_LEN-4);
    }
    // hcl
    if (strncmp(buffer, "hcl", 3) == 0) {
        strncpy(password->hcl, buffer+4, FIELD_LEN-4);
    }
    // hgt
    if (strncmp(buffer, "hgt", 3) == 0) {
        strncpy(password->hgt, buffer+4, FIELD_LEN-4);
    }
    // iyr
    if (strncmp(buffer, "iyr", 3) == 0) {
        strncpy(password->iyr, buffer+4, FIELD_LEN-4);
    }
    // pid
    if (strncmp(buffer, "pid", 3) == 0) {
        strncpy(password->pid, buffer+4, FIELD_LEN-4);
    }
}

int read_passwords_file(const char* filename, struct password_record** passwords)
{
    FILE* file;
    int counter = 0;
    char c1, c2;
    int new_pass = 0;
    struct password_record temp = {};
    struct password_record* pwptr = NULL;
    char buffer[MAX_BUFFER_SIZE] = "";

    (void) passwords;

    if((file = fopen(filename, "r")) == 0) {
        perror("Could not open input file\n");
        exit(1);
    }

    do {
        fscanf(file, "%s", buffer);

        fill_field(buffer, &temp);

        c1 = fgetc(file);
        if (c1 == '\n') {
            c2 = fgetc(file);
            if (c2 == '\n' || c2 == EOF) {
                new_pass = 1;
            }
            else {
                ungetc(c2, file);
            }
        }
        else {
            ungetc(c1, file);
        }

        if (new_pass) {
            new_pass = 0;
            counter++;

            // Get some memory and store the password
            *passwords = (struct password_record*) realloc(*passwords, counter * sizeof(struct password_record));
            pwptr = &(*passwords)[counter - 1];

            // Store data
            memcpy(pwptr, &temp, sizeof(struct password_record));

            // Clear temp pointer
            memset(&temp, 0, sizeof(struct password_record));
        }

    } while(!feof(file));

    fclose(file);
    return counter;
}

void part1(const struct password_record* passwords, int length)
{
    int valid_passwords = 0;
    int byr, ecl, eyr, hcl, hgt, iyr, pid = 0;

    for (int i=0; i<length; i++) {
        byr = strnlen(passwords[i].byr, FIELD_LEN);
        ecl = strnlen(passwords[i].ecl, FIELD_LEN);
        eyr = strnlen(passwords[i].eyr, FIELD_LEN);
        hcl = strnlen(passwords[i].hcl, FIELD_LEN);
        hgt = strnlen(passwords[i].hgt, FIELD_LEN);
        iyr = strnlen(passwords[i].iyr, FIELD_LEN);
        pid = strnlen(passwords[i].pid, FIELD_LEN);

        if (byr && ecl &&eyr && hcl && hgt && iyr && pid) {
            valid_passwords++;
        }
    }

    printf("Part1: %d\n", valid_passwords);
}


void part2(const struct password_record* passwords, int length)
{
    int valid_passwords = 0;

    for (int i=0; i<length; i++) {
        if (validate(&passwords[i])) {
            valid_passwords++;
        }
    }

    printf("Part1: %d\n", valid_passwords);
}


int main(void)
{
    struct password_record* passwords = NULL;
    int length = 0;

    length = read_passwords_file(INPUT_FILE, &passwords);
    printf("Len: %d\n", length);

    part1(passwords, length);
    part2(passwords, length);

    free(passwords);

    return 0;
}
