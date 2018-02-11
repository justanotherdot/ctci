#!/usr/bin/env python3

def is_unique_via_sorted(s):
    ss = {s0 for s0 in sorted(s)}
    return len(ss) == len(s)

def is_unique_via_ds(s):
    d = {}
    for c in list(s):
        if d.get(c, False):
            return False
        else:
            d[c] = c
    return True

if __name__ == "__main__":
    examples = [
        "a",
        "ba",
        "bba",
        "yum",
    ]
    expected = [
        True,
        True,
        False,
        True
    ]

    print("is_unique_via_sorted")
    is_unique = is_unique_via_sorted
    for i, example in enumerate(examples):
        s = example
        b = "yes" if is_unique(example) else "no"

        print("Is {s} unique? {b}.".format(s=s, b=b));
        assert(is_unique(example) == expected[i])
    print("")

    print("is_unique_via_ds")
    is_unique = is_unique_via_ds
    for i, example in enumerate(examples):
        s = example
        b = "yes" if is_unique(example) else "no"

        print("Is {s} unique? {b}.".format(s=s, b=b));
        assert(is_unique(example) == expected[i])
