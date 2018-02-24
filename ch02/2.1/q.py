#!/usr/bin/env python3

# O(n), if you believe in 'effectively constant' hashing.
def nub_with_tmp(xs):
    d = {}
    ys = []
    for x in xs:
        if d.get(x, None) == None:
            d[x] = True
            ys.append(x)
    return ys


if __name__ == '__main__':
    xs = [
        13,
        12,
        13,
        11,
        14,
        12,
    ]
    ys = nub_with_tmp(xs)
    print(ys)
