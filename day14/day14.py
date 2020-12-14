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


def all_combinations(data, cache):
    ids = []

    cache["".join(data)] = True

    for i, x in enumerate(data):
        if x == 'X':
            tmp = data[:]
            for bit in ['0', '1']:
                tmp[i] = bit
                if "".join(tmp) not in cache:
                    ids += all_combinations(tmp, cache)

    if not 'X' in data:
        return [int("".join(data), 2)]

    return ids


def apply_mask2(number, mask):
    result = [x for x in number]

    for i, x in enumerate(mask):
        if x in ['1', 'X'] :
            result[i] = x

    cache = {}
    return all_combinations(result, cache)


def part2(data):
    mask = ""
    memory = {}

    for line in data:
        if "mask" in line:
            mask = line.split(' = ')[-1]
        else:
            match = re.match(r"mem\[(\d+)\] = (\d+)", line)
            number = "{0:036b}".format(int(match[1]))

            for index in apply_mask2(number, mask):
                memory[index] = int(match[2])

    print("Part2: {}".format(sum(memory.values())))


def main(input_file):

    with open(input_file) as f:
        data = f.read().splitlines()

    part1(data)
    part2(data)


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument('input_file')
    args = parser.parse_args()

    main(**vars(args))
