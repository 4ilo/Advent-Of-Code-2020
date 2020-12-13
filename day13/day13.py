#!/usr/bin/env python3

import argparse


def part1(timestamp, ids):
    nearest_times = {}

    for id in ids:
        time = id
        while time <= timestamp:
            time += id

        nearest_times[time] = id

    nearest = sorted(nearest_times.keys())[0]
    print("Part1: {}".format(nearest_times[nearest] * (nearest - timestamp)))


def mul_inv(a, b):
    '''
    Chinese remainder theorem implementation used from
    https://rosettacode.org/wiki/Chinese_remainder_theorem#Procedural
    '''

    b0 = b
    x0, x1 = 0, 1

    if b == 1:
        return 1

    while a > 1:
        q = a // b
        a, b = b, a % b
        x0, x1 = x1 - q * x0, x0

    if x1 < 0:
        x1 += b0

    return x1


def part2(ids):
    dividers = [int(bus) for bus in ids if bus != 'x']
    remainders = [int(bus) - i for i, bus in enumerate(ids) if bus != 'x']

    total = 0
    n_prod = 1
    for n in dividers:
        n_prod *= n

    for n_i, a_i in zip(dividers, remainders):
        p = n_prod // n_i
        total += a_i * mul_inv(p, n_i) * p

    result = total % n_prod

    print(f"Part2: {result}")


def main(input_file):
    with open(input_file) as f:
        timestamp, ids = f.read().splitlines()

    timestamp = int(timestamp)
    ids = [x for x in ids.split(',')]

    part1(timestamp, [int(x) for x in ids if x != 'x'])
    part2(ids)


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument('input_file')
    args = parser.parse_args()

    main(**vars(args))
