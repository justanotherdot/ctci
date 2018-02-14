#!/usr/bin/env python3

from collections import defaultdict


# Utility.
even_str = lambda s: len(s) % 2 == 0
no_spaces_str = lambda s: filter(lambda cs: not cs.isspace(), list(s))

def histogram(s0):
    d = defaultdict(int)
    for c in no_spaces_str(s0):
        d[c] += 1
    return d

def palindrome_permute_exists(s0):
    """
    Given some string, determine if there exists a permutation of said string
    which is a valid palindrome.

    This function ignores whitespace and _should be_ utf8 aware.
    """

    h = histogram(s0)
    if even_str(no_spaces_str(s0)):
        return all(v % 2 == 0 for v in h.values())
    else:
        vs = sorted(h.values(), key=lambda a: -a)

        k_minus_one_evens = all(v % 2 == 0 for v in vs[:-1])
        last_elem_is_odd = vs[-1] % 2 == 1

        return k_minus_one_evens and last_elem_is_odd


if __name__ == '__main__':
    examples = [
        ("", True),
        ("a", True),
        ("ab", False),
        ("aa", True),
        ("taco cat", True),
        ("racecar", True),
        ("rreeejjjqqqrr", False),
        ("ba ab", True),
        ("ba      ab", True),
        ("boabab", False),
        ("   boabab", False),
        ("   boabab  ", False),
        ("   bab  ", True),
    ]

    for example, expectation in examples:
        pal_permute_exists = palindrome_permute_exists(example)
        assert pal_permute_exists == expectation
        print("'{}' is {} palindrome".format(example, "a" if expectation else "not a"))
