#!/usr/bin/env python3

class List:
    def __init__(self, payload):
        self.next = None
        self.payload = payload

    def link(self, new_node_ref):
        self.next = new_node_ref

    def ith(self, ix):
        curr = self
        i = 0
        while curr is not None and i < ix:
            i += 1
            curr = curr.next
        return curr

    def __str__(self):
        s = "[{}, ".format(self.payload)
        curr = self.next
        while curr != None:
            s += "{}".format(curr.payload)
            if curr.next is not None:
                s += ", "
            curr = curr.next
        s += "]"
        return s

def length(xs):
    curr = xs
    length = 1 if xs is not None else 0
    while curr is not None:
        length += 1
        curr = curr.next
    return length

def from_prim_list(xs):
    prev = None
    curr = None
    head = None
    for x in xs:
        prev = curr
        curr = List(x)
        if head is None:
            head = curr
        if prev is not None:
            prev.link(curr)
    return head


def head_of_intersection(xs, ys):
    xlen = length(xs)
    ylen = length(ys)
    d = set([])
    ps = xs if xlen > ylen else ys
    qs = ys if xlen > ylen else xs
    curr = ps
    while curr is not None:
        d |= {hex(id(curr))}
        curr = curr.next
    curr = qs
    while curr is not None:
        if hex(id(curr)) in d:
            return curr
        curr = curr.next
    return None


if __name__ == '__main__':
    xs = from_prim_list([1,2,3, 4, 5, 6])
    ys = xs.ith(2)
    print(xs)
    print(ys)
    intersection0 = head_of_intersection(xs, ys)
    print(intersection0)
    assert(ys == intersection0)

    ps = from_prim_list([1,2,3])
    qs = from_prim_list([1,2,3])
    print(ps)
    print(qs)
    intersection1 = head_of_intersection(ps, qs)
    print(intersection1)
    assert(qs != intersection1)
