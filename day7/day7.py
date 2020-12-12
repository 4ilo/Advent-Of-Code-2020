#!/usr/bin/env python3

import argparse
from collections import defaultdict


def find(all_bags, bag, target):
    amount = 0

    for number, content in all_bags[bag]:
        if content == target:
            amount += number
        else:
            amount += number * find(all_bags, content, target)

    return amount


def part1(all_bags, target):
    amount = 0

    for bag in list(all_bags):
        if find(all_bags, bag, target):
            amount += 1

    print(f"Part1: {amount}")


def find2(all_bags, bag):
    amount = 1

    if len(all_bags[bag]) == 0:
        return 1

    for number, content in all_bags[bag]:
        amount += number * find2(all_bags, content)

    return amount


def part2(all_bags, target):
    amount = 0
    amount += find2(all_bags, target) - 1
    print(f"Part2: {amount}")


def main(input_file):
    with open(input_file) as f:
        data = f.read().splitlines()

    bags = defaultdict(list)
    for line in data:
        bag, contents = line.split("bags contain")
        for content in contents.split(","):
            number, prefix, color = content.strip().split(' ')[:3]
            if number != 'no':
                bags[bag.strip()].append((int(number), f"{prefix} {color}"))

    part1(bags, "shiny gold")
    part2(bags, "shiny gold")


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument('input_file')
    args = parser.parse_args()

    main(**vars(args))
