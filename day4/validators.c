#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "day4/main.h"

static int validate_hcl(const char* hcl)
{
    int len = strnlen(hcl, FIELD_LEN);
    char allowlist[] = "0123456789abcdef";

    if (hcl[0] != '#') {
        return 0;
    }

    for (int i=1; i<len; i++) {
        int ok = 0;
        for (int j=0; j<16; j++) {
            if (hcl[i] == allowlist[j]) {
                ok = 1;
            }
        }

        if (!ok) {
            return 0;
        }
    }

    return 1;
}


static int validate_ecl(const char* ecl)
{
    char fields[][3] = {"amb", "blu", "brn", "gry", "grn", "hzl", "oth"};

    for (int i=0; i<7; i++) {
        if (strncmp(ecl, fields[i], 3) == 0) {
            return 1;
        }
    }

    return 0;
}

static int validate_range(const char* data, int required_len, int min, int max)
{
    int len = strnlen(data, FIELD_LEN);
    int number = atoi(data);
    if (len == required_len && number >= min && number <= max) {
        return 1;
    }

    return 0;
}


int validate(const struct password_record* password)
{
    int pid = 0;
    int number = 0;
    char unit[FIELD_LEN];

    if (!validate_range(password->byr, 4, 1920, 2002)) {
        return 0;
    }

    if (!validate_range(password->iyr, 4, 2010, 2020)) {
        return 0;
    }

    if (!validate_range(password->eyr, 4, 2020, 2030)) {
        return 0;
    }

    sscanf(password->hgt, "%d%s", &number, unit);
    if (strncmp(unit, "cm", 2) == 0) {
        if (!(number >= 150 && number <= 193)) {
            return 0;
        }
    }
    else {
        if (!(number >= 59 && number <= 76)) {
            return 0;
        }
    }

    if (!validate_hcl(password->hcl)) {
        return 0;
    }

    if (!validate_ecl(password->ecl)) {
        return 0;
    }

    pid = strnlen(password->pid, FIELD_LEN);
    if (!(pid == 9)) {
        return 0;
    }

    return 1;
}
