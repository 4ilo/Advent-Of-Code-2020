#ifndef _MAIN_H
#define _MAIN_H

#define FIELD_LEN 25

struct password_record {
    char byr[FIELD_LEN];
    char cid[FIELD_LEN];
    char ecl[FIELD_LEN];
    char eyr[FIELD_LEN];
    char hcl[FIELD_LEN];
    char hgt[FIELD_LEN];
    char iyr[FIELD_LEN];
    char pid[FIELD_LEN];
};

int validate(const struct password_record* password);

#endif  // _MAIN_H
