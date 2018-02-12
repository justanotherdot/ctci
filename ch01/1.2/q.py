#!/usr/bin/env python3

def histogram(str0):
    d = {}
    for c in list(str0):
        if c in d:
            d[c] += 1
        else:
            d[c] = 0
    return d

def cmp(str0, str1):
    d0 = histogram(str0)
    d1 = histogram(str1)
    return d0 == d1

if __name__ == '__main__':
    examples = [
        ('apple', 'pplea', True),
        ('can', 'dog', False),
        ('taco', 'octa', True),
        ('', '', True),
        ('castles were here', 'here were castles', True),
        ('castles  ', 'seltsac   ', False),
    ]
    for ex0, ex1, rv0 in examples:
        rv = cmp(ex0, ex1)
        assert rv == rv0
        print(rv)

