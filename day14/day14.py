#!/usr/bin/env python3

import re
import argparse


def apply_mask(number, mask):
    result = [x for x in number]

    for i, x in enumerate(mask):
        if x == '1':
            result[i] = x

        if x == '0':
            result[i] = x

    return int("".join(result), 2)


def part1(data):
    mask = ""
    memory = {}

    for line in data:
        if "mask" in line:
            mask = line.split(' = ')[-1]
        else:
            match = re.match(r"mem\[(\d+)\] = (\d+)", line)
            number = "{0:036b}".format(int(match[2]))

            memory[match[1]] = apply_mask(number, mask)

    print("Part1: {}".format(sum(memory.values())))


def main(input_file):

    with open(input_file) as f:
        data = f.read().splitlines()

    part1(data)


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument('input_file')
    args = parser.parse_args()

    main(**vars(args))
