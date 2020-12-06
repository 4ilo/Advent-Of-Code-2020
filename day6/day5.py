#!/usr/bin/env python3
import argparse
from collections import defaultdict

def part1(data):
    groups = []
    group = set()
    for line in data:
        if line == '':
            groups.append(group)
            group = set()
            continue

        group.update(list(line))

    groups.append(group)

    print(f"Part1: {sum([len(x) for x in groups])}")


def part2(data):
    groups = []
    group = []
    for line in data:
        if line == '':
            groups.append(group)
            group = []
            continue

        group.append(set(line))

    groups.append(group)

    yes = []
    for group in groups:
        test = defaultdict(int)
        for person in group:
            for q in list(person):
                test[q] += 1

        yes.append(sum([1 for k, v in test.items() if v == len(group)]))

    print(f"Part2: {sum(yes)}")


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
