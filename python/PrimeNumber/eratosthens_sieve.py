#!/usr/bin/env python2.7
# -*- utf-8 -*-

import argparse


def get_all_prime(max_n):
    blanks = [True] * max_n
    for num in xrange(2, max_n + 1):
        for div in xrange(2, max_n + 1):
            if num != div and num % div == 0:
                blanks[num - 1] = False

    for number, is_prime in enumerate(blanks, 1):
        if is_prime:
            yield number


def main():
    parser = argparse.ArgumentParser(description='Print prime number')
    parser.add_argument(
        '-m', '--max-number',
        type=int,
        metavar="NUM",
        required=True,
        help='Max number of output sequense',
    )
    args = parser.parse_args()
    for num in get_all_prime(args.max_number):
        print num


if __name__ == "__main__":
    main()
